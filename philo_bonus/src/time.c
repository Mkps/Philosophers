/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 23:44:58 by aloubier          #+#    #+#             */
/*   Updated: 2023/08/21 01:30:44 by aloubier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_sleep(t_phi *phi, long duration)
{
	long	start;

	(void)phi;
	start = ft_get_time();
	if (duration < 10)
	{
		return ;
	}
	while (ft_get_time() - start < duration)
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
			usleep(200);
			output_msg(phi, "is thinking");
		}
	}
	else if (data->phi_count % 2 != 0)
	{
		if (phi->id % 2 == 0)
		{
			usleep(200);
			output_msg(phi, "is thinking");
		}
	}
}

void	wait_start(t_data *data)
{
	while (ft_get_time() < data->start_time)
		continue ;
}
