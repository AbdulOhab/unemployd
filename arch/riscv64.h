#ifndef __ARCH_SHIM_IMPL__
#define __ARCH_SHIM_IMPL__

static inline long
__syscall4(long n, long a, long b, long c, long d)
{
	register long a0 __asm__("a0") = a;
	register long a1 __asm__("a1") = b;
	register long a2 __asm__("a2") = c;
	register long a3 __asm__("a3") = d;
	register long a7 __asm__("a7") = n;

	__asm__ volatile ("ecall"
	                  : "+r" (a0)
	                  : "r" (a1), "r" (a2), "r" (a3), "r" (a7)
	                  : "memory");
	return a0;
}

__attribute__((naked, noreturn, used, section(".text.startup._start")))
void _start(void)
{
	__asm__ (".option push\n"
	         ".option norelax\n"
	         "	la	gp, __global_pointer$\n"
	         ".option pop\n"
	         "	andi	sp, sp, -16\n"
	         "	call	main\n"
	         "	tail	__exit\n");
}
#endif /* __ARCH_SHIM_IMPL__ */
