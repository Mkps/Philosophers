/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 12:32:19 by aloubier          #+#    #+#             */
/*   Updated: 2023/08/15 12:38:54 by aloubier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_data(t_data *data, char **av)
{
	t_mutex	mutex;
	t_mutex	output;

	pthread_mutex_init(&mutex, NULL);
	pthread_mutex_init(&output, NULL);
	data->mutex = mutex;
	data->output = output;
	data->alive = 1;
	data->sated = 0;
	gettimeofday(&data->start_time, NULL);
	data->phi_count = ft_atol(av[1]);
	data->ttd = ft_atol(av[2]);
	data->tte = ft_atol(av[3]);
	data->tts = ft_atol(av[4]);
	if (av[5] != NULL)
		data->meal_limit = ft_atol(av[5]);
	else
		data->meal_limit = -1;
	data->phi_array = (t_phi **)malloc(sizeof(t_phi *) * data->phi_count);
}

void	set_table(t_data *data)
{
	data->overseer = (t_phi *)malloc(sizeof(t_phi));
	data->overseer->data = data;
	forks_init(data);
	philos_init(data);
}
