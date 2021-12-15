/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayoo <jayoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 16:56:03 by jayoo             #+#    #+#             */
/*   Updated: 2021/12/15 18:08:41 by jayoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void	reset_buf(unsigned char *buf, int len)
{
	int i;

	i = 0;
	while (i++ < len)
		buf[i] &= 0;
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
	//buf[idx] &= ~128;// 이거는 무슨 의미일까
	if (signo == SIGUSR1)
		buf[idx] |= (1 << count);
	else if (signo == SIGUSR2)
		buf[idx] &= ~(1 << count);

	if (buf[idx] == 127 || idx == 99)
	{
		write(1, buf, idx + 1);
		if (buf[idx] == 127)
			write(1, "\n" , 1);
		//만약 100글자를 넘기면 버퍼 초기화 해야한다.
		//무조건 리셋해야 된다 안그러면 중복된다.
		reset_buf(buf ,100);
		idx = 0;
	}
}

int		main(void)
{
	struct sigaction act1;

	act1.sa_sigaction = handler;
	act1.sa_flags = SA_SIGINFO;
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
	while (1);
	return (0);
}
