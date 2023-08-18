/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meal_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 12:32:26 by aloubier          #+#    #+#             */
/*   Updated: 2023/08/15 12:32:27 by aloubier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	increase_meal_count(t_phi *phi)
{
	sem_wait(phi->data->sem_data);
	if (phi->meal_count != -1)
		phi->meal_count++;
	sem_post(phi->data->sem_data);
}

int	is_phi_sated(t_phi *phi)
{
	sem_wait(phi->data->sem_data);
	// printf("phi->data->meal_limit = %i\n", phi->data->meal_limit);
	// printf("phi->meal_count = %i\n", phi->meal_count);
	if (phi->data->meal_limit == -1)
	{
		sem_post(phi->data->sem_data);
		return (0);
	}
	if (phi->meal_count < phi->data->meal_limit)
	{
		sem_post(phi->data->sem_data);
		return (0);
	}
	if (phi->meal_count == phi->data->meal_limit)
	{
		// printf("equal");
		// printf("mc = %i \n", phi->meal_count);
		phi->meal_count++;
		phi->data->sated++;
	}
	sem_post(phi->data->sem_data);
	return (1);
}

int	all_phi_sated(t_data *data)
{
	int		i;
	int		sated;

	i = 0;
	sated = 1;
	while (i < data->phi_count)
	{
		sated = is_phi_sated(&data->phi_array[i]);
		if (sated == 0)
			return (0);
		i++;
	}
	return (sated);
}
