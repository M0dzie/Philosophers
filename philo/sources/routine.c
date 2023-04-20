/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:00:14 by thmeyer           #+#    #+#             */
/*   Updated: 2023/04/20 15:54:31 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	display_status(t_philo *philo, int status)
{
	char	*msg[5];
	long	time_ms;

	msg[0] = "is thinking\n";
	msg[1] = "has taken a fork\n";
	msg[2] = "is eating\n";
	msg[3] = "is sleeping\n";
	msg[4] = "died\n";
	gettimeofday(&philo->data->now, NULL);
	time_ms = (philo->data->now.tv_sec - philo->data->initial.tv_sec) * 1000 \
	+ (philo->data->now.tv_usec - philo->data->initial.tv_usec) / 1000;
	printf("%ld %d %s", time_ms, philo->id, msg[status]);
}

static void	check_death(t_philo *philo)
{
	long	new_eat;

	gettimeofday(&philo->new_eat, NULL);
	new_eat = philo->new_eat.tv_sec * 1000 + philo->new_eat.tv_usec / 1000;
	printf("new_eat = %ld\n", new_eat);
	if (new_eat - philo->last_eat > philo->data->time_to_die)
		return (philo->data->all_alive = 0, display_status(philo, 4));
	else
		philo->last_eat = new_eat;
	printf("last_eat = %ld\n", philo->last_eat);
}

static void	forks_and_eat(t_philo *philo)
{
	display_status(philo, 0);
	pthread_mutex_lock(&philo->data->fork[philo->id - 1]);
	display_status(philo, 1);
	pthread_mutex_lock(&philo->data->fork[philo->id % philo->data->nbr_philo]);
	display_status(philo, 1);
	display_status(philo, 2);
	usleep(philo->data->time_to_eat * 1000);
	check_death(philo);
	pthread_mutex_unlock(&philo->data->fork[philo->id - 1]);
	pthread_mutex_unlock(&philo->data->fork[philo->id % \
	philo->data->nbr_philo]);
	display_status(philo, 3);
	usleep(philo->data->time_to_sleep * 1000);
}

static void	*start_routine(void *arg)
{
	int		index;
	t_philo	*philo;

	index = 0;
	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(50);
	if (philo->data->nbr_must_eat == -1)
		while (philo->data->all_alive)
			forks_and_eat(philo);
	else
	{
		while (index < philo->data->nbr_must_eat)
		{
			forks_and_eat(philo);
			index++;
		}
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
	i = -1;
	while (++i < data->nbr_philo)
		pthread_mutex_init(&data->fork[i], NULL);
	i = -1;
	while (++i < data->nbr_philo)
	{
		philo[i].id = i + 1;
		philo[i].data = data;
		philo[i].last_eat = philo->data->initial.tv_sec * 1000 + \
		philo->data->initial.tv_usec / 1000;
		printf("last_eat = %ld\n", philo[i].last_eat);
		pthread_create(&ph_thread[i], NULL, start_routine, (void *)&philo[i]);
	}
	i = -1;
	while (++i < data->nbr_philo)
		pthread_join(ph_thread[i], NULL);
	return (free(data->fork), free(philo), free(ph_thread), NULL);
}
