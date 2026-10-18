#ifndef __ARCH_SHIM_IMPL__
#define __ARCH_SHIM_IMPL__
#include <asm/prctl.h>

static inline void set_tls_ptr(void *ptr) {
	syscall(SYS_arch_prctl, ARCH_SET_FS, ptr);
}

#endif /* __ARCH_SHIM_IMPL__ */
