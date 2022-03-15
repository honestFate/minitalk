#include "minitalk.h"

void	ft_sighandler(int signal, siginfo_t *siginfo, void *context)
{
    static int  i;
    static int ch;

	usleep(500);
    (void)context;
    i++;
	if (signal == SIGUSR2) {
		ch += 1;
	}
	if (i == 8) {
		if (!ch)
			kill(siginfo->si_pid, SIGUSR2);
		write(1, &ch, 1);
		ch = 0;
		i = 0;
	} else { ch <<= 1; }
	kill(siginfo->si_pid, SIGUSR1);
}

int	main()
{
    struct sigaction sa;

	ft_putnbr_fd(getpid(), 1);
	ft_putendl_fd("", 1);
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = ft_sighandler;
	//sigemptyset(&sa.sa_mask);
	//sigaddset(&sa.sa_mask, SIGUSR1);
    if (sigaction(SIGUSR1, &sa, NULL) < 0 ||
    	sigaction(SIGUSR2, &sa, NULL) < 0)
		write(2, "SIG ERROR\n", 10);
	while(1)
    	pause();
}