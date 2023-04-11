/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:23:23 by thmeyer           #+#    #+#             */
/*   Updated: 2023/04/11 13:31:32 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Philosophers.h"

void	display_error(char *str)
{
	write(2, "\033[0;31mError\n", 13);
	write(2, str, ft_strlen(str));
	write(2, "\n\033[0m", 5);
	exit (0);
}

static void	check_number(char **argv)
{
	int	i;

	i = 1;
	if (ft_atoi(argv[1]) > INT_MAX || ft_atoi(argv[1]) < 1 || \
	ft_strlen(argv[1]) > 11)
		display_error("<number_of_philosophers> must be greater than 0");
	while (argv[++i])
	{
		if (ft_atoi(argv[i]) > INT_MAX || ft_atoi(argv[i]) < 0 || \
		ft_strlen(argv[i]) > 11)
		{
			if (i == 2)
				display_error("<time_to_die> is not a positive int");
			if (i == 3)
				display_error("<time_to_eat> is not a positive int");
			if (i == 4)
				display_error("<time_to_sleep> is not a positive int");
			if (i == 5)
				display_error("<number_of_times_each_philosopher_must_eat> \
is not a positive int");
		}
	}
}

void	check_arg(char **argv)
{
	int	i;
	int	j;

	i = 0;
	check_number(argv);
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			if (!ft_isdigit(argv[i][j]))
			{
				display_error("The argument must be numeric");
				exit (0);
			}
		}
	}
}
