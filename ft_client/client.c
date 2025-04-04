#include <signal.h>
#include <unistd.h>

pid_t	ft_atoi(char *str)
{
	pid_t	pid;

	pid = 0;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			pid = pid * 10 + (*str - 48);
		else
			return (-1);
		str++;
	}
	return (pid);
}

void	ft_atob(unsigned char c, int *byte)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		byte[i] = c % 2;
		c /= 2;
		i--;
	}
}

void	ft_sig_handler(int signal)
{
	if (signal == SIGUSR2)
		write(1, "OK\n", 0);
}

void	ft_send_end(pid_t pid)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		kill(pid, SIGUSR1);
		usleep(2500);
		i++;
	}
}

void	ft_send(pid_t pid, char *msg)
{
	int	byte[8];
	int	i;

	while (*msg)
	{
		i = 0;
		ft_atob(*msg, byte);
		while (i < 8)
		{
			if (byte[i])
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(3500);
			i++;
		}
		write(1, "Ok!\n", 4);
		msg++;
	}
	ft_send_end(pid);
}

int	main(int argc, char **argv)
{
	pid_t				pid;
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = ft_sig_handler;
	sa.sa_flags = 0;
	sigaction(SIGUSR2, &sa, NULL);
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		if (pid != -1)
			ft_send(pid, argv[2]);
	}
	return (0);
}
