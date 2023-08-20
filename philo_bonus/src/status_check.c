/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 23:44:44 by aloubier          #+#    #+#             */
/*   Updated: 2023/08/15 12:35:58 by aloubier         ###   ########.fr       */
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

int	all_phi_alive(t_data *data)
{
	int		i;
	int		alive;

	i = 0;
	alive = 1;
	while (i < data->phi_count)
	{
		alive = is_phi_alive(&data->phi_array[i]);
		if (alive == 0)
			return (0);
		i++;
	}
	return (alive);
}

int	is_phi_alive(t_phi *phi)
{
	sem_wait(phi->data->sem_data);
	if (phi->is_alive == 0)
	{
		phi->data->alive = 0;
		sem_post(phi->data->sem_data);
		return (0);
	}
	if (check_last_meal(phi) == 0)
	{
		// phi->is_alive = 0;
		phi->data->alive = 0;
		sem_post(phi->data->sem_data);
		return (0);
	}
	sem_post(phi->data->sem_data);
	return (1);
}

int	phi_continue(t_phi *phi)
{
	t_data *data;

	data = phi->data;
	sem_wait(data->sem_data);
	if (ft_get_time() - phi->last_meal_time >= phi->data->ttd)
	{
		output_death(phi);
		sem_post(data->sem_death);
		sem_post(data->sem_data);
		return (0);
	}
	if (data->meal_limit != -1 && phi->is_sated == 0 && phi->meal_count >= data->meal_limit)
	{
		sem_post(data->sem_sated);
		phi->is_sated = 1;
	}
	sem_post(data->sem_data);
	return (1);
}
