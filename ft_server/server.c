#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void	ft_putnbr(int num)
{
	char	c;

	if (num == 0)
		write(1, "0", 1);
	if (num / 10 != 0)
		ft_putnbr(num / 10);
	c = (num % 10) + 48;
	write(1, &c, 1);
}

void	ft_sig_handler(int signal, siginfo_t *info, void *context)
{
	static char	byte;
	static int	count;
	pid_t		client_pid;

	(void)context;
	client_pid = info->si_pid;
	count++;
	if (signal == SIGUSR1)
		byte = (byte << 1);
	else
		byte = (byte << 1) | 1;
	if (count == 8)
	{
		if (byte == 0)
			write(STDOUT_FILENO, "\n", 1);
		else
			write(STDOUT_FILENO, &byte, 1);
		count = 0;
	}
	kill(client_pid, SIGUSR2);
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ft_sig_handler;
	write(1, "PID: ", 5);
	ft_putnbr(getpid());
	write(1, "\n", 1);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
