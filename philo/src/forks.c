/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 12:32:07 by aloubier          #+#    #+#             */
/*   Updated: 2023/08/22 09:32:32 by aloubier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	forks_init(t_data *data)
{
	int	i;

	data->forks = (t_mutex *)malloc(sizeof(t_mutex) * data->phi_count);
	i = 0;
	while (i < data->phi_count)
	{
		if (pthread_mutex_init(&data->forks[i],
				NULL) != EXIT_SUCCESS)
			return (error_forks_init(data, i));
		i++;
	}
	return (EXIT_SUCCESS);
}

void	forks_destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->phi_count)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
}

void	unlock_forks(t_phi *phi)
{
	int		forks;

	pthread_mutex_lock(&phi->data->mutex);
	forks = phi->got_forks;
	pthread_mutex_unlock(&phi->data->mutex);
	if (forks == 2)
	{
		pthread_mutex_unlock(phi->left_fork);
		pthread_mutex_unlock(phi->right_fork);
	}
	else if (forks == 1)
	{
		if (phi->id % 2 == 0)
			pthread_mutex_unlock(phi->left_fork);
		else
			pthread_mutex_unlock(phi->right_fork);
	}
}

void	philo_taking_first_fork(t_phi *phi)
{
	if (phi->id % 2 == 0)
		pthread_mutex_lock(phi->left_fork);
	else
		pthread_mutex_lock(phi->right_fork);
	pthread_mutex_lock(&phi->data->mutex);
	phi->got_forks = 1;
	pthread_mutex_unlock(&phi->data->mutex);
	output_msg(phi, "has taken a fork");
}

void	philo_taking_second_fork(t_phi *phi)
{
	if (phi->id % 2 == 0)
	{
		pthread_mutex_lock(phi->right_fork);
	}
	else
	{
		pthread_mutex_lock(phi->left_fork);
	}
	pthread_mutex_lock(&phi->data->mutex);
	phi->got_forks = 2;
	pthread_mutex_unlock(&phi->data->mutex);
	output_msg(phi, "has taken a fork");
}
