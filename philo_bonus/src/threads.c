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
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void	wait_start(t_data *data);
int		error_exit(t_data *data);
void	philo_routine(t_phi *phi);

void	child_exit(t_data *data, int exit_code)
{
	sem_post(data->sem_sated);
	pthread_join(data->current_phi->overseer, NULL);
	if (exit_code == -1)
		printf("error opening semaphore");
	if (exit_code == -2)
		printf("error opening thread");
	sem_close(data->sem_sated);
	sem_close(data->sem_death);
	sem_close(data->sem_data);
	sem_close(data->sem_forks);
	sem_close(data->sem_output);
	free(data->phi_array);
	exit(exit_code);
}

void	*check_sated_thread(void *src)
{
	t_data *data;

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

void	*check_death_thread(void *src)
{
	t_data	*data;

	data = (t_data *)src;
	wait_start(data);
	if (!data_continue(data))
		return(NULL);
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
	if (pthread_create(&data->sated_thread, NULL, check_sated_thread, data) != 0)
		return (error_exit(data));
	if (pthread_create(&data->death_thread, NULL, check_death_thread, data) != 0)
		return (error_exit(data));
	return (0);
}

void	run_process(t_data *data)
{
	t_phi	*phi;

	phi = data->current_phi;
	pthread_create(&phi->overseer, NULL, &overseer_thread, data);
	if (data->meal_limit == 0)
	{
		sem_post(data->sem_sated);
		child_exit(data, 2);
	}
	if (data->ttd == 0)
	{
		sem_post(data->sem_death);
		child_exit(data, 3);
	}
	wait_start(data);
	philo_routine(phi);
}

int		ft_spawn_philo(t_data *data)
{
	int	i;
	pid_t	pid;

	i = -1;
	while (++i < data->phi_count)
	{
		pid = fork();
		if (pid == -1)
			printf("error forking process\n");
		if (pid > 0)
			data->phi_array[i].pid = pid;
		if (!pid)
		{
			data->current_phi = &data->phi_array[i];
			data->current_phi->data = data;
			data->current_phi->is_sated = 0;
			run_process(data);
		}
	}
	if (status_check(data) == 1)
		return (1);
	return (0);
}

void	*overseer_thread(void *source)
{
	t_data	*data;

	data = (t_data *)source;
	if (data->meal_limit == 0)
		return (NULL);
	sem_wait(data->sem_death);
	sem_wait(data->sem_sated);
	wait_start(data);
	while (phi_continue(data->current_phi))
	{
		usleep(100);
		continue ;
	}
	return (NULL);
}

void	wait_start(t_data *data)
{
	while (ft_get_time() < data->start_time)
		continue ;	
}

void	philo_routine(t_phi *phi)
{
	ft_philo_q(phi);
	while (1)
	{
		philo_is_taking_forks(phi);
		philo_is_eating(phi);
		philo_is_sleeping(phi);
		philo_is_thinking(phi);
	}
}
