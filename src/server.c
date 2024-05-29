/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 01:30:58 by joandre-          #+#    #+#             */
/*   Updated: 2024/05/29 16:59:27 by joandre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	sigmsg(int sig, siginfo_t *info, void *context)
{
	static unsigned int		b = 0;
	static unsigned char	c = 0;

	(void)context;
	if (sig == SIGUSR1)
		++c;
	if (++b == 8)
	{
		if (c)
			write(STDOUT_FILENO, &c, 1);
		else
			write(STDOUT_FILENO, "\n_______________________\n", 25);
		b = 0;
		c = 0;
	}
	else
		c <<= 1;
	usleep(350);
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	act;

	if (sigemptyset(&act.sa_mask) == -1)
		return (-1);
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = sigmsg;
	if (sigaction(SIGUSR1, &act, NULL) == -1
		|| sigaction(SIGUSR2, &act, NULL) == -1)
		return (-1);
	ft_printf("PID: %i\n_____________\n", getpid());
	while (1)
		;
	return (0);
}
