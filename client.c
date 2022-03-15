#include "minitalk.h"

void ft_exit(char *str)
{
	ft_putendl_fd(str, 2);
	exit(0);
}

void ft_send(int ch, int pid)
{
	int bit;
	int	pow2;

	pow2 = 7;
	while (pow2 >= 0)
	{
		bit = (ch >> pow2) & 1;
		if (bit) {
			if (kill(pid, SIGUSR2) < 0)
				ft_exit("WRONG PID");
		}
		else if (kill(pid, SIGUSR1) < 0)
			ft_exit("WRONG PID");
		pause();
		usleep(100);
		--pow2;
	}
}

void	ft_sighandler(int signal, siginfo_t *siginfo, void *context)
{
	static int  count;

	count++;
	if (signal == SIGUSR2)
	{
		ft_putnbr_fd(count / 8, 1);
		ft_putendl_fd(" - chars sent", 1);
	}
}

int	main(int argc, char **argv)
{
	int 	i;
	int 	pid;
	struct	sigaction sa;

	long start = clock();
	if (argc != 3)
		ft_exit("WRONG ARGUMENTS");
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ft_sighandler;
	if (sigaction(SIGUSR1, &sa, NULL) < 0 ||
		sigaction(SIGUSR2, &sa, NULL) < 0)
		write(2, "SIG ERROR\n", 10);
	if (ft_isdigit(argv[1]))
		ft_exit("WRONG PID");
	pid = ft_atoi(argv[1]);
	i = 0;
	while(argv[2][i])
	{
		ft_send((unsigned char)argv[2][i], pid);
		i++;
	}
	ft_send(0, pid);
	long end = clock();
	printf("%ld\n",end - start);
	printf("%.4Lf\n",((long double)(end - start)) / (CLOCKS_PER_SEC));
}