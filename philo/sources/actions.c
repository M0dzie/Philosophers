/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:43:45 by thmeyer           #+#    #+#             */
/*   Updated: 2023/04/29 15:58:05 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_data);
	if (philo->data->all_alive)
	{
		pthread_mutex_unlock(&philo->data->mutex_data);
		display_status(philo, 0);
	}
	else
		pthread_mutex_unlock(&philo->data->mutex_data);
}

static void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_data);
	if (philo->data->all_alive)
	{
		pthread_mutex_unlock(&philo->data->mutex_data);
		display_status(philo, 1);
		pthread_mutex_lock(&philo->data->fork[philo->id - 1]);
	}
	else
		pthread_mutex_unlock(&philo->data->mutex_data);
	pthread_mutex_lock(&philo->data->mutex_data);
	if (philo->data->all_alive)
	{
		pthread_mutex_unlock(&philo->data->mutex_data);
		display_status(philo, 1);
		pthread_mutex_lock(&philo->data->fork[philo->id % \
		philo->data->nbr_philo]);
	}
	else
		pthread_mutex_unlock(&philo->data->mutex_data);
}

void	forks_and_eat(t_philo *philo)
{
	thinking(philo);
	take_forks(philo);
	pthread_mutex_lock(&philo->data->mutex_data);
	if (philo->data->all_alive)
	{
		pthread_mutex_unlock(&philo->data->mutex_data);
		display_status(philo, 2);
		usleep(philo->data->time_to_eat * 1000);
		gettimeofday(&philo->last_eat, NULL);
	}
	else
		pthread_mutex_unlock(&philo->data->mutex_data);
	pthread_mutex_unlock(&philo->data->fork[philo->id - 1]);
	pthread_mutex_unlock(&philo->data->fork[philo->id % \
	philo->data->nbr_philo]);
	pthread_mutex_lock(&philo->data->mutex_data);
	if (philo->data->all_alive)
	{
		pthread_mutex_unlock(&philo->data->mutex_data);
		display_status(philo, 3);
		usleep(philo->data->time_to_sleep * 1000);
	}
	else
		pthread_mutex_unlock(&philo->data->mutex_data);
}