#ifndef __ARCH_SHIM_IMPL__
#define __ARCH_SHIM_IMPL__

static inline long
__syscall4(long n, long a, long b, long c, long d)
{
	register long r10 __asm__("r10") = d;
	long ret;

	__asm__ volatile ("syscall"
	                  : "=a" (ret)
	                  : "a" (n), "D" (a), "S" (b), "d" (c), "r" (r10)
	                  : "rcx", "r11", "memory");
	return ret;
}

__attribute__((naked, noreturn, used, section(".text.startup._start")))
void _start(void)
{
	__asm__ ("	xor	%ebp, %ebp\n"
	         "	and	$-16, %rsp\n"
	         "	call	main\n"
	         "	mov	%eax, %edi\n"
	         "	jmp	__exit\n");
}
#endif /* __ARCH_SHIM_IMPL__ */
