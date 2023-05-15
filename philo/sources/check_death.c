/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 09:50:33 by thmeyer           #+#    #+#             */
/*   Updated: 2023/05/15 11:50:11 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	update_status(t_philo *philo, t_data *data, int should_display_msg)
{
	pthread_mutex_lock(&data->mutex_data);
	data->all_alive = 0;
	pthread_mutex_unlock(&data->mutex_data);
	if (should_display_msg)
		display_status(philo, 4);
}

static void	end_of_loop(t_philo *philo, long nbr_philo)
{
	int	i;

	i = -1;
	while (++i < nbr_philo)
	{
		pthread_mutex_lock(&philo[i].mutex_philo);
		if (!philo[i].ate)
			return ((void)pthread_mutex_unlock(&philo[i].mutex_philo));
		pthread_mutex_unlock(&philo[i].mutex_philo);
	}
	i = -1;
	while (++i < nbr_philo)
	{
		pthread_mutex_lock(&philo[i].mutex_philo);
		philo[i].ate = 0;
		pthread_mutex_unlock(&philo[i].mutex_philo);
	}
}

static int	enough_meal(t_philo *philo, long nbr_philo, long nbr_must_eat)
{
	int	i;

	i = -1;
	while (++i < nbr_philo)
	{
		pthread_mutex_lock(&philo->mutex_philo);
		if (philo[i].eat_count != nbr_must_eat)
			return (pthread_mutex_unlock(&philo->mutex_philo), 0);
		pthread_mutex_unlock(&philo->mutex_philo);
	}
	return (1);
}

void	check_death(t_philo *philo, t_data *data)
{
	int				i;
	long			time_eat;

	while (1)
	{
		i = -1;
		while (++i < data->nbr_philo)
		{
			end_of_loop(philo, data->nbr_philo);
			if (enough_meal(philo, data->nbr_philo, data->nbr_must_eat))
				return (update_status(philo + i, data, 0));
			pthread_mutex_lock(&data->mutex_data);
			time_eat = get_time() - philo[i].last_eat;
			if (time_eat > data->time_to_die)
				return (pthread_mutex_unlock(&data->mutex_data), \
				update_status(philo + i, data, 1));
			pthread_mutex_unlock(&data->mutex_data);
		}
	}
}
