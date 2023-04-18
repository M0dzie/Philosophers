/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:23:23 by thmeyer           #+#    #+#             */
/*   Updated: 2023/04/18 09:47:32 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	display_error(char *str)
{
	write(2, "\033[0;31mError\n", 13);
	write(2, str, ft_strlen(str));
	write(2, "\n\033[0m", 5);
	return ;
}

static int	wrong_number(char **argv)
{
	int	i;

	i = 0;
	while (argv[++i])
	{
		if (ft_atoi(argv[i]) > INT_MAX || ft_atoi(argv[i]) < 1 || \
		ft_strlen(argv[i]) > 11)
		{
			if (i == 1)
				display_error("<number_of_philosophers> must be greater \
than 0");
			if (i == 2)
				display_error("<time_to_die> is not a positive int greater \
than 0");
			if (i == 3)
				display_error("<time_to_eat> is not a positive int greater \
than 0");
			if (i == 4)
				display_error("<time_to_sleep> is not a positive int greater \
than 0");
			if (i == 5)
				display_error("<number_of_times_each_philosopher_must_eat> \
is not a positive int greather than 0");
			return (1);
		}
	}
	return (0);
}

int	wrong_arg(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			if (!ft_isdigit(argv[i][j]) && argv[i][j] != '-' && \
			argv[i][j] != '+')
			{
				display_error("The argument must be numeric");
				return (1);
			}
		}
	}
	if (wrong_number(argv))
		return (1);
	return (0);
}
