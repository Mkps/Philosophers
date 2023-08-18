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
		data->phi_array[i].pid = fork();
		if (data->phi_array[i].pid == 0)
		{
			philo_thread(&data->phi_array[i]);
			sem_close(data->sem_continue);
			sem_close(data->sem_output);
			sem_close(data->sem_data);
			sem_close(data->sem_forks);
			if (data->phi_array[i].is_alive == 0)
			{
				free(data->phi_array);
				exit (1);

			}
			free(data->phi_array);
			exit (0);
		}
		i++;
	}
	ft_join_thread(data);
	sem_post(data->sem_continue);
	return ;
}

void	ft_join_thread(t_data *data)
{
	int	i;
	// int	count;
	int	status;

	i = 0;
	status = 0;
	// count = 0;
	while (i < data->phi_count)
	{
		// printf("got a process");
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			i = -1;
			while (++i < data->phi_count)
				kill(data->phi_array[i].pid, SIGKILL);
			break;
		}
		// printf("count2 = %i\n", count);
		// printf("got a process");
		// if (count == data->phi_count)
		// 	sem_post(data->sem_continue);// while (i < data->phi_count)
		i++;
	}
}

void	*overseer_thread(void *source)
{
	// t_phi	*overseer;
	(void)source;

	// overseer = (t_phi *)source;
	while (1)
	{
		// if (!phi_continue(overseer->data))
			break ;
		usleep(50);
	}
	return (0);
}

void	*philo_thread(void *source)
{
	t_phi	*phi;
	// t_data	*data;

	phi = (t_phi *)source;
	// data = phi->data; 
	ft_philo_q(phi);
	// printf("entered thread");
	while (phi_continue(phi))
	{
		if (phi_continue(phi))
			philo_is_taking_forks(phi);
		if (phi_continue(phi))
			philo_is_eating(phi);
		if (phi_continue(phi))
			philo_is_sleeping(phi);
		if (phi_continue(phi))
			philo_is_thinking(phi);
		// printf("keep going");
	}
	printf("phi %i is done\n", phi->id+1);
	unlock_forks(phi);
	return (0);
}

void	run_thread(t_data *data)
{
	int	i;
	
	sem_wait(data->sem_continue);
	ft_create_thread(data);
	sem_wait(data->sem_continue);
	i = -1;
	while (++i < data->phi_count)
		kill(data->phi_array[i].pid, SIGKILL);
	// ft_join_thread(data);
}
