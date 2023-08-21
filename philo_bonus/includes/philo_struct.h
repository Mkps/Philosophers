/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 12:43:57 by aloubier          #+#    #+#             */
/*   Updated: 2023/08/21 04:15:33 by aloubier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_STRUCT_H
# define PHILO_STRUCT_H

# include <pthread.h>
# include <semaphore.h>
# include <unistd.h>

typedef pthread_mutex_t	t_mutex;
typedef struct timeval	t_tv;

# define ERR_PTHREAD	-2
# define ERR_SEM 		-3
# define PHI_DEAD		2
# define PHI_SATED		3

typedef struct s_phi {
	pid_t			pid;
	int				is_alive;
	int				is_sated;
	int				id;
	int				meal_count;
	int				got_forks;
	long			last_meal_time;
	pthread_t		overseer;
	struct s_data	*data;
}	t_phi;

typedef struct s_data {
	long		start_time;
	int			alive;
	int			sated;
	int			continuer;
	long		tts;
	long		tte;
	long		ttd;
	int			phi_count;
	int			meal_limit;
	sem_t		*sem_forks;
	sem_t		*sem_data;
	sem_t		*sem_output;
	sem_t		*sem_continue;
	sem_t		*sem_death;
	sem_t		*sem_sated;
	t_phi		*phi_array;
	t_phi		*current_phi;
	pthread_t	sated_thread;
	pthread_t	death_thread;
}	t_data;

#endif
