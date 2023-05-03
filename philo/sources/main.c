/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:23:23 by thmeyer           #+#    #+#             */
/*   Updated: 2023/05/03 22:39:35 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

long	get_time(void)
{
	struct timeval	current;

	if (gettimeofday(&current, NULL) == -1)
		return (display_error("gettimeofday() failed"), 0);
	return (current.tv_sec * 1000 + current.tv_usec / 1000);
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
