/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:23:23 by thmeyer           #+#    #+#             */
/*   Updated: 2023/04/18 15:07:00 by thmeyer          ###   ########.fr       */
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
}

static void	*start_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
	{
		// printf("je suis le philo %d\n", philo->id + 1);
		pthread_mutex_lock(&philo->data->fork[philo->id - 1]);
		printf("Philo %d has taken a fork\n", philo->id + 1);
		pthread_mutex_lock(&philo->data->fork[philo->id]);
		printf("Philo %d has taken a fork\n", philo->id + 1);
		printf("Philo %d is eating\n", philo->id + 1);
		pthread_mutex_unlock(&philo->data->fork[philo->id - 1]);
		pthread_mutex_unlock(&philo->data->fork[philo->id]);
	}
	else
		printf("ca marche R\n");
	return (NULL);
}

static void	*create_thread(t_data *data)
{
	int				i;
	t_philo			philo[data->nbr_philo];
	pthread_t		config[data->nbr_philo];
	pthread_mutex_t	fork[data->nbr_philo];

	data->fork = fork;
	philo->data = data;
	i = -1;
	while (++i < data->nbr_philo)
	{
		philo[i].id = i;
		printf("i = %d\n", i);
		pthread_mutex_init(&philo->data->fork[i], NULL);
		pthread_create(&config[i], NULL, start_routine, &philo[i]);
		pthread_join(config[i], NULL);
		usleep(30);
	}
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
	