/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 23:44:25 by aloubier          #+#    #+#             */
/*   Updated: 2023/08/15 12:37:48 by aloubier         ###   ########.fr       */
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
		printf("[time to sleep] Optional: [Number of meal]\n");
		exit(1);
	}
	i = 1;
	while (i < ac)
	{
		if (check_input(av[i]))
			exit (1);
		i++;
	}
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
