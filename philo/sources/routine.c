/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:00:14 by thmeyer           #+#    #+#             */
/*   Updated: 2023/05/04 13:44:20 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	destroy_mutex(t_philo *philo, t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nbr_philo)
	{
		pthread_mutex_destroy(&data->fork[i]);
		pthread_mutex_destroy(&philo[i].mutex_philo);
	}
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->mutex_data);
}

static void	forks_and_eat(t_philo *philo, t_data *data)
{
	thinking(philo, data);
	if (philo->id == data->nbr_philo)
		take_last_forks(philo, data);
	else
		take_forks(philo, data);
	eating(philo, data);
	if (philo->id == data->nbr_philo)
	{
		pthread_mutex_unlock(&data->fork[philo->id % data->nbr_philo]);
		if (data->nbr_philo > 1)
			pthread_mutex_unlock(&data->fork[philo->id - 1]);
	}
	else
	{
		pthread_mutex_unlock(&data->fork[philo->id - 1]);
		if (data->nbr_philo > 1)
			pthread_mutex_unlock(&data->fork[philo->id % data->nbr_philo]);
	}
	sleeping(philo, data);
}

static void	delimited_routine(t_philo *philo, t_data *data)
{
	int	eat_count;

	eat_count = 0;
	while (1)
	{
		pthread_mutex_lock(&data->mutex_data);
		if (!data->all_alive)
			return ((void)pthread_mutex_unlock(&data->mutex_data));
		pthread_mutex_unlock(&data->mutex_data);
		forks_and_eat(philo, data);
		eat_count++;
		if (eat_count == data->nbr_must_eat)
		{
			pthread_mutex_lock(&data->mutex_data);
			data->all_alive = 2;
			pthread_mutex_unlock(&data->mutex_data);
			return ;
		}
	}
}

static void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep((philo->data->time_to_eat - (philo->data->time_to_eat / 10)) \
		* 1000);
	if (philo->data->nbr_must_eat == -1)
	{
		while (1)
		{
			pthread_mutex_lock(&philo->data->mutex_data);
			if (!philo->data->all_alive)
				return (pthread_mutex_unlock(&philo->data->mutex_data), NULL);
			pthread_mutex_unlock(&philo->data->mutex_data);
			forks_and_eat(philo, philo->data);
		}
	}
	else
		delimited_routine(philo, philo->data);
	return (NULL);
}

void	*create_thread(t_data *data)
{
	int				i;
	t_philo			*philo;
	pthread_t		*ph_thread;

	data->fork = malloc(sizeof(pthread_mutex_t) * data->nbr_philo);
	philo = malloc(sizeof(t_philo) * data->nbr_philo);
	ph_thread = malloc(sizeof(pthread_t) * data->nbr_philo);
	if (!philo || !ph_thread || !data->fork)
		return (NULL);
	init_philo(philo, data);
	i = -1;
	while (++i < data->nbr_philo)
		pthread_mutex_init(&data->fork[i], NULL);
	i = -1;
	while (++i < data->nbr_philo)
		if (pthread_create(&ph_thread[i], NULL, routine, (void *)&philo[i]))
			return (display_error("Error while creating threads"), NULL);
	i = -1;
	check_death(philo, data);
	while (++i < data->nbr_philo)
		if (pthread_join(ph_thread[i], NULL))
			return (display_error("Error while joining threads"), NULL);
	destroy_mutex(philo, data);
	return (free(data->fork), free(philo), free(ph_thread), NULL);
}
