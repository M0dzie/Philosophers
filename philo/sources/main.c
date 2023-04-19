/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:23:23 by thmeyer           #+#    #+#             */
/*   Updated: 2023/04/19 13:41:56 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	init_time(t_data *data)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	data->time = time.tv_sec;
	printf("time = %ld\n", time.tv_sec);
}

static void	init_data(t_data *data, char **argv)
{
	data->nbr_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->nbr_must_eat = ft_atoi(argv[5]);
	else
		data->nbr_must_eat = -1;
}

static void	*forks_and_eat(t_philo *philo)
{
	printf("Philo %d is thinking\n", philo->index + 1);
	pthread_mutex_lock(&philo->data->fork[philo->index]);
	printf("Philo %d has taken a fork\n", philo->index + 1);
	pthread_mutex_lock(&philo->data->fork[philo->index - 1]);
	printf("Philo %d has taken a fork\n", philo->index + 1);
	printf("Philo %d is eating\n", philo->index + 1);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->data->fork[philo->index]);
	pthread_mutex_unlock(&philo->data->fork[philo->index - 1]);
	printf("Philo %d is sleeping\n", philo->index + 1);
	usleep(philo->data->time_to_sleep * 1000);
	return (NULL);
}

static void	*start_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->index % 2 != 0)
		usleep(50);
	if (philo->data->nbr_must_eat == -1)
		while (philo->data->nbr_must_eat == -1)
			forks_and_eat(philo);
	// else
	// 	while (philo->data->nbr_must_eat-- > 0)
	// 		forks_and_eat(philo);
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
		philo[i].index = i;
		philo[i].data = data;
		pthread_create(&ph_thread[i], NULL, start_routine, (void *)&philo[i]);
		// usleep(50);
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
	init_time(&data);
	init_data(&data, argv);
	create_thread(&data);
	return (0);
}
	