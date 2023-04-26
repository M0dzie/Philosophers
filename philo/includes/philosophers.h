/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:23:23 by thmeyer           #+#    #+#             */
/*   Updated: 2023/04/26 14:10:53 by thmeyer          ###   ########.fr       */
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
	// int				all_alive;
	long			nbr_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			nbr_must_eat;
	long			time_init;
	pthread_mutex_t	write;
	pthread_mutex_t	*fork;
	struct timeval	now;
}					t_data;

typedef struct s_philo
{
	int				id;
	int				is_alive;
	t_data			*data;
	pthread_mutex_t	mutex_philo;
	struct timeval	last_eat;
}					t_philo;

int		wrong_arg(char **argv);
int		ft_isdigit(int c);
int		ft_strlen(char *str);

long	ft_atoi(const char *str);

void	*create_thread(t_data *data);
void	display_error(char *str);
void	display_status(t_philo *philo, int status);
// void	ft_usleep(int usleep_time, t_data *data);

#endif