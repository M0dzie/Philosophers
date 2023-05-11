/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 09:50:33 by thmeyer           #+#    #+#             */
/*   Updated: 2023/05/11 11:12:43 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	special_case(t_data *data)
{
	pthread_mutex_lock(&data->mutex_data);
	if (data->all_alive == 2)
		return (pthread_mutex_unlock(&data->mutex_data), 1);
	pthread_mutex_unlock(&data->mutex_data);
	return (0);
}

static void	check_meal(t_philo *philo, t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nbr_philo)
	{
		pthread_mutex_lock(&philo[i].mutex_philo);
		if (!philo[i].ate)
			return ((void)pthread_mutex_unlock(&philo[i].mutex_philo));
		pthread_mutex_unlock(&philo[i].mutex_philo);
	}
	i = -1;
	while (++i < data->nbr_philo)
	{
		pthread_mutex_lock(&philo[i].mutex_philo);
		philo[i].ate = 0;
		pthread_mutex_unlock(&philo[i].mutex_philo);
	}
}

void	check_death(t_philo *philo, t_data *data)
{
	int				i;
	long			time_eat;

	while (1)
	{
		if (special_case(data))
			return ;
		i = -1;
		while (++i < data->nbr_philo)
		{
			check_meal(philo, data);
			pthread_mutex_lock(&philo[i].mutex_philo);
			time_eat = get_time() - philo[i].last_eat;
			pthread_mutex_unlock(&philo[i].mutex_philo);
			if (time_eat > data->time_to_die)
			{
				pthread_mutex_lock(&data->mutex_data);
				data->all_alive = 0;
				display_status(&philo[i], 4);
				pthread_mutex_unlock(&data->mutex_data);
				return ;
			}
		}
	}
}
