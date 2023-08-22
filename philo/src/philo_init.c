/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 12:32:34 by aloubier          #+#    #+#             */
/*   Updated: 2023/08/22 09:32:41 by aloubier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	init_philo(t_phi *phi, t_data *data)
{
	phi->data = data;
	phi->is_alive = 1;
	phi->last_meal_time = ft_get_time();
	phi->got_forks = 0;
	if (phi->data->meal_limit == -1)
		phi->meal_count = -1;
	else
		phi->meal_count = 0;
	phi->left_fork = &data->forks[phi->id];
	if (phi->id == 0)
		phi->right_fork = &data->forks[data->phi_count - 1];
	else
		phi->right_fork = &data->forks[phi->id - 1];
}

static t_phi	*create_philo(int index, t_data *data)
{
	t_phi	*phi;

	phi = (t_phi *)malloc(sizeof(t_phi));
	if (!phi)
		return (NULL);
	phi->id = index;
	init_philo(phi, data);
	return (phi);
}

static int	error_init_phi(t_data *data, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free(data->phi_array[i]);
		i++;
	}
	return (EXIT_FAILURE);
}

int	philos_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->phi_count)
	{
		data->phi_array[i] = create_philo(i, data);
		if (!data->phi_array[i])
			return (error_init_phi(data, i));
		i++;
	}
	return (EXIT_SUCCESS);
}
