/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sever.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayoo <jayoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 16:56:03 by jayoo             #+#    #+#             */
/*   Updated: 2021/12/14 23:28:35 by jayoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

////////////**1**//////////////
// void sig_handler_usr1()
// {
// 	printf("catched sigusr1\n");
// 	return ;
// }

// void sig_handler_usr2()
// {
// 	printf("catched sigusr2\n");
// 	return ;
// }

// int main()
// {
// 	signal(SIGUSR1, sig_handler_usr1);
// 	signal(SIGUSR2, sig_handler_usr2);

// 	while(1) sleep(1);
// 	return 1;
// }
////////////**1**//////////////

void	handler(int signo, siginfo_t *info, void *context)
{
	if (signo == SIGUSR1)
		write(1, "1", 1);
    else if (signo == SIGUSR2)
		write(1, "0", 1);
}

int		main(void)
{
	struct sigaction act1;

	act1.sa_sigaction = handler;
	act1.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &act1, NULL) != 0)
	{
		printf("Sigaction Error");
		exit(1);
	}
	if (sigaction(SIGUSR2, &act1, NULL) != 0)
	{
		printf("Sigaction Error");
		exit(1);
	}
	while (1)
		;
	return (0);
}
