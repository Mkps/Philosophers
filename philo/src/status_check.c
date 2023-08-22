/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 23:44:44 by aloubier          #+#    #+#             */
/*   Updated: 2023/08/22 09:32:43 by aloubier         ###   ########.fr       */
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
		alive = is_phi_alive(data->phi_array[i]);
		if (alive == 0)
			return (0);
		i++;
	}
	return (alive);
}

int	is_phi_alive(t_phi *phi)
{
	pthread_mutex_lock(&phi->data->mutex);
	if (phi->is_alive == 0)
	{
		phi->data->alive = 0;
		pthread_mutex_unlock(&phi->data->mutex);
		return (0);
	}
	if (check_last_meal(phi) == 0)
	{
		phi->is_alive = 0;
		phi->data->alive = 0;
		pthread_mutex_unlock(&phi->data->mutex);
		return (0);
	}
	pthread_mutex_unlock(&phi->data->mutex);
	return (1);
}

int	phi_continue(t_data *data)
{
	if (all_phi_alive(data) == 1 && all_phi_sated(data) == 0)
		return (1);
	return (0);
}
