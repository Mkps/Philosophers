/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 12:31:58 by aloubier          #+#    #+#             */
/*   Updated: 2023/08/15 12:32:14 by aloubier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// static void	free_philosophers(t_data *data)
// {
// 	int	i;
//
// 	i = 0;
// 	while (i < data->phi_count)
// 		free(data->phi_array[i++]);
// }
//
void	kill_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->phi_count)
	{
		i++;
		kill(data->phi_array[i++].pid, SIGKILL);
	}
}
void	cleanup_data(t_data *data)
{
	forks_destroy(data);
	// sem_close(data->sem_output);
	// free_philosophers(data);
	sem_close(data->sem_output);
	sem_close(data->sem_continue);
	sem_close(data->sem_data);
	free(data->phi_array);
}
