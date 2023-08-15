/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 12:32:34 by aloubier          #+#    #+#             */
/*   Updated: 2023/08/15 12:32:35 by aloubier         ###   ########.fr       */
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
}

static t_phi	*create_philo(int index, t_data *data)
{
	t_phi	*phi;

	phi = (t_phi *)malloc(sizeof(t_phi));
	phi->id = index;
	init_philo(phi, data);
	return (phi);
}

void	philos_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->phi_count)
	{
		data->phi_array[i] = create_philo(i, data);
		i++;
	}
}
