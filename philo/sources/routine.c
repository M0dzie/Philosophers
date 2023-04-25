/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:00:14 by thmeyer           #+#    #+#             */
/*   Updated: 2023/04/25 09:49:03 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	init_philo(t_philo *philo, t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nbr_philo)
	{
		philo[i].id = i + 1;
		philo[i].data = data;
		philo[i].last_eat = 0;
		philo[i].cur_eat = 0;
	}
}

// static int	is_dead(t_philo *philo, t_data *data)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < data->nbr_philo)
// 	{
// 		if (philo[i].last_eat == 0)
// 			philo[i].last_eat = data->initial.tv_sec * 1000 + data->initial.tv_usec / 1000;
// 		if (philo[i].cur_eat == 0)
// 			philo[i].cur_eat = data->initial.tv_sec * 1000 + data->initial.tv_usec / 1000;
// 		printf("last eat = %ld\n", philo[i].last_eat);
// 		printf("cur eat = %ld\n", philo[i].cur_eat);
// 		printf("ttd = %ld\n", data->time_to_die);
// 		printf("calcul = %ld\n", philo[i].cur_eat - philo[i].last_eat);
// 		if (philo[i].cur_eat - philo[i].last_eat > data->time_to_die)
// 			return (display_status(&philo[i], 4), 1);
// 		philo[i].last_eat = philo[i].cur_eat;
// 		printf("last eat = %ld\nend of loop\n", philo[i].last_eat);
// 	}
// 	return (0);
// }

static int	is_dead(t_philo *philo, t_data *data)
{
	if (philo->last_eat == 0)
		philo->last_eat = data->initial.tv_sec * 1000 + \
		data->initial.tv_usec / 1000;
	if (philo->cur_eat == 0)
		philo->cur_eat = data->initial.tv_sec * 1000 + \
		data->initial.tv_usec / 1000;
	printf("last eat = %ld\n", philo->last_eat);
	printf("cur eat = %ld\n", philo->cur_eat);
	printf("ttd = %ld\n", data->time_to_die);
	printf("calcul = %ld\n", philo->cur_eat - philo->last_eat);
	if (philo->cur_eat - philo->last_eat > data->time_to_die)
		return (display_status(philo, 4), 1);
	philo->last_eat = philo->cur_eat;
	printf("last eat = %ld\nend of loop\n", philo->last_eat);
	return (0);
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
	gettimeofday(&philo->new_eat, NULL);
	philo->cur_eat = philo->new_eat.tv_sec * 1000 + \
	philo->new_eat.tv_usec / 1000;
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
		while (!is_dead(philo, philo->data))
			forks_and_eat(philo);
	else
	{
		while (index < philo->data->nbr_must_eat && \
		!is_dead(philo, philo->data))
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
	init_philo(philo, data);
	while (++i < data->nbr_philo)
		pthread_mutex_init(&data->fork[i], NULL);
	i = -1;
	while (++i < data->nbr_philo)
		pthread_create(&ph_thread[i], NULL, start_routine, (void *)&philo[i]);
	i = -1;
	while (++i < data->nbr_philo)
		pthread_join(ph_thread[i], NULL);
	return (free(data->fork), free(philo), free(ph_thread), NULL);
}
