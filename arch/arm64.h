#ifndef __ARCH_SHIM_IMPL__
#define __ARCH_SHIM_IMPL__

static inline void set_tls_ptr(void *ptr) {
	__asm__("msr tpidr_el0, %0" :: "r"(ptr));
}

void abort()
{
	__exit(-1);
}
#endif /* __ARCH_SHIM_IMPL__ */
