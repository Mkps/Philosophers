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
#include <semaphore.h>

void	init_data(t_data *data, char **av)
{
	sem_unlink("sem_data");
	data->sem_data = sem_open("sem_data", O_CREAT, 0600, 1);
	sem_unlink("sem_output");
	data->sem_output = sem_open("sem_output", O_CREAT, 0600, 1);
	sem_unlink("sem_continue");
	data->sem_continue = sem_open("sem_continue", O_CREAT, 0600, 1);
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
	data->phi_array = (t_phi *)malloc(sizeof(t_phi) * data->phi_count);
}

void	set_table(t_data *data)
{
	forks_init(data);
	philos_init(data);
}
