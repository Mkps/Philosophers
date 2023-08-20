/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 23:44:36 by aloubier          #+#    #+#             */
/*   Updated: 2023/08/21 01:24:59 by aloubier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	timestamp(t_phi *phi)
{
	t_tv	end;

	gettimeofday(&end, NULL);
	printf("%ld ", (ft_timetol(end) - phi->data->start_time));
}

void	output_msg(t_phi *phi, char *msg)
{
	int	alive;
	int	sated;

	sem_wait(phi->data->sem_data);
	alive = phi->data->alive;
	sated = phi->data->sated;
	sem_post(phi->data->sem_data);
	if (alive && !sated)
	{
		sem_wait(phi->data->sem_output);
		timestamp(phi);
		printf("%i %s\n", phi->id + 1, msg);
		sem_post(phi->data->sem_output);
	}
}

void	output_death(t_phi *phi)
{
	sem_wait(phi->data->sem_output);
	timestamp(phi);
	printf("%i died\n", phi->id + 1);
	phi->is_alive = 0;
	return ;
}

void	output_meal_count(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->phi_count)
	{
		if (data->phi_array[i].meal_count >= 0)
		{
			timestamp(&data->phi_array[0]);
			printf("%i has eaten %i times\n", i + 1, 
				data->phi_array[i].meal_count);
		}
		i++;
	}
}
