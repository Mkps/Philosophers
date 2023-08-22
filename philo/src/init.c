/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 12:32:19 by aloubier          #+#    #+#             */
/*   Updated: 2023/08/22 09:32:33 by aloubier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	init_mutex(t_data *data)
{
	t_mutex	mutex;
	t_mutex	output;

	if (pthread_mutex_init(&mutex, NULL) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&output, NULL) != EXIT_SUCCESS)
	{
		pthread_mutex_destroy(&mutex);
		return (EXIT_FAILURE);
	}
	data->mutex = mutex;
	data->output = output;
	return (EXIT_SUCCESS);
}

int	init_data(t_data *data, char **av)
{
	if (init_mutex(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	data->alive = 1;
	data->sated = 0;
	gettimeofday(&data->start_time, NULL);
	data->phi_count = ft_atol(av[1]);
	data->ttd = ft_atol(av[2]);
	data->tte = ft_atol(av[3]);
	data->tts = ft_atol(av[4]);
	data->meal_limit = -1;
	if (av[5] != NULL)
		data->meal_limit = ft_atol(av[5]);
	data->phi_array = (t_phi **)malloc(sizeof(t_phi *) * data->phi_count);
	if (!data->phi_array)
	{
		pthread_mutex_destroy(&data->mutex);
		pthread_mutex_destroy(&data->output);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	error_exit(t_data *data, int mode)
{
	pthread_mutex_destroy(&data->mutex);
	pthread_mutex_destroy(&data->output);
	free(data->phi_array);
	if (mode == 1)
		exit (EXIT_FAILURE);
	free(data->overseer);
	if (mode == 2)
		exit (EXIT_FAILURE);
	forks_destroy(data);
	exit (EXIT_FAILURE);
}

void	set_table(t_data *data)
{
	data->overseer = (t_phi *)malloc(sizeof(t_phi));
	if (!data->overseer)
		error_exit(data, 1);
	data->overseer->data = data;
	if (forks_init(data) != EXIT_SUCCESS)
		error_exit(data, 2);
	if (philos_init(data) != EXIT_SUCCESS)
		error_exit(data, 3);
}
