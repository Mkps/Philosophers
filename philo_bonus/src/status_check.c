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
		// printf("time is %ld last meal is %ld result is %ld\n", ft_get_time(), phi->last_meal_time, ft_get_time() - phi->last_meal_time);
		// printf("heded?");
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
		// printf("ded of dedness");
		phi->data->alive = 0;
		sem_post(phi->data->sem_data);
		return (0);
	}
	if (check_last_meal(phi) == 0)
	{
		// printf("ded of nofoodness");
		phi->is_alive = 0;
		phi->data->alive = 0;
		sem_post(phi->data->sem_data);
		return (0);
	}
	sem_post(phi->data->sem_data);
	return (1);
}

int	phi_continue(t_phi *phi)
{
	int	alive;
	int	sated;

	alive = is_phi_alive(phi);
	sated = is_phi_sated(phi);
	// if (alive == 1 && sated == 0)
	// 	return (1);
	if (alive == 0)
	{
		// sem_post(phi->data->sem_continue);
		phi->is_alive = 0;
		return (0);
	}
	else if (sated == 1)
	{
		if (phi->data->sated == 1)
		{
			// printf("NOMNOMNOM %i %i\n", phi->id + 1, phi->data->sated);
			// sem_post(phi->data->sem_continue);
			// free(phi->data->phi_array);
			// sem_close(phi->data->sem_continue);
			// sem_close(phi->data->sem_output);
			// sem_close(phi->data->sem_data);
			// sem_close(phi->data->sem_forks);
			// sem_post(phi->data->sem_continue);
			// exit (0);
			return (0);
		}
	}
	// printf("nocontinue");
	// free(phi->data->phi_array);
	// sem_post(phi->data->sem_continue);
	return (1);
}
