/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 23:44:52 by aloubier          #+#    #+#             */
/*   Updated: 2023/08/12 23:44:53 by aloubier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_create_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->phi_count)
	{
		pthread_create(&data->phi_array[i]->t_id, NULL, &philo_thread, data->phi_array[i]);
		i++;
	}
}

void	ft_join_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->phi_count)
	{
		pthread_join(data->phi_array[i]->t_id, NULL);
		i++;
	}
}
