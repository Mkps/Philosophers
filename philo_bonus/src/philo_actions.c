/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 12:32:42 by aloubier          #+#    #+#             */
/*   Updated: 2023/08/15 12:37:34 by aloubier         ###   ########.fr       */
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
	philo_taking_first_fork(phi);
	philo_taking_second_fork(phi);
}

void	philo_is_eating(t_phi *phi)
{
	if (phi->got_forks == 2)
		output_msg(phi, "is eating");
	sem_wait(phi->data->sem_data);
	phi->last_meal_time = ft_get_time();
	sem_post(phi->data->sem_data);
	ft_sleep(phi, phi->data->tte);
	unlock_forks(phi);
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
