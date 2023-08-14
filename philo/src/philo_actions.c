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
