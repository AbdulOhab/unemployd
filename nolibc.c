/* with this... only safe glibc function is syscall */

#include <stdint.h>
#include "arch.h"

#define TLS_SIZE 64

static int64_t  __errno_variable;
static uintptr_t tls_area[TLS_SIZE] __attribute__((aligned(16))); // tiny TLS block
static void __tls_init(void)
{
	for (size_t i = 0; i < TLS_SIZE; i++)
		tls_area[i] = (uintptr_t) &__errno_variable;

	set_tls_ptr(&tls_area[TLS_SIZE / 2]);
}

NORETURN int
__libc_start_main(
    int (*main) (int, char * *, char * *),
    int argc,
    char **argv,
    void (*init) (void),
    void (*fini) (void),
    void (*rtld_fini) (void),
    void (* stack_end))
{
	__tls_init();
	__exit(main(argc, argv, &argv[argc + 1]));
	__builtin_unreachable();
}
