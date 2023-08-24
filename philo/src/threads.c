/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 23:44:52 by aloubier          #+#    #+#             */
/*   Updated: 2023/08/24 16:41:49 by aloubier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <pthread.h>

int	ft_create_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->phi_count)
	{
		if (pthread_create(&data->phi_array[i]->t_id, NULL,
				&philo_thread, data->phi_array[i]) != EXIT_SUCCESS)
			return (thread_error_exit(data, i));
		i++;
	}
	return (EXIT_SUCCESS);
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

int	run_thread(t_data *data)
{
	if (pthread_create(&data->overseer->t_id, NULL,
			&overseer_thread, data->overseer) != 0)
	{
		data->alive = 0;
		printf("Error creating overseer thread.\n");
		return (EXIT_FAILURE);
	}
	if (ft_create_thread(data) == EXIT_FAILURE)
	{
		pthread_detach(data->overseer->t_id);
		printf("Error creating philosopher thread.\n");
		return (EXIT_FAILURE);
	}
	ft_join_thread(data);
	pthread_join(data->overseer->t_id, NULL);
	return (EXIT_SUCCESS);
}
