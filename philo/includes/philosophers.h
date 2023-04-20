/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:23:23 by thmeyer           #+#    #+#             */
/*   Updated: 2023/04/20 09:41:28 by thmeyer          ###   ########.fr       */
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
	long			nbr_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			nbr_must_eat;
	long			time;
	pthread_mutex_t	*fork;
}					t_data;

typedef struct s_philo
{
	int		id;
	t_data	*data;
}			t_philo;

int		wrong_arg(char **argv);
int		ft_isdigit(int c);
int		ft_strlen(char *str);

long	ft_atoi(const char *str);

void	display_error(char *str);

#endif