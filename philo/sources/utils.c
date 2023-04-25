/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:23:23 by thmeyer           #+#    #+#             */
/*   Updated: 2023/04/25 15:19:28 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

long	ft_atoi(const char *str)
{
	long	i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		if (result != ((result * 10 + (((str[i] - 48)) * sign)) / 10))
			return (((sign + 1) / 2) / -1);
		result = result * 10 + ((str[i] - 48) * sign);
		i++;
	}
	return (result);
}

void	display_status(t_philo *philo, int status)
{
	char	*msg[5];

	msg[0] = "is thinking\n";
	msg[1] = "has taken a fork\n";
	msg[2] = "is eating\n";
	msg[3] = "is sleeping\n";
	msg[4] = "died\n";
	gettimeofday(&philo->data->now, NULL);
	pthread_mutex_lock(&philo->data->write);
	printf("%ld %d %s", (philo->data->now.tv_sec * 1000 + \
	philo->data->now.tv_usec / 1000) - philo->data->time_init, \
	philo->id, msg[status]);
	pthread_mutex_unlock(&philo->data->write);
}

// void	ft_usleep(int time)
// {
// }
