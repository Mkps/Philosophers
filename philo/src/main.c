/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 23:44:25 by aloubier          #+#    #+#             */
/*   Updated: 2023/08/12 23:44:30 by aloubier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	check_args(int ac, char **av)
{
	(void)av;
	if (ac != 5 && ac != 6)
		exit(1);
}

void	free_philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->phi_count)
		free(data->phi_array[i++]);
}

void	cleanup_data(t_data *data)
{
	forks_destroy(data);
	pthread_mutex_destroy(&data->mutex);
	pthread_mutex_destroy(&data->output);
	free_philosophers(data);
	free(data->overseer);
	free(data->phi_array);
}
int	main(int ac, char **av)
{
	t_data	data;

	check_args(ac, av);
	init_data(&data, av);
	set_table(&data);
	run_thread(&data);
	cleanup_data(&data);
	return (0);
}
