#ifndef __ARCH_SHIM_IMPL__
#define __ARCH_SHIM_IMPL__

#define set_tls_ptr(ptr) __asm__("msr tpidr_el0, %0" :: "r"(ptr))

void abort()
{
	__exit(-1);
}
#endif /* __ARCH_SHIM_IMPL__ */
