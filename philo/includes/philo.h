/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 12:44:07 by aloubier          #+#    #+#             */
/*   Updated: 2023/08/22 09:47:38 by aloubier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

//init.c
int		init_data(t_data *data, char **av);
void	set_table(t_data *data);

//philo_init.c
int		philos_init(t_data *data);

//time.c
void	ft_sleep(t_phi *phi, long duration);
long	ft_timetol(t_tv time);
long	ft_get_time(void);
void	ft_philo_q(t_phi *phi);

//output.c
void	timestamp(t_tv start);
void	output_msg(t_phi *phi, char *msg);
void	output_death(t_phi *phi);
void	output_meal_count(t_data *data);

//status_check.c
int		phi_continue(t_data *data);
int		all_phi_alive(t_data *data);
int		is_phi_alive(t_phi *phi);

//meal_check.c
int		has_eaten_enough(t_phi *phi);
int		all_phi_sated(t_data *data);
void	increase_meal_count(t_phi *phi);

//threads.c
int		run_thread(t_data *data);
void	*philo_thread(void *source);

//forks.c
int		forks_init(t_data *data);
void	forks_destroy(t_data *data);
void	philo_taking_first_fork(t_phi *phi);
void	philo_taking_second_fork(t_phi *phi);
void	unlock_forks(t_phi *phi);

//philo_actions.c
void	philo_is_taking_forks(t_phi *phi);
void	philo_is_eating(t_phi *phi);
void	philo_is_sleeping(t_phi *phi);
void	philo_is_thinking(t_phi *phi);

//utils.c
int		check_input(char *arg);
long	ft_atol(const char *str);
void	ft_putstr(char *str);

//exit.c
void	cleanup_data(t_data *data);
int		error_forks_init(t_data *data, int index);
int		thread_error_exit(t_data *data, int index);

#endif
