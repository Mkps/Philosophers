/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 23:44:52 by aloubier          #+#    #+#             */
/*   Updated: 2023/08/12 23:44:53 by aloubier         ###   ########.fr       */
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
void	phi_locked(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->phi_count)
	{
		if (data->phi_array[i]->got_forks == 1)
			unlock_forks(data->phi_array[i]);
		i++;
	}
}
void	*overseer_thread(void *source)
{
	t_phi	*overseer;
	// int		i;

	overseer = (t_phi *)source;
	// usleep(100);
	// i = 0;
	// while (i < overseer->data->phi_count)
	// {
		// pthread_mutex_lock(&overseer->data->mutex);
		// if (overseer->data->phi_array[i]->got_forks == 0)
		// {
			// pthread_mutex_unlock(&overseer->data->mutex);
		// 	output_msg(overseer->data->phi_array[i], "is thinking");
		// }
		// i++;
	// }
	while (1)
	{
		if (!phi_continue(overseer->data))
			break;
		// phi_locked(overseer->data);
		usleep(50);
	}
	return (0);
}

void	*philo_thread(void *source)
{
	t_phi *phi;
	t_data	*data;
	phi = (t_phi *)source;
	data = phi->data; 
	if (phi->id % 2 == 0)
		ft_sleep(phi, 10);
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
	return(0);
}

void	run_thread(t_data *data)
{
	pthread_create(&data->overseer->t_id, NULL, &overseer_thread, data->overseer);
	ft_create_thread(data);
	ft_join_thread(data);
	pthread_join(data->overseer->t_id, NULL);

}
