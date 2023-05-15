/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:43:45 by thmeyer           #+#    #+#             */
/*   Updated: 2023/05/15 10:57:21 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	thinking(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->mutex_data);
	if (data->all_alive)
	{
		pthread_mutex_unlock(&data->mutex_data);
		display_status(philo, 0);
	}
	else
		pthread_mutex_unlock(&data->mutex_data);
}

static void	take_forks(t_philo *philo, t_data *data, int fork1, int fork2)
{
	pthread_mutex_lock(&data->fork[fork1]);
	pthread_mutex_lock(&data->mutex_data);
	if (data->all_alive)
	{
		pthread_mutex_unlock(&data->mutex_data);
		display_status(philo, 1);
	}
	else
		pthread_mutex_unlock(&data->mutex_data);
	if (data->nbr_philo > 1)
	{
		pthread_mutex_lock(&data->fork[fork2]);
		pthread_mutex_lock(&data->mutex_data);
		if (data->all_alive)
		{
			pthread_mutex_unlock(&data->mutex_data);
			display_status(philo, 1);
		}
		else
			pthread_mutex_unlock(&data->mutex_data);
	}
	else
		usleep(data->time_to_die * 1100);
}

static void	eating(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->mutex_data);
	if (data->all_alive)
	{
		pthread_mutex_unlock(&data->mutex_data);
		display_status(philo, 2);
		pthread_mutex_lock(&philo->mutex_philo);
		philo->ate = 1;
		pthread_mutex_unlock(&philo->mutex_philo);
		usleep(data->time_to_eat * 1000);
	}
	else
		pthread_mutex_unlock(&data->mutex_data);
	pthread_mutex_lock(&data->mutex_data);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&data->mutex_data);
}

static void	sleeping(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->mutex_data);
	if (data->all_alive)
	{
		pthread_mutex_unlock(&data->mutex_data);
		display_status(philo, 3);
		usleep(data->time_to_sleep * 1000);
	}
	else
		pthread_mutex_unlock(&data->mutex_data);
}

void	actions(t_philo *philo, t_data *data, long nbr_philo)
{
	thinking(philo, data);
	if (philo->id == nbr_philo && nbr_philo != 1)
		take_forks(philo, data, philo->id % nbr_philo, philo->id - 1);
	else
		take_forks(philo, data, philo->id - 1, philo->id % nbr_philo);
	eating(philo, data);
	if (philo->id == nbr_philo)
	{
		pthread_mutex_unlock(&data->fork[philo->id - 1]);
		if (nbr_philo > 1)
			pthread_mutex_unlock(&data->fork[philo->id % nbr_philo]);
	}
	else
	{
		pthread_mutex_unlock(&data->fork[philo->id % nbr_philo]);
		if (nbr_philo > 1)
			pthread_mutex_unlock(&data->fork[philo->id - 1]);
	}
	sleeping(philo, data);
}
