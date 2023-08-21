/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 23:44:44 by aloubier          #+#    #+#             */
/*   Updated: 2023/08/21 16:37:16 by aloubier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	*check_sated_thread(void *src)
{
	t_data	*data;

	data = (t_data *)src;
	if (data->meal_limit == -1 || data->ttd == 0 || data->phi_count == 1)
		return (NULL);
	wait_start(data);
	while (data->sated < data->phi_count)
	{
		if (!data_continue(data))
			return (NULL);
		sem_wait(data->sem_sated);
		if (data_continue(data))
			data->sated++;
		else
			return (NULL);
	}
	sem_wait(data->sem_continue);
	data->continuer = 0;
	kill_all_phi(data, EXIT_SUCCESS);
	sem_post(data->sem_death);
	sem_post(data->sem_continue);
	return (NULL);
}

static void	*check_death_thread(void *src)
{
	t_data	*data;

	data = (t_data *)src;
	wait_start(data);
	if (!data_continue(data))
		return (NULL);
	sem_wait(data->sem_death);
	if (!data_continue(data))
		return (NULL);
	sem_wait(data->sem_continue);
	data->continuer = 0;
	kill_all_phi(data, EXIT_SUCCESS);
	sem_post(data->sem_sated);
	sem_post(data->sem_continue);
	return (NULL);
}

int	status_check(t_data *data)
{
	if (pthread_create(&data->sated_thread, NULL, 
			check_sated_thread, data) != 0)
	{
		printf("An error occured while starting a thread: sated_thread\n");
		return (error_exit(data));
	}
	if (pthread_create(&data->death_thread, NULL, 
			check_death_thread, data) != 0)
	{
		pthread_detach(data->sated_thread);
		printf("An error occured while starting a thread: sated_thread\n");
		return (error_exit(data));
	}
	return (0);
}

int	phi_continue(t_phi *phi)
{
	t_data	*data;

	data = phi->data;
	sem_wait(data->sem_data);
	if (ft_get_time() - phi->last_meal_time >= phi->data->ttd)
	{
		output_death(phi);
		sem_post(data->sem_death);
		sem_post(data->sem_data);
		return (0);
	}
	if (data->meal_limit != -1 && phi->is_sated == 0 
		&& phi->meal_count >= data->meal_limit)
	{
		sem_post(data->sem_sated);
		phi->is_sated = 1;
	}
	sem_post(data->sem_data);
	return (1);
}
