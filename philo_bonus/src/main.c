/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 23:44:25 by aloubier          #+#    #+#             */
/*   Updated: 2023/08/21 21:18:12 by aloubier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int		ft_spawn_philo(t_data *data);

void	check_args(int ac, char **av)
{
	int	i;

	if (ac != 5 && ac != 6)
	{
		printf("Incorrect parameter number. Correct use is:\n");
		printf ("./philo [nb_of_philosophers][time until death][time to eat]");
		printf("[time to sleep] Optional: [Number of meal]\n");
		exit(0);
	}
	i = 1;
	while (i < ac)
	{
		if (check_input(av[i]))
			exit (1);
		i++;
	}
}

int	ft_get_child(t_data *data, t_phi phi)
{
	int	phi_exit_code;
	int	exit_code;

	if (phi.pid && waitpid(phi.pid, &phi_exit_code, WNOHANG) != 0)
	{
		if (WIFEXITED(phi_exit_code))
		{
			exit_code = WEXITSTATUS(phi_exit_code);
			if (exit_code == PHI_DEAD)
				return (kill_all_phi(data, 1));
			if (exit_code == ERR_SEM || exit_code == ERR_PTHREAD)
				return (kill_all_phi(data, -1));
			if (exit_code == PHI_SATED)
			{
				data->sated += 1;
				return (1);
			}
		}
	}
	return (0);
}

int	stop_process(t_data *data)
{
	int	i;
	int	exit_code;

	while (data_continue(data))
	{
		i = 0;
		while (i < data->phi_count)
		{
			exit_code = ft_get_child(data, data->phi_array[i]);
			if (exit_code == 1 || exit_code == -1)
			{
				sem_wait(data->sem_continue);
				data->continuer = 0;
				sem_post(data->sem_sated);
				sem_post(data->sem_death);
				sem_post(data->sem_continue);
				return (exit_code);
			}
			i++;
		}
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		exit_code;

	exit_code = 0;
	check_args(ac, av);
	init_data(&data, av);
	philos_init(&data);
	if (ft_spawn_philo(&data) == EXIT_FAILURE)
		return (error_exit(&data));
	exit_code = stop_process(&data);
	cleanup_data(&data);
	return (exit_code);
}
