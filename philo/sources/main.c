/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:23:23 by thmeyer           #+#    #+#             */
/*   Updated: 2023/04/20 11:41:55 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	init_data(t_data *data, char **argv)
{
	gettimeofday(&data->initial, NULL);
	data->nbr_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->nbr_must_eat = ft_atoi(argv[5]);
	else
		data->nbr_must_eat = -1;
}

static void	*display_msg(t_philo *philo, int status)
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
	printf("%ldms Philo %d %s", time_ms, philo->id, msg[status]);
	return (NULL);
}

static void	*forks_and_eat(t_philo *philo)
{
	display_msg(philo, 0);
	pthread_mutex_lock(&philo->data->fork[philo->id - 1]);
	display_msg(philo, 1);
	pthread_mutex_lock(&philo->data->fork[philo->id % philo->data->nbr_philo]);
	display_msg(philo, 1);
	display_msg(philo, 2);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->data->fork[philo->id - 1]);
	pthread_mutex_unlock(&philo->data->fork[philo->id % philo->data->nbr_philo]);
	display_msg(philo, 3);
	usleep(philo->data->time_to_sleep * 1000);
	return (NULL);
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
		while (philo->data->nbr_must_eat == -1)
			forks_and_eat(philo);
	else
		while (index < philo->data->nbr_must_eat)
		{
			forks_and_eat(philo);
			index++;
		}
	return (NULL);
}

static void	*create_thread(t_data *data)
{
	int				i;
	t_philo			philo[data->nbr_philo];
	pthread_t		ph_thread[data->nbr_philo];
	pthread_mutex_t	fork[data->nbr_philo];

	data->fork = fork;
	i = -1;
	while (++i < data->nbr_philo)	
		pthread_mutex_init(&data->fork[i], NULL);
	i = -1;
	while (++i < data->nbr_philo)
	{
		philo[i].id = i + 1;
		philo[i].data = data;
		pthread_create(&ph_thread[i], NULL, start_routine, (void *)&philo[i]);
	}
	i = -1;
	while (++i < data->nbr_philo)
		pthread_join(ph_thread[i], NULL);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
		return (display_error("Wrong number of arguments, you should have :\n\
<number of philosophers> <time to die> <time to eat> <time to sleep> \n\
and eventually <number of times each philosophers must eat>"), 1);
	if (wrong_arg(argv))
		return (1);
	init_data(&data, argv);
	create_thread(&data);
	return (0);
}
	