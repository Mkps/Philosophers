#include "../includes/philo.h"

static void	free_philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->phi_count)
		free(data->phi_array[i++]);
}

void	cleanup_data(t_data *data)
{
	forks_destroy(data);
	pthread_mutex_destroy(&data->mutex);
	pthread_mutex_destroy(&data->output);
	free_philosophers(data);
	free(data->overseer);
	free(data->phi_array);
}
