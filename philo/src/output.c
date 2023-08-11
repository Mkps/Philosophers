#include "../includes/philo.h"

void	timestamp(tv start)
{
	tv	end;

	gettimeofday(&end, NULL);
	printf("%ld ", (ft_timetol(end) - ft_timetol(start)));
}

void	output_msg(t_phi *phi, char *msg)
{
	int	alive;

	
	pthread_mutex_lock(&phi->data->mutex);
	alive = phi->data->alive;
	pthread_mutex_unlock(&phi->data->mutex);
	if (alive != 0)
	{
		pthread_mutex_lock(&phi->data->output);
		timestamp(phi->data->start_time);	
		printf("%i %s\n", phi->id + 1, msg);
		pthread_mutex_unlock(&phi->data->output);
	}
}
