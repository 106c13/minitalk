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
		write(1, "Message sent!\n", 14);
}

int	ft_send_byte(char c, pid_t pid)
{
	int	i;
	int	sig;

	i = 7;
	while (i >= 0)
	{
		if ((c >> i) & 1)
			sig = SIGUSR2;
		else
			sig = SIGUSR1;
		if (kill(pid, sig) == -1)
			return (0);
		usleep(2800);
		i--;
	}
	return (1);
}

void	ft_minitalk(pid_t pid, char *msg)
{
	if (!(*msg))
		return ;
	while (1)
	{
		if (!ft_send_byte(*msg, pid))
		{
			write(1, "Error!\n", 7);
			return ;
		}
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
			ft_minitalk(pid, argv[2]);
		else
			write(1, "./client <pid> \"<message\">\n", 27);
	}
	else
		write(1, "./client <pid> \"<message>\"\n", 27);
	return (0);
}
