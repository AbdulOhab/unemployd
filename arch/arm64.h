#ifndef __ARCH_SHIM_IMPL__
#define __ARCH_SHIM_IMPL__

static inline long
__syscall4(long n, long a, long b, long c, long d)
{
	register long x8 __asm__("x8") = n;
	register long x0 __asm__("x0") = a;
	register long x1 __asm__("x1") = b;
	register long x2 __asm__("x2") = c;
	register long x3 __asm__("x3") = d;

	__asm__ volatile ("svc #0"
	                  : "+r" (x0)
	                  : "r" (x8), "r" (x1), "r" (x2), "r" (x3)
	                  : "memory");
	return x0;
}

__attribute__((naked, noreturn, used, section(".text.startup._start")))
void _start(void)
{
	__asm__ ("	mov	x29, xzr\n"
	         "	mov	x9, sp\n"
	         "	and	x9, x9, #-16\n"
	         "	mov	sp, x9\n"
	         "	bl	main\n"
	         "	mov	w0, w0\n"
	         "	b	__exit\n");
}
#endif /* __ARCH_SHIM_IMPL__ */
