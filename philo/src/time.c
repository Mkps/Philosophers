#include "../includes/philo.h"

long	ft_timetol(tv time)
{
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

long	ft_get_time(void)
{
	tv	time;

	gettimeofday(&time, NULL);
	return(ft_timetol(time));
}
