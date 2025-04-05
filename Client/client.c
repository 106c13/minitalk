/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 13:56:24 by haaghaja          #+#    #+#             */
/*   Updated: 2025/04/05 15:08:33 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

pid_t	ft_atoi(char *str)
{
	pid_t	pid;

	pid = 0;
	if (!(*str))
		return (-1);
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			pid = pid * 10 + (*str - '0');
		else
			return (-1);
		str++;
	}
	return (pid);
}

void	ft_sig_handler(int signal)
{
	if (signal == SIGUSR1)
		write(1, "Message sent ", 13);
}

void	ft_send(pid_t pid, char *msg)
{
	int				i;
	unsigned char	c;

	if (!(*msg))
		return ;
	while (1)
	{
		i = 7;
		c = *msg;
		while (i >= 0)
		{
			if ((c >> i) & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(2800);
			i--;
		}
		write(1, "Ok!\n", 4);
		if (!(*msg))
			return ;
		msg++;
	}
}

int	main(int argc, char **argv)
{
	pid_t				pid;
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = ft_sig_handler;
	sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		if (pid != -1)
			ft_send(pid, argv[2]);
	}
	return (0);
}
