#ifndef __ARCH_SHIM_H__
#define __ARCH_SHIM_H__
#define _GNU_SOURCE

#include <unistd.h>
#include <sys/syscall.h>

#define NORETURN __attribute__((noreturn, used))

NORETURN void __exit(int ret);

static inline long __syscall4(long, long, long, long, long);

#if defined(__i386__) || defined(__x86_64__)
#include "arch/x86.h"
#elif defined(__aarch64__)
#include "arch/arm64.h"
#elif defined(__riscv) && __riscv_xlen == 64
#include "arch/riscv64.h"
#endif /* __ARCH_SHIM_IMPL__ */

#ifndef __ARCH_SHIM_IMPL__
#error "Unsupported architecture"
#endif
#endif /* __ARCH_SHIM_H__ */
