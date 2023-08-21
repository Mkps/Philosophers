/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 23:44:52 by aloubier          #+#    #+#             */
/*   Updated: 2023/08/21 21:17:48 by aloubier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	run_process(t_data *data)
{
	t_phi	*phi;

	phi = data->current_phi;
	if (pthread_create(&phi->overseer, NULL, &overseer_thread, data))
	{
		printf("Error creating overseer thread for process %i\n", phi->id + 1);
		exit (ERR_PTHREAD);
	}
	if (data->meal_limit == 0)
	{
		sem_post(data->sem_sated);
		child_exit(data, PHI_SATED);
	}
	if (data->ttd == 0)
	{
		sem_post(data->sem_death);
		child_exit(data, PHI_DEAD);
	}
	wait_start(data);
	philo_routine(phi);
}

static int	fork_error(t_data *data)
{
	printf("Error forking process\n");
	if (data->phi_array)
		free(data->phi_array);
	return (EXIT_FAILURE);
}

int	ft_spawn_philo(t_data *data)
{
	int		i;

	i = -1;
	while (++i < data->phi_count)
	{
		data->phi_array[i].pid = fork();
		if (data->phi_array[i].pid == -1)
			return (fork_error(data));
		if (!data->phi_array[i].pid)
		{
			data->current_phi = &data->phi_array[i];
			data->current_phi->data = data;
			data->current_phi->is_sated = 0;
			run_process(data);
		}
	}
	if (status_check(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
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
		usleep(1000);
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
