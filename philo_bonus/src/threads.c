/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 23:44:52 by aloubier          #+#    #+#             */
/*   Updated: 2023/08/15 12:46:03 by aloubier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <pthread.h>

void	ft_create_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->phi_count)
	{
		pthread_create(&data->phi_array[i]->t_id, NULL,
			&philo_thread, data->phi_array[i]);
		i++;
	}
}

void	ft_join_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->phi_count)
	{
		pthread_join(data->phi_array[i]->t_id, NULL);
		i++;
	}
}

void	*overseer_thread(void *source)
{
	t_phi	*overseer;

	overseer = (t_phi *)source;
	while (1)
	{
		if (!phi_continue(overseer->data))
			break ;
		usleep(50);
	}
	return (0);
}

void	*philo_thread(void *source)
{
	t_phi	*phi;
	t_data	*data;

	phi = (t_phi *)source;
	data = phi->data; 
	ft_philo_q(phi);
	while (phi_continue(data))
	{
		if (phi_continue(data))
			philo_is_taking_forks(phi);
		if (phi_continue(data))
			philo_is_eating(phi);
		if (phi_continue(data))
			philo_is_sleeping(phi);
		if (phi_continue(data))
			philo_is_thinking(phi);
	}
	unlock_forks(phi);
	return (0);
}

void	run_thread(t_data *data)
{
	pthread_create(&data->overseer->t_id, NULL,
		&overseer_thread, data->overseer);
	ft_create_thread(data);
	ft_join_thread(data);
	pthread_join(data->overseer->t_id, NULL);
}
