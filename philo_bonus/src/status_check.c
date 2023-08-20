/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 23:44:44 by aloubier          #+#    #+#             */
/*   Updated: 2023/08/21 01:24:36 by aloubier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_last_meal(t_phi *phi)
{
	if (ft_get_time() - phi->last_meal_time >= phi->data->ttd)
	{
		if (phi->data->alive != 0)
			output_death(phi);
		return (0);
	}
	return (1);
}

int	phi_continue(t_phi *phi)
{
	t_data	*data;

	data = phi->data;
	sem_wait(data->sem_data);
	if (ft_get_time() - phi->last_meal_time >= phi->data->ttd)
	{
		output_death(phi);
		sem_post(data->sem_death);
		sem_post(data->sem_data);
		return (0);
	}
	if (data->meal_limit != -1 && phi->is_sated == 0 
		&& phi->meal_count >= data->meal_limit)
	{
		sem_post(data->sem_sated);
		phi->is_sated = 1;
	}
	sem_post(data->sem_data);
	return (1);
}
