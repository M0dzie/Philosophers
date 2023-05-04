/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:23:23 by thmeyer           #+#    #+#             */
/*   Updated: 2023/05/04 13:47:13 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	int				all_alive;
	long			nbr_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			nbr_must_eat;
	long			time_init;
	pthread_mutex_t	mutex_data;
	pthread_mutex_t	write;
	pthread_mutex_t	*fork;
}					t_data;

typedef struct s_philo
{
	int				id;
	long			last_eat;
	t_data			*data;
	pthread_mutex_t	mutex_philo;
}					t_philo;

int		ft_isdigit(int c);
int		ft_strlen(char *str);
int		wrong_arg(char **argv);

long	ft_atoi(const char *str);
long	get_time(void);

void	check_death(t_philo *philo, t_data *data);
void	*create_thread(t_data *data);
void	display_error(char *str);
void	display_status(t_philo *philo, int status);
void	eating(t_philo *philo, t_data *data);
void	init_data(t_data *data, char **argv);
void	init_philo(t_philo *philo, t_data *data);
void	lock_mutex_philo(t_philo *philo, int lock);
void	sleeping(t_philo *philo, t_data *data);
void	take_forks(t_philo *philo, t_data *data);
void	take_last_forks(t_philo *philo, t_data *data);
void	thinking(t_philo *philo, t_data *data);

#endif