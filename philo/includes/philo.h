#ifndef PHILO_H
#define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <limits.h>
# include <pthread.h>
# include <sys/wait.h>
# include <sys/time.h>

typedef pthread_mutex_t mutex_t;
typedef struct timeval tv;

typedef struct s_phi {
	pthread_t	t_id;
	int			is_alive;
	int			id;
	int			meal_count;
	int			got_forks;
	long		last_meal_time;
	mutex_t		*left_fork;
	mutex_t		*right_fork;
	struct s_data	*data;
} t_phi;

typedef struct s_data {
	tv 		start_time;
	int		alive;
	int		sated;
	long	tts;
	long	tte;
	long	ttd;
	int		phi_count;
	int		meal_limit;
	mutex_t	*forks;
	mutex_t	mutex;
	mutex_t	output;
	t_phi	**phi_array;
} t_data;

void	ft_sleep(t_phi *phi, long duration);
long	ft_timetol(tv time);
long	ft_get_time(void);
int		is_phi_alive(t_phi *phi);
void	timestamp(tv start);
void	output_msg(t_phi *phi, char *msg);
void	output_death(t_phi *phi);
long	ft_timetol(tv time);
int		has_eaten_enough(t_phi *phi);
int		phi_continue(t_data *data);
int		all_phi_alive(t_data *data);
int		all_phi_sated(t_data *data);
void	ft_create_thread(t_data *data);
void	ft_join_thread(t_data *data);
void	*philo_thread(void *source);

#endif
