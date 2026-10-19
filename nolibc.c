/* freestanding runtime: raw syscall wrapper and exit */

#include "arch.h"

long syscall(long n, ...)
{
	__builtin_va_list ap;
	long a, b, c, d;

	__builtin_va_start(ap, n);
	a = __builtin_va_arg(ap, long);
	b = __builtin_va_arg(ap, long);
	c = __builtin_va_arg(ap, long);
	d = __builtin_va_arg(ap, long);
	__builtin_va_end(ap);

	return __syscall4(n, a, b, c, d);
}

NORETURN void
__exit(int ret)
{
	__syscall4(SYS_exit_group, ret, 0, 0, 0);
	__builtin_unreachable();
}
