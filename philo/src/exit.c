/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 12:31:58 by aloubier          #+#    #+#             */
/*   Updated: 2023/08/22 09:32:26 by aloubier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	thread_error_exit(t_data *data, int index)
{
	int	i;

	pthread_mutex_lock(&data->mutex);
	data->alive = 0;
	pthread_mutex_unlock(&data->mutex);
	i = 0;
	while (i < index)
	{
		pthread_detach(data->phi_array[i]->t_id);
		i++;
	}
	return (EXIT_FAILURE);
}

int	error_forks_init(t_data *data, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
	return (EXIT_FAILURE);
}
