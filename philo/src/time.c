/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 23:44:58 by aloubier          #+#    #+#             */
/*   Updated: 2023/08/15 12:47:14 by aloubier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_sleep(t_phi *phi, long duration)
{
	long	start;

	start = ft_get_time();
	if (duration < 10)
	{
		usleep(100);
		return ;
	}
	while (ft_get_time() - start < duration && phi_continue(phi->data))
	{
		usleep(100);
	}
}

long	ft_timetol(t_tv time)
{
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

long	ft_get_time(void)
{
	t_tv	time;

	gettimeofday(&time, NULL);
	return (ft_timetol(time));
}

void	ft_philo_q(t_phi *phi)
{
	t_data	*data;

	data = phi->data; 
	if (data->phi_count % 2 == 0)
	{
		if (phi->id % 2 != 0)
		{
			ft_sleep(phi, 10);
			output_msg(phi, "is thinking");
		}
	}
	else if (data->phi_count % 2 != 0)
	{
		if (phi->id % 2 == 0)
		{
			ft_sleep(phi, 10);
			output_msg(phi, "is thinking");
		}
	}
}
