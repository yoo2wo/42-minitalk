/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayoo <jayoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 16:56:03 by jayoo             #+#    #+#             */
/*   Updated: 2021/12/22 17:12:06 by jayoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	reset_buf(unsigned char *buf, int len)
{
	int	i;

	i = 0;
	while (i < len)
		buf[i++] &= 0;
}

void	handler(int signo, siginfo_t *info, void *context)
{
	static unsigned char	buf[100];
	static int				idx;
	static int				count;

	if (--count == -1)
	{
		count = 7;
		idx++;
	}
	if (signo == SIGUSR1)
		buf[idx] |= (1 << count);
	else if (signo == SIGUSR2)
		buf[idx] &= ~(1 << count);
	if (buf[idx] == 127 || idx == 99)
	{
		write(1, buf, idx + 1);
		if (buf[idx] == 127)
			write(1, "\n", 1);
		reset_buf(buf, 100);
		idx = 0;
	}
}

int	main(void)
{
	struct sigaction	act1;
	pid_t				pid;

	act1.sa_sigaction = handler;
	act1.sa_flags = SA_SIGINFO;
	pid = getpid();
	write(1, "PID : ", 6);
	ft_putnbr(pid);
	write(1, "\n", 1);
	if (sigaction(SIGUSR1, &act1, NULL) != 0)
	{
		write(1, "Sigaction Error", 15);
		exit(1);
	}
	if (sigaction(SIGUSR2, &act1, NULL) != 0)
	{
		write(1, "Sigaction Error", 15);
		exit(1);
	}
	while (1)
		sleep(1);
	return (0);
}
