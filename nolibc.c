/* with this... only safe glibc function is syscall */

#include <stddef.h>

#include <stdint.h>
#include <unistd.h>
#include <sys/syscall.h>

#if defined(__i386__) || defined(__x86_64__)
#include <asm/prctl.h>
#endif
#define NORETURN __attribute__((noreturn, used))
#define TLS_SIZE 64

static int64_t  __errno_variable;
static uintptr_t tls_area[TLS_SIZE] __attribute__((aligned(16))); // tiny TLS block
static void __tls_init(void)
{
	for (size_t i = 0; i < TLS_SIZE; i++)
		tls_area[i] = (uintptr_t) &__errno_variable;
#if defined(__x86_64__)
	syscall(SYS_arch_prctl, ARCH_SET_FS, &tls_area[TLS_SIZE / 2]);
#elif defined(__aarch64__)
	__asm__("msr tpidr_el0, %0" :: "r"(&tls_area[TLS_SIZE / 2]));
#else
#error "Unsupported architecture"
#endif
}

NORETURN static inline void
__exit(int ret)
{
	syscall(SYS_exit_group, ret);
	__builtin_unreachable();
}


NORETURN int
__libc_start_main(
    int (*main) (int, char * *, char * *),
    int argc,
    char **argv,
    void (*init) (void),
    void (*fini) (void),
    void (*rtld_fini) (void),
    void (* stack_end)
)
{
	__tls_init();
	__exit(main(argc, argv, &argv[argc + 1]));
	__builtin_unreachable();
}

#ifdef __aarch64__
void abort()
{
	__exit(-1);
}
#endif
