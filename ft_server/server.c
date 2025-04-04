#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>



void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

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
	
	//if (signal == SIGUSR2)
	//	write(1, "1", 1);
	//else
	//	write(1, "0", 1);
	if (signal == SIGUSR1)
		byte = (byte << 1);
	else
		byte = (byte << 1) | 1;
	//printf("\n=%d %d\n", byte, count);
	if (count == 8)
	{
		if (byte == 0)
			write(STDOUT_FILENO, "\n", 1);
		else
			write(STDOUT_FILENO, &byte, 1);
		count = 0;
		//write(1, " ", 1);
	}
	if (client_pid == 0)
		printf("sdf");
	kill(client_pid, SIGUSR2);
}


int	main()
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ft_sig_handler;
	ft_putstr("PID: ");
	ft_putnbr(getpid());
	ft_putstr("\n");
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
