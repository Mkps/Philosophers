#include "../includes/philo.h"

void	increase_meal_count(t_phi *phi)
{
	pthread_mutex_lock(&phi->data->mutex);
	if (phi->meal_count != -1)
		phi->meal_count++;
	pthread_mutex_unlock(&phi->data->mutex);
}

int	is_phi_sated(t_phi *phi)
{
	pthread_mutex_lock(&phi->data->mutex);
	if (phi->data->meal_limit == -1)
	{
		pthread_mutex_unlock(&phi->data->mutex);
		return (0);
	}
	if (phi->meal_count < phi->data->meal_limit)
	{
		pthread_mutex_unlock(&phi->data->mutex);
		return (0);
	}
	pthread_mutex_unlock(&phi->data->mutex);
	return (1);
}

int	all_phi_sated(t_data *data)
{
	int		i;
	int		sated;

	i = 0;
	sated = 1;
	while (i < data->phi_count)
	{
		sated = is_phi_sated(data->phi_array[i]);
		if (sated == 0)
			return (0);
		i++;
	}
	return (sated);
}
