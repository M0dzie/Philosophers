/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 17:27:56 by thmeyer           #+#    #+#             */
/*   Updated: 2023/04/29 17:34:20 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	init_data(t_data *data, char **argv)
{
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->mutex_data, NULL);
	data->time_init = get_time();
	data->all_alive = 1;
	data->nbr_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->nbr_must_eat = ft_atoi(argv[5]);
	else
		data->nbr_must_eat = -1;
}

void	init_philo(t_philo *philo, t_data *data)
{
	int				i;

	i = -1;
	while (++i < data->nbr_philo)
	{
		philo[i].id = i + 1;
		philo[i].data = data;
		philo[i].last_eat = get_time();
		pthread_mutex_init(&philo[i].mutex_philo, NULL);
		pthread_mutex_init(&philo[i].l_fork, NULL);
		pthread_mutex_init(&philo[i].r_fork, NULL);
	}
}

void	assign_forks(t_philo *philo, t_data *data)
{
	int	i;

	i = -1;
	
	while (++i < data->nbr_philo)
	{
		philo[i].l_fork = data->fork[philo[i].id - 1];
		philo[i].r_fork = data->fork[philo[i].id % data->nbr_philo];
	}
}