/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 12:32:07 by aloubier          #+#    #+#             */
/*   Updated: 2023/08/15 12:41:48 by aloubier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <semaphore.h>

void	forks_init(t_data *data)
{
	sem_init(&data->sem_forks, 1, data->phi_count);
}

void	forks_destroy(t_data *data)
{
	sem_destroy(&data->sem_forks);
}

void	unlock_forks(t_phi *phi)
{
	int		forks;

	pthread_mutex_lock(&phi->data->mutex);
	forks = phi->got_forks;
	pthread_mutex_unlock(&phi->data->mutex);
	if (forks == 2)
	{
		sem_post(&phi->data->sem_forks);
		sem_post(&phi->data->sem_forks);
	}
	else if (forks == 1)
	{
		sem_post(&phi->data->sem_forks);
	}
}

void	philo_taking_first_fork(t_phi *phi)
{
	sem_wait(&phi->data->sem_forks);
	pthread_mutex_lock(&phi->data->mutex);
	phi->got_forks = 1;
	pthread_mutex_unlock(&phi->data->mutex);
	output_msg(phi, "has taken a fork");
}

void	philo_taking_second_fork(t_phi *phi)
{
	sem_wait(&phi->data->sem_forks);
	pthread_mutex_lock(&phi->data->mutex);
	phi->got_forks = 2;
	pthread_mutex_unlock(&phi->data->mutex);
	output_msg(phi, "has taken a fork");
}
