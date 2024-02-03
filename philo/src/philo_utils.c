/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 15:10:05 by eros-gir          #+#    #+#             */
/*   Updated: 2022/12/18 18:25:37 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../incl/philolib.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

long int	ft_atol(char *input)
{
	size_t		len;
	int			sign;
	long int	result;

	len = 0;
	sign = 1;
	result = 0;
	while (input[len] == ' ' || input[len] == '\n' || input[len] == '\t'
		|| input[len] == '\v' || input[len] == '\r' || input[len] == '\f')
		len ++;
	while (input[len] == '-' || input[len] == '+')
	{
		if (input[len] == '-')
			sign *= -1;
		len ++;
	}
	while (ft_isdigit(input[len]))
	{
		result = (input[len] - '0') + (result * 10);
		len ++;
	}
	result = result * sign;
	return (result);
}

//delta time updates the time the program has been running
long int	ft_set_delta_time(t_args *args)
{
	long int	d_time;

	args->timer = ft_get_time();
	d_time = (args->timer - args->s_timer) / 1000;
	return (d_time);
}

//get the time difference in miliseconds
long int	ft_time_dif(long int first, long int second)
{
	return ((second - first) / 1000);
}

long int	ft_get_time(void)
{
	struct timeval	tv;
	long int		fulltime;

	gettimeofday(&tv, NULL);
	fulltime = (tv.tv_sec * 1000000) + tv.tv_usec;
	return (fulltime);
}
