#define _GNU_SOURCE
#include <errno.h>
#include <signal.h>
#include <sys/signalfd.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdint.h>

#define SIGMASK(sig) (UINT64_C(1) << (sig - 1))
typedef uint64_t sigmask_t;

int main(void)
{
	sigmask_t mask = SIGMASK(SIGTERM) | SIGMASK(SIGINT);

	if (syscall(SYS_rt_sigprocmask, SIG_BLOCK, &mask, 0, sizeof(mask)) < 0)
		return 1;

	long fd = syscall(SYS_signalfd4, -1, &mask, sizeof(mask), SFD_CLOEXEC);
	if (fd < 0)
		return 1;

	struct signalfd_siginfo si;
	while(syscall(SYS_read, fd, &si, sizeof(si)) < 0
	      ? errno == EINTR
	      : si.ssi_signo != SIGINT && si.ssi_signo != SIGTERM
	     );

	syscall(SYS_close, fd);
	return 0;
}
