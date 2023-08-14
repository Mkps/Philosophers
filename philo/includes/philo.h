#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <limits.h>
# include <pthread.h>
# include <sys/wait.h>
# include <sys/time.h>
# include "philo_struct.h"

void	philos_init(t_data *data);
void	ft_sleep(t_phi *phi, long duration);
long	ft_timetol(t_tv time);
long	ft_get_time(void);
void	timestamp(t_tv start);
void	output_msg(t_phi *phi, char *msg);
void	output_death(t_phi *phi);
long	ft_timetol(t_tv time);
int		phi_continue(t_data *data);
int		all_phi_alive(t_data *data);
int		is_phi_alive(t_phi *phi);
int		has_eaten_enough(t_phi *phi);
int		all_phi_sated(t_data *data);
void	increase_meal_count(t_phi *phi);
void	ft_create_thread(t_data *data);
void	ft_join_thread(t_data *data);
void	*philo_thread(void *source);
void	forks_init(t_data *data);
void	forks_destroy(t_data *data);
void	philo_taking_first_fork(t_phi *phi);
void	philo_taking_second_fork(t_phi *phi);
void	unlock_forks(t_phi *phi);

#endif
