#include <signal.h>
#include <stdio.h>
#include <unistd.h>

static int	not_recv;

pid_t	ft_atoi(char *str)
{
	pid_t	pid;

	pid = 0;
	while(*str)
	{
		if (*str >= '0' && *str <= '9')
			pid = pid * 10 + (*str - 48);
		else
			return (-1);
		str++;
	}
	return (pid);
}

void	ft_atob(char c, int *byte)
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

void	ft_sig_handler()
{
	//printf("\nGot signal from serer %d\n", signal);
	not_recv = 0;
}

void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

void	ft_send(pid_t pid, char *msg)
{
	int	byte[8];
	int	i;
	char	c;
	
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
			c = byte[i] + 48;
			write(1, &c, 1);
			not_recv = 1;
			usleep(2000);
			i++;
		}
		msg++;
	}
}


int main(int argc, char **argv)
{
	pid_t	pid;
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
	return 0;
}
