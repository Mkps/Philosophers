/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 23:44:52 by aloubier          #+#    #+#             */
/*   Updated: 2023/08/21 04:03:38 by aloubier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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

int	ft_spawn_philo(t_data *data)
{
	int		i;
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
