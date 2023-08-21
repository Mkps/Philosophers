/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 12:44:07 by aloubier          #+#    #+#             */
/*   Updated: 2023/08/21 16:23:08 by aloubier         ###   ########.fr       */
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
# include <fcntl.h>
# include "philo_struct.h"
# include <signal.h>

//exit.c
int		kill_all_phi(t_data *data, int exit_code);
void	cleanup_data(t_data *data);
void	child_exit(t_data *data, int exit_code);

//init.c
void	init_data(t_data *data, char **av);
void	unlink_semaphores(void);
int		error_exit(t_data *data);
void	init_error(t_data *data);

//output.c
void	output_msg(t_phi *phi, char *msg);
void	output_death(t_phi *phi);
void	output_meal_count(t_data *data);
void	timestamp(t_phi *phi);

//philo_actions.c
void	philo_is_taking_forks(t_phi *phi);
void	philo_is_eating(t_phi *phi);
void	philo_is_sleeping(t_phi *phi);
void	philo_is_thinking(t_phi *phi);

//philo_init.c
void	philos_init(t_data *data);

//philo_process.c
void	philo_routine(t_phi *phi);
void	*overseer_thread(void *source);
int		ft_spawn_philo(t_data *data);
void	run_process(t_data *data);

//status_check.c
int		status_check(t_data *data);
int		phi_continue(t_phi *phi);

//time.c
void	wait_start(t_data *data);
void	ft_philo_q(t_phi *phi);
long	ft_get_time(void);
long	ft_timetol(t_tv time);
void	ft_sleep(t_phi *phi, long duration);

//utils.c
int		check_input(char *arg);
long	ft_atol(const char *str);
int		data_continue(t_data *data);

#endif
