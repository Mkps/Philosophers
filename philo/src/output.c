/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 23:44:36 by aloubier          #+#    #+#             */
/*   Updated: 2023/08/12 23:44:38 by aloubier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	timestamp(t_tv start)
{
	t_tv	end;

	gettimeofday(&end, NULL);
	printf("%ld ", (ft_timetol(end) - ft_timetol(start)));
}

void	output_msg(t_phi *phi, char *msg)
{
	int	alive;
	int	sated;

	pthread_mutex_lock(&phi->data->mutex);
	alive = phi->data->alive;
	sated = phi->data->sated;
	pthread_mutex_unlock(&phi->data->mutex);
	if (alive && !sated)
	{
		pthread_mutex_lock(&phi->data->output);
		timestamp(phi->data->start_time);
		printf("%i %s\n", phi->id + 1, msg);
		pthread_mutex_unlock(&phi->data->output);
	}
}

void	output_death(t_phi *phi)
{
	pthread_mutex_lock(&phi->data->output);
	timestamp(phi->data->start_time);
	printf("%i died\n", phi->id + 1);
	pthread_mutex_unlock(&phi->data->output);
}
