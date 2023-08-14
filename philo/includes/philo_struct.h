#ifndef PHILO_STRUCT_H
# define PHILO_STRUCT_H

# include <pthread.h>

typedef pthread_mutex_t	t_mutex;
typedef struct timeval	t_tv;

typedef struct s_phi {
	pthread_t		t_id;
	int				is_alive;
	int				id;
	int				meal_count;
	int				got_forks;
	long			last_meal_time;
	t_mutex			*left_fork;
	t_mutex			*right_fork;
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
	t_mutex	*forks;
	t_mutex	mutex;
	t_mutex	output;
	t_phi	**phi_array;
	t_phi	*overseer;
}	t_data;

#endif
