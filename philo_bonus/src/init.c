/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 12:32:19 by aloubier          #+#    #+#             */
/*   Updated: 2023/08/21 01:35:39 by aloubier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <semaphore.h>

void	init_error(t_data *data)
{
	printf("Error initializing data.\n");
	if (data->sem_data)
		sem_close(data->sem_data);
	if (data->sem_death)
		sem_close(data->sem_death);
	if (data->sem_continue)
		sem_close(data->sem_continue);
	if (data->sem_output)
		sem_close(data->sem_output);
	if (data->phi_array)
		free(data->phi_array);
	exit (1);
}

int	error_exit(t_data *data)
{
	if (data->phi_array)
		free(data->phi_array);
	return (0);
}

void	unlink_semaphores(void)
{
	sem_unlink("/sem_forks");
	sem_unlink("/sem_data");
	sem_unlink("/sem_output");
	sem_unlink("/sem_continue");
	sem_unlink("/sem_death");
	sem_unlink("/sem_sated");
}

int	init_semaphores(t_data *data)
{
	unlink_semaphores();
	data->sem_forks = sem_open("/sem_forks", O_CREAT, 0600, data->phi_count);
	if (data->sem_forks == SEM_FAILED)
		error_exit(data);
	data->sem_data = sem_open("/sem_data", O_CREAT, 0600, 1);
	if (data->sem_data == SEM_FAILED)
		error_exit(data);
	data->sem_output = sem_open("/sem_output", O_CREAT, 0600, 1);
	if (data->sem_output == SEM_FAILED)
		error_exit(data);
	data->sem_continue = sem_open("sem_continue", O_CREAT, 0600, 1);
	if (data->sem_continue == SEM_FAILED)
		error_exit(data);
	data->sem_death = sem_open("/sem_death", O_CREAT, 0600, data->phi_count);
	if (data->sem_death == SEM_FAILED)
		error_exit(data);
	data->sem_sated = sem_open("/sem_sated", O_CREAT, 0600, data->phi_count);
	if (data->sem_sated == SEM_FAILED)
		error_exit(data);
	return (0);
}

void	init_data(t_data *data, char **av)
{
	data->alive = 1;
	data->sated = 0;
	data->continuer = 1;
	data->phi_count = ft_atol(av[1]);
	data->ttd = ft_atol(av[2]);
	data->tte = ft_atol(av[3]);
	data->tts = ft_atol(av[4]);
	data->meal_limit = -1;
	data->start_time = ft_get_time() + (10 * data->phi_count);
	init_semaphores(data);
	if (av[5] != NULL)
		data->meal_limit = ft_atol(av[5]);
	data->phi_array = (t_phi *)malloc(sizeof(t_phi) * data->phi_count);
	if (!data->phi_array)
		init_error(data);
}
