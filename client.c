/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayoo <jayoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 16:56:04 by jayoo             #+#    #+#             */
/*   Updated: 2021/12/22 17:08:49 by jayoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	post(int pid, int c)
{
	if (c == 1)
		kill(pid, SIGUSR1);
	else if (c == 0)
		kill(pid, SIGUSR2);
	usleep(100);
}

void	postBinary(int pid, int c, int num)
{
	if (c == 0)
	{
		while (num < 8)
		{
			post(pid, 0);
			num++;
		}
	}
	else
	{
		postBinary(pid, c / 2, ++num);
		post(pid, c % 2);
	}
}

void	postByte(int pid, char *str)
{
	int	i;
	int	c;
	int	num;
	int	last;

	last = 7;
	c = 0;
	i = 0;
	while (str[i])
	{
		num = 0;
		c = (int)str[i++];
		postBinary(pid, c, num);
	}
	post(pid, 0);
	while (last--)
		post(pid, 1);
}

int	main(int argc, char *argv[])
{
	if (argc != 3)
		return (0);
	write(1, "PID : ", 6);
	write(1, argv[1], ft_strlen(argv[1]));
	write(1, "\nMessage : ", 11);
	write(1, argv[2], ft_strlen(argv[2]));
	write(1, "\n", 1);
	postByte(ft_atoi(argv[1]), argv[2]);
}
