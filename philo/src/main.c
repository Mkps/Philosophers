/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 23:44:25 by aloubier          #+#    #+#             */
/*   Updated: 2023/08/22 09:34:50 by aloubier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	check_args(int ac, char **av)
{
	int	i;

	if (ac != 5 && ac != 6)
	{
		printf("Incorrect parameter number. Correct use is:\n");
		printf ("./philo [nb_of_philosophers][time until death][time to eat]");
		printf("[time to sleep] \nOptional: [Number of meal]\n");
		exit(1);
	}
	i = 1;
	while (i < ac)
	{
		if (check_input(av[i]))
			exit (1);
		i++;
	}
	if (ac == 6)
	{
		if (ft_atol(av[5]) == 0)
		{
			exit (0);
		}
	}
}

int	main(int ac, char **av)
{
	t_data	data;

	check_args(ac, av);
	if (init_data(&data, av) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	set_table(&data);
	if (run_thread(&data) != EXIT_SUCCESS)
	{
		cleanup_data(&data);
		return (EXIT_FAILURE);
	}
	cleanup_data(&data);
	return (EXIT_SUCCESS);
}
