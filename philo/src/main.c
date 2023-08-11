#include "../includes/philo.h"
#include <pthread.h>


void	ft_sleep(t_phi *phi, long duration)
{
	long	start;

	start = ft_get_time();
	while (ft_get_time() - start < duration && is_phi_alive(phi) != 0)
	{
		usleep(10);
	}
}

void	init_philo(t_phi *phi, t_data *data)
{
	phi->data = data;
	phi->is_alive = 1;
	phi->last_meal_time = ft_get_time();
	phi->got_forks = 0;
	if (phi->data->meal_limit == -1)
		phi->meal_count = -1;
	else
	 	phi->meal_count = 0;
	phi->left_fork = &data->forks[phi->id];
	if (phi->id == 0)
		phi->right_fork = &data->forks[data->phi_count - 1];
	else
		phi->right_fork = &data->forks[phi->id - 1];

}

t_phi	*create_philo(int index, t_data *data)
{
	t_phi	*phi;


	phi = (t_phi *)malloc(sizeof(t_phi));
	phi->id = index;
	init_philo(phi, data);
	return (phi);
}
void	unlock_forks(t_phi *phi)
{
	int		forks;

	pthread_mutex_lock(&phi->data->mutex);
	forks = phi->got_forks;
	pthread_mutex_unlock(&phi->data->mutex);
	if (forks == 2)
	{
		pthread_mutex_unlock(phi->left_fork);
		pthread_mutex_unlock(phi->right_fork);
	}
	else if (forks == 1)
	{
		if (phi->id % 2 == 0)
			pthread_mutex_unlock(phi->left_fork);
		else
			pthread_mutex_unlock(phi->right_fork);
	}
}

int	check_last_meal(t_phi *phi)
{
	if (ft_get_time() - phi->last_meal_time > phi->data->ttd)
	{
		pthread_mutex_unlock(&phi->data->mutex);
		output_msg(phi, "has died");
		pthread_mutex_lock(&phi->data->mutex);
		phi->data->alive = 0;
		return (0);
	}
	return (1);
}

int	all_phi_alive(t_data *data)
{
	int		i;
	int		alive;

	i = 0;
	alive = 1;
	while (i < data->phi_count)
	{
		alive = is_phi_alive(data->phi_array[i]);
		if (alive == 0)
			return (0);
		i++;
	}
	return (alive);
}

int	is_phi_alive(t_phi *phi)
{
	pthread_mutex_lock(&phi->data->mutex);
	if (phi->is_alive == 0)	
	{
		phi->data->alive = 0;
		pthread_mutex_unlock(&phi->data->mutex);
		return (0);
	}
	if (check_last_meal(phi) == 0)
	{
		phi->is_alive = 0;
		phi->data->alive = 0;
		pthread_mutex_unlock(&phi->data->mutex);
		return (0);
	}
	pthread_mutex_unlock(&phi->data->mutex);
	return (1);
}

void	philo_taking_first_fork(t_phi *phi)
{
	if (phi->id % 2 == 0)
		pthread_mutex_lock(phi->left_fork);
	else
		pthread_mutex_lock(phi->right_fork);
	pthread_mutex_lock(&phi->data->mutex);
	phi->got_forks = 1;
	pthread_mutex_unlock(&phi->data->mutex);
	output_msg(phi, "has taken a fork");	
}

void	philo_taking_second_fork(t_phi *phi)
{
	if (phi->id % 2 == 0)
	{
		if (pthread_mutex_lock(phi->right_fork) != 0)
			pthread_mutex_unlock(phi->left_fork);
	}
	else
	{
		if (pthread_mutex_lock(phi->left_fork) != 0)
			pthread_mutex_unlock(phi->right_fork);
	}
	pthread_mutex_lock(&phi->data->mutex);
	phi->got_forks = 2;
	pthread_mutex_unlock(&phi->data->mutex);
	output_msg(phi, "has taken a fork");	
}

void	philo_is_taking_forks(t_phi *phi)
{
	if (phi->data->phi_count <= 1)
	{
		ft_sleep(phi, phi->data->ttd);
		pthread_mutex_lock(&phi->data->mutex);
		phi->is_alive = 0;
		pthread_mutex_unlock(&phi->data->mutex);
		return ;
	}
	philo_taking_first_fork(phi);
	philo_taking_second_fork(phi);
}

