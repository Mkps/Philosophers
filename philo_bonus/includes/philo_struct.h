/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 12:43:57 by aloubier          #+#    #+#             */
/*   Updated: 2023/08/15 12:43:58 by aloubier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_STRUCT_H
# define PHILO_STRUCT_H

# include <pthread.h>
# include <semaphore.h>
#include <unistd.h>

typedef pthread_mutex_t	t_mutex;
typedef struct timeval	t_tv;

typedef struct s_phi {
	pthread_t		t_id;
	pid_t			pid;
	int				is_alive;
	int				id;
	int				meal_count;
	int				got_forks;
	long			last_meal_time;
	struct s_data	*data;
}	t_phi;

typedef struct s_data {
	t_tv	start_time;
	int		alive;
	int		sated;
	long	tts;
	long	tte;
	long	ttd;
	int		phi_count;
	int		meal_limit;
	sem_t	*sem_forks;
	sem_t	*sem_data;
	sem_t	*sem_output;
	sem_t	*sem_continue;
	t_phi	*phi_array;
}	t_data;

#endif
