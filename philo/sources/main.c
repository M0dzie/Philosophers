/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:23:23 by thmeyer           #+#    #+#             */
/*   Updated: 2023/04/17 14:18:49 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	init_data(t_pdata *data, char **argv)
{
	data->nbr_philo = ft_atoi(argv[1]);
	printf("nbr_philo = %ld\n", data->nbr_philo);
	data->time_to_die = ft_atoi(argv[2]);
	printf("time_to_die = %ld\n", data->time_to_die);
	data->time_to_eat = ft_atoi(argv[3]);
	printf("time_to_eat = %ld\n", data->time_to_eat);
	data->time_to_sleep = ft_atoi(argv[4]);
	printf("time_to_sleep = %ld\n", data->time_to_sleep);
	if (argv[5])
	{
		data->nbr_must_eat = ft_atoi(argv[5]);
		printf("nbr_must_eat = %ld\n", data->nbr_must_eat);
	}
}

static void	*start_routine(void *index)
{
	long	n;

	n = (long)index;
	if (n % 2 == 0)
		printf("(pair) philo n%ld\n", n);
	else
		printf("(impair) philo n%ld\n", n);
	return (NULL);
}

static void	*create_thread(t_pdata *data)
{
	long		i;
	pthread_t	*philo;

	i = -1;
	philo = malloc(sizeof(pthread_t) * (data->nbr_philo + 1));
	if (!philo)
		return (NULL);
	while (++i < data->nbr_philo)
	{	
		pthread_create(&philo[i], NULL, start_routine, (void *)i);
		pthread_join(philo[i], NULL);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_pdata		data;

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
