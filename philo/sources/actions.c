/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:43:45 by thmeyer           #+#    #+#             */
/*   Updated: 2023/05/03 14:21:36 by thmeyer          ###   ########.fr       */
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
	pthread_mutex_lock(&philo->data->fork[philo->id - 1]);
	// pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(&philo->data->mutex_data);
	if (philo->data->all_alive)
	{
		pthread_mutex_unlock(&philo->data->mutex_data);
		display_status(philo, 1);
	}
	else
		pthread_mutex_unlock(&philo->data->mutex_data);
	if (philo->data->nbr_philo > 1)
	{
		// pthread_mutex_lock(philo->l_fork);
		pthread_mutex_lock(&philo->data->fork[philo->id % \
		philo->data->nbr_philo]);
		pthread_mutex_lock(&philo->data->mutex_data);
		if (philo->data->all_alive)
		{
			pthread_mutex_unlock(&philo->data->mutex_data);
			display_status(philo, 1);
		}
		else
			pthread_mutex_unlock(&philo->data->mutex_data);
	}
	else
		ft_usleep(philo->data->time_to_die);
		// usleep(philo->data->time_to_die * 1000);
}

static void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_data);
	if (philo->data->all_alive)
	{
		pthread_mutex_unlock(&philo->data->mutex_data);
		display_status(philo, 2);
		ft_usleep(philo->data->time_to_eat);
		usleep(philo->data->time_to_eat * 1000);
		pthread_mutex_lock(&philo->mutex_philo);
		philo->last_eat = get_time();
		pthread_mutex_unlock(&philo->mutex_philo);
	}
	else
		pthread_mutex_unlock(&philo->data->mutex_data);
}

static void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_data);
	if (philo->data->all_alive)
	{
		pthread_mutex_unlock(&philo->data->mutex_data);
		display_status(philo, 3);
		ft_usleep(philo->data->time_to_sleep);
		usleep(philo->data->time_to_sleep * 1000);
	}
	else
		pthread_mutex_unlock(&philo->data->mutex_data);
}

void	forks_and_eat(t_philo *philo)
{
	thinking(philo);
	take_forks(philo);
	eating(philo);
	// pthread_mutex_unlock(philo->r_fork);
	// pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(&philo->data->fork[philo->id - 1]);
	if (philo->data->nbr_philo > 1)
		pthread_mutex_unlock(&philo->data->fork[philo->id % \
		philo->data->nbr_philo]);
	sleeping(philo);
}
