#include "../includes/philo.h"

typedef struct timeval tv;
void	timestamp(long tc, tv tval)
{
	gettimeofday(&tval, NULL);
	printf("[ms : %ld]   ", tval.tv_usec - tc);
}
int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	long	tc;
	tv value;

	gettimeofday(&value, NULL);
	tc = value.tv_usec;
	pid_t f = fork();
	if (!f)
	{
		timestamp(tc, value);
		printf("child\n");	
	}
	else
	{
		wait(NULL);
		timestamp(tc, value);
		printf("parent\n");
	
	pid_t p = fork();
	if (!p)
	{
		for (int i=0; i < 500; i++)
		{
			if (i == 0)
			{
				timestamp(tc, value);
				printf("waiting...\n");
			}
		}
	}
	else
	{
		wait(NULL);
		timestamp(tc, value);
		printf("DONE\n");
	}
	}
	return (0);
}
