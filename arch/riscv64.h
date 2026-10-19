#ifndef __ARCH_SHIM_IMPL__
#define __ARCH_SHIM_IMPL__

static inline void set_tls_ptr(void *ptr) {
	__asm__ volatile("mv tp, %0" :: "r"(ptr));
}

#endif /* __ARCH_SHIM_IMPL__ */
