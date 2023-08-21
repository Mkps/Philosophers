/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 12:32:42 by aloubier          #+#    #+#             */
/*   Updated: 2023/08/21 04:10:56 by aloubier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_is_taking_forks(t_phi *phi)
{
	if (phi->data->phi_count <= 1)
	{
		ft_sleep(phi, phi->data->ttd + 10);
		sem_wait(phi->data->sem_data);
		phi->got_forks = 0;
		sem_post(phi->data->sem_data);
		return ;
	}
	sem_wait(phi->data->sem_forks);
	sem_wait(phi->data->sem_data);
	phi->got_forks = 1;
	sem_post(phi->data->sem_data);
	output_msg(phi, "has taken a fork");
	sem_wait(phi->data->sem_forks);
	sem_wait(phi->data->sem_data);
	phi->got_forks = 2;
	sem_post(phi->data->sem_data);
	output_msg(phi, "has taken a fork");
}

void	philo_is_eating(t_phi *phi)
{
	if (phi->got_forks == 2)
		output_msg(phi, "is eating");
	sem_wait(phi->data->sem_data);
	phi->last_meal_time = ft_get_time();
	sem_post(phi->data->sem_data);
	ft_sleep(phi, phi->data->tte);
	sem_post(phi->data->sem_forks);
	sem_post(phi->data->sem_forks);
	sem_wait(phi->data->sem_data);
	phi->got_forks = 0;
	phi->meal_count++;
	sem_post(phi->data->sem_data);
}

void	philo_is_sleeping(t_phi *phi)
{
	output_msg(phi, "is sleeping");
	ft_sleep(phi, phi->data->tts);
}

void	philo_is_thinking(t_phi *phi)
{
	long	big_think;

	output_msg(phi, "is thinking");
	big_think = (phi->data->ttd - (phi->data->tte + phi->data->tts));
	if (big_think >= 200)
		usleep(200);
}
