/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 23:44:58 by aloubier          #+#    #+#             */
/*   Updated: 2023/08/12 23:44:59 by aloubier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_sleep(t_phi *phi, long duration)
{
	long	start;

	start = ft_get_time();
	if (duration < 10)
	{
		return ;
	}
	while (ft_get_time() - start < duration && phi_continue(phi->data))
	{
		usleep(10);
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
