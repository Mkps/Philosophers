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

void	unlock_forks(t_phi *phi)
{
	int		forks;

	sem_wait(phi->data->sem_data);
	forks = phi->got_forks;
	sem_post(phi->data->sem_data);
	if (forks == 2)
	{
		sem_post(phi->data->sem_forks);
		sem_post(phi->data->sem_forks);
	}
	else if (forks == 1)
	{
		sem_post(phi->data->sem_forks);
	}
}

void	philo_taking_first_fork(t_phi *phi)
{
	sem_wait(phi->data->sem_forks);
	sem_wait(phi->data->sem_data);
	phi->got_forks = 1;
	sem_post(phi->data->sem_data);
	output_msg(phi, "has taken a fork");
}

void	philo_taking_second_fork(t_phi *phi)
{
	sem_wait(phi->data->sem_forks);
	sem_wait(phi->data->sem_data);
	phi->got_forks = 2;
	sem_post(phi->data->sem_data);
	output_msg(phi, "has taken a fork");
}
