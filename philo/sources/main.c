/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:23:23 by thmeyer           #+#    #+#             */
/*   Updated: 2023/04/17 11:09:38 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	*start_routine(void *index)
{
	long	n;

	n = (long)index;
	printf("salut %ld fois\n", n);
	return (NULL);
}

int	main(int argc, char **argv)
{
	pthread_t	*data;
	int			n_philo;
	long		i;

	i = -1;
	if (argc != 5 && argc != 6)
		display_error("Wrong number of arguments, you should have :\n\
<number of philosophers> <time to die> <time to eat> <time to sleep> \n\
and eventually <number of times each philosophers must eat>");
	check_arg(argv);
	n_philo = ft_atoi(argv[1]);
	data = malloc(sizeof(pthread_t) * (n_philo + 1));
	if (!data)
		return (1);
	while (++i < n_philo)
	{
		pthread_create(&data[i], NULL, start_routine, (void *)i);
		pthread_join(data[i], NULL);
	}
	return (0);
}