void	increase_meal_count(t_phi *phi)
{
	pthread_mutex_lock(&phi->data->mutex);
	if (phi->meal_count != -1)
		phi->meal_count++;
	pthread_mutex_unlock(&phi->data->mutex);
}

void	philo_is_eating(t_phi *phi)
{
	output_msg(phi, "is eating");
	pthread_mutex_lock(&phi->data->mutex);
	phi->last_meal_time = ft_get_time();
	pthread_mutex_unlock(&phi->data->mutex);
	ft_sleep(phi, phi->data->tte);
	increase_meal_count(phi);
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
	output_msg(phi, "is thinking");
}

int	is_phi_sated(t_phi *phi)
{
	pthread_mutex_lock(&phi->data->mutex);
	if (phi->data->meal_limit == -1)	
	{
		pthread_mutex_unlock(&phi->data->mutex);
		return (0);
	}
	if (phi->meal_count < phi->data->meal_limit)
	{
		pthread_mutex_unlock(&phi->data->mutex);
		return (0);
	}
	pthread_mutex_unlock(&phi->data->mutex);
	return (1);
}
int	phi_continue(t_data *data)
{
	if (all_phi_alive(data) == 1 && all_phi_sated(data) == 0)
		return (1);
	return (0);
}

int	all_phi_sated(t_data *data)
{
	int		i;
	int		sated;

	i = 0;
	sated = 1;
	while (i < data->phi_count)
	{
		sated = is_phi_sated(data->phi_array[i]);
		if (sated == 0)
			return (0);
		i++;
	}
	return (sated);
}
void	*overseer_thread(void *source)
{
	t_phi	*overseer;
	int		alive;
	int		sated;

	alive = 1;
	sated = 0;
	overseer = (t_phi *)source;
	while (1)
	{
		alive = all_phi_alive(overseer->data);
		sated = all_phi_sated(overseer->data);
		if (!alive || sated)
			break;
		usleep(10);
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

void	forks_init(t_data *data)
{
	int i;

	data->forks = (mutex_t *)malloc(sizeof(mutex_t) * data->phi_count);
	i = 0;
	while (i < data->phi_count)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
}
void	forks_destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->phi_count)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
}
void	check_args(int ac, char **av)
{
	(void)av;
	if (ac != 5 && ac != 6)
		exit(1);
}

void	init_data(t_data *data, char **av)
{

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

void	philos_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->phi_count)
	{
		data->phi_array[i] = create_philo(i, data);
		i++;
	}
}

void	ft_create_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->phi_count)
	{
		pthread_create(&data->phi_array[i]->t_id, NULL, &philo_thread, data->phi_array[i]);
		i++;
	}
}
void	ft_join_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->phi_count)
	{
		pthread_join(data->phi_array[i]->t_id, NULL);
		i++;
	}
}
int	main(int ac, char **av)
{
	int		i;
	t_data	*data;
	t_phi	*overseer;
	mutex_t mutex;
	mutex_t	output;

	pthread_mutex_init(&mutex, NULL);
	pthread_mutex_init(&output, NULL);
	check_args(ac, av);
	data = (t_data *)malloc(sizeof(t_data));
	data->mutex = mutex;
	data->output = output;
	overseer = (t_phi*)malloc(sizeof(t_phi));
	overseer->data = data;
	init_data(data, av);
	forks_init(data);
	philos_init(data);
	pthread_create(&overseer->t_id, NULL, &overseer_thread, overseer);
	ft_create_thread(data);
	pthread_join(overseer->t_id, NULL);
	ft_join_thread(data);
	forks_destroy(data);
	i = 0;
	while (i < data->phi_count)
	{
		if (data->phi_array[i]->meal_count >= 0)
		{
			timestamp(data->start_time);	
			printf("%i has eaten %i times\n", i + 1, data->phi_array[i]->meal_count);
		}
		free(data->phi_array[i]);
		i++;
	}
	pthread_mutex_destroy(&mutex);
	pthread_mutex_destroy(&output);
	free(overseer);
	free(data->phi_array);
	free(data);
	return (0);
}
