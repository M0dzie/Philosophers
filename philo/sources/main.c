/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:23:23 by thmeyer           #+#    #+#             */
/*   Updated: 2023/04/17 13:31:05 by thmeyer          ###   ########.fr       */
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
		data->must_eat = ft_atoi(argv[5]);
		printf("must_eat = %ld\n", data->must_eat);
	}
}

// static void	*start_routine(void *index)
// {
// 	long	n;

// 	n = (long)index;
// 	printf("salut %ld fois\n", n);
// 	return (NULL);
// }

int	main(int argc, char **argv)
{
	t_pdata		data;
	// pthread_t	*data;
	// int			n_philo;
	// long		i;

	// i = -1;
	if (argc != 5 && argc != 6)
		return (display_error("Wrong number of arguments, you should have :\n\
<number of philosophers> <time to die> <time to eat> <time to sleep> \n\
and eventually <number of times each philosophers must eat>"), 1);
	if (wrong_arg(argv))
		return (1);
	init_data(&data, argv);
	// n_philo = ft_atoi(argv[1]);
	// data = malloc(sizeof(pthread_t) * (n_philo + 1));
	// if (!data)
	// 	return (1);
	// while (++i < n_philo)
	// {
	// 	pthread_create(&data[i], NULL, start_routine, (void *)i);
	// 	pthread_join(data[i], NULL);
	// }
	return (0);
}
