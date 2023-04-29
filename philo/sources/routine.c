/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:00:14 by thmeyer           #+#    #+#             */
/*   Updated: 2023/04/29 14:11:15 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	init_philo(t_philo *philo, t_data *data)
{
	int				i;
	struct timeval	init_p;

	i = -1;
	gettimeofday(&init_p, NULL);
	while (++i < data->nbr_philo)
	{
		philo[i].id = i + 1;
		philo[i].data = data;
		philo[i].last_eat = init_p;
		philo[i].is_alive = 1;
		pthread_mutex_init(&philo[i].mutex_philo, NULL);
	}
}

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
}

static void	forks_and_eat(t_philo *philo)
{
	if (philo->is_alive)
		display_status(philo, 0);
	pthread_mutex_lock(&philo->data->fork[philo->id - 1]);
	if (philo->is_alive)
		display_status(philo, 1);
	pthread_mutex_lock(&philo->data->fork[philo->id % \
	philo->data->nbr_philo]);
	if (philo->is_alive)
		display_status(philo, 1);
	if (philo->is_alive)
	{
		display_status(philo, 2);
		usleep(philo->data->time_to_eat * 1000);
		gettimeofday(&philo->last_eat, NULL);
	}
	pthread_mutex_unlock(&philo->data->fork[philo->id - 1]);
	pthread_mutex_unlock(&philo->data->fork[philo->id % \
	philo->data->nbr_philo]);
	if (philo->is_alive)
	{
		display_status(philo, 3);
		usleep(philo->data->time_to_sleep * 1000);
	}
}

static void	*start_routine(void *arg)
{
	int		eat_count;
	t_philo	*philo;

	eat_count = 0;
	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep((philo->data->time_to_eat - (philo->data->time_to_eat / 10)) * 1000);
	if (philo->data->nbr_must_eat == -1)
		while (philo->is_alive)
			forks_and_eat(philo);
	else
	{
		while (eat_count < philo->data->nbr_must_eat && philo->is_alive)
		{
			forks_and_eat(philo);
			eat_count++;
		}
		if (eat_count == philo->data->nbr_must_eat)
			philo->is_alive = 0;
	}
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
		pthread_create(&ph_thread[i], NULL, start_routine, (void *)&philo[i]);
	i = -1;
	check_death(philo);
	while (++i < data->nbr_philo)
		pthread_join(ph_thread[i], NULL);
	destroy_mutex(philo, data);
	return (free(data->fork), free(philo), free(ph_thread), NULL);
}
