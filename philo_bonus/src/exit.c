/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 12:31:58 by aloubier          #+#    #+#             */
/*   Updated: 2023/08/21 01:36:42 by aloubier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	kill_all_phi(t_data *data, int exit_code)
{
	int	i;

	i = 0;
	while (i < data->phi_count)
	{
		kill(data->phi_array[i++].pid, SIGKILL);
	}
	return (exit_code);
}

void	cleanup_data(t_data *data)
{
	pthread_join(data->death_thread, NULL);
	pthread_join(data->sated_thread, NULL);
	sem_close(data->sem_output);
	sem_close(data->sem_continue);
	sem_close(data->sem_data);
	sem_close(data->sem_forks);
	sem_close(data->sem_death);
	sem_close(data->sem_sated);
	sem_unlink("/sem_forks");
	sem_unlink("/sem_data");
	sem_unlink("/sem_output");
	sem_unlink("/sem_continue");
	sem_unlink("/sem_death");
	sem_unlink("/sem_sated");
	free(data->phi_array);
}

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
