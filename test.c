#include <signal.h>
#include <unistd.h>
#include <stdio.h>

void sig_handler()
{
	printf("catched sigusr1\n");
	return ;
}

int main()
{
	if (signal(SIGUSR1, sig_handler) == SIG_ERR)
	{
		perror("SIGUSR1 ERROR");
	}
	while(1) sleep(1);
	return 1;
}

