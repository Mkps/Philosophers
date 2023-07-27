#include "../includes/philo.h"

typedef struct timeval tv;
void	timestamp(tv start)
{
	tv	end;

	gettimeofday(&end, NULL);
	printf("[ms : %ld ", ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)) / 1000 );
}

typedef struct philosopher {
	int	is_alive;
	long	tts;
	long	tte;
	long	ttd;
} t_philo;

int	main(int argc, char **argv)
{
	tv		tc;
	tv		to;
	tv		cycle;
	t_philo phi;

	if (argc != 5)
		return (0);
	gettimeofday(&to, NULL);
	phi.is_alive = 1;
	phi.ttd = atol(argv[2]);
	phi.tte = atoi(argv[3]);
	phi.tts = atol(argv[4]);
	while (phi.is_alive)
	{
		gettimeofday(&cycle, NULL);
		timestamp(to);	
		printf("phi is eating\n");
		usleep(phi.tte * 1000);
		timestamp(to);	
		printf("phi is sleeping\n");
		usleep(phi.tts * 1000);
		gettimeofday(&tc, NULL);
		if (((tc.tv_sec * 1000000 + tc.tv_usec) - (cycle.tv_sec * 1000000 + cycle.tv_usec)) / 1000 > phi.ttd)
			phi.is_alive = 0;
	}
	timestamp(to);	
	printf("phi died...\n");
	return (0);
}
