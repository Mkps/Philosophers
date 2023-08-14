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

void	philo_is_taking_forks(t_phi *phi)
{
	if (phi->data->phi_count <= 1)
	{
		ft_sleep(phi, phi->data->ttd);
		phi->got_forks = 0;
		return ;
	}
	philo_taking_first_fork(phi);
	philo_taking_second_fork(phi);
}

void	philo_is_eating(t_phi *phi)
{
	output_msg(phi, "is eating");
	pthread_mutex_lock(&phi->data->mutex);
	phi->last_meal_time = ft_get_time();
	pthread_mutex_unlock(&phi->data->mutex);
	increase_meal_count(phi);
	ft_sleep(phi, phi->data->tte);
	unlock_forks(phi);
	pthread_mutex_lock(&phi->data->mutex);
	phi->got_forks = 0;
	pthread_mutex_unlock(&phi->data->mutex);
}

void	philo_is_sleeping(t_phi *phi)
{
	output_msg(phi, "is sleeping");
	ft_sleep(phi, phi->data->tts);
}

void	philo_is_thinking(t_phi *phi)
{
	long big_think;

	output_msg(phi, "is thinking");
	big_think = (phi->data->ttd - (phi->data->tte + phi->data->tts));
	ft_sleep(phi, big_think / 2);
}

void	*overseer_thread(void *source)
{
	t_phi	*overseer;

	overseer = (t_phi *)source;
	while (1)
	{
		if (!phi_continue(overseer->data))
			break;
		usleep(50);
	}
	return (0);
}

void	*philo_thread(void *source)
{
	t_phi *phi;
	t_data	*data;
	phi = (t_phi *)source;
	data = phi->data; 
	while (phi_continue(data))
	{
		if (phi_continue(data))
			philo_is_taking_forks(phi);
		if (phi_continue(data))
			philo_is_eating(phi);
		if (phi_continue(data))
			philo_is_sleeping(phi);
		if (phi_continue(data))
			philo_is_thinking(phi);
	}
	unlock_forks(phi);
	return(0);
}

void	check_args(int ac, char **av)
{
	(void)av;
	if (ac != 5 && ac != 6)
		exit(1);
}

void	init_data(t_data *data, char **av)
{
	t_mutex mutex;
	t_mutex	output;

	pthread_mutex_init(&mutex, NULL);
	pthread_mutex_init(&output, NULL);
	// data = (t_data *)malloc(sizeof(t_data));
	data->mutex = mutex;
	data->output = output;
	data->alive = 1;
	data->sated = 0;
	gettimeofday(&data->start_time, NULL);
	data->phi_count = atoi(av[1]);
	data->ttd = atol(av[2]);
	data->tte = atoi(av[3]);
	data->tts = atol(av[4]);
	if (av[5] != NULL)
		data->meal_limit = atoi(av[5]);
	else
		data->meal_limit = -1;
	data->phi_array = (t_phi **)malloc(sizeof(t_phi *) * data->phi_count);
}

void	free_philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->phi_count)
		free(data->phi_array[i++]);
}

void	output_meal_count(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->phi_count)
	{
		if (data->phi_array[i]->meal_count >= 0)
		{
			timestamp(data->start_time);	
			printf("%i has eaten %i times\n", i + 1, data->phi_array[i]->meal_count);
		}
		i++;
	}
}

void	set_table(t_data *data)
{
	data->overseer = (t_phi*)malloc(sizeof(t_phi));
	data->overseer->data = data;
	forks_init(data);
	philos_init(data);
}

int	main(int ac, char **av)
{
	t_data	data;

	check_args(ac, av);
	init_data(&data, av);
	set_table(&data);
	pthread_create(&data.overseer->t_id, NULL, &overseer_thread, data.overseer);
	ft_create_thread(&data);
	ft_join_thread(&data);
	pthread_join(data.overseer->t_id, NULL);
	forks_destroy(&data);
	pthread_mutex_destroy(&data.mutex);
	pthread_mutex_destroy(&data.output);
	// output_meal_count(&data);
	free_philosophers(&data);
	free(data.overseer);
	free(data.phi_array);
	return (0);
}
