#include "../includes/philo.h"

typedef struct timeval tv;

long	ft_time(tv time);
void	timestamp(tv start)
{
	tv	end;

	gettimeofday(&end, NULL);
	printf("[ms : %ld ", (ft_time(end) - ft_time(start)));
}



typedef struct philosopher {
	int	is_alive;
	long	tts;
	long	tte;
	long	ttd;
} t_philo;
long	ft_time(tv time)
{
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
void	ft_sleep(long duration)
{
	long	time;
	tv		start;
	tv		current;

	time = 0;
	gettimeofday(&start, NULL);
	while (time < duration)
	{
		usleep(50);
		gettimeofday(&current, NULL);
		time = ft_time(current) - ft_time(start);
	}
	usleep(time);
	return ;
}
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
		ft_sleep(phi.tte);
		timestamp(to);	
		printf("phi is sleeping\n");
		ft_sleep(phi.tts);
		gettimeofday(&tc, NULL);
		if ((ft_time(tc) - ft_time(cycle)) > phi.ttd)
			phi.is_alive = 0;
	}
	timestamp(to);	
	printf("phi died...\n");
	return (0);
}
