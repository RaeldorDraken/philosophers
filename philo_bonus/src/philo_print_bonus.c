/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_print_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 11:09:17 by eros-gir          #+#    #+#             */
/*   Updated: 2023/01/25 10:17:58 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../incl/philolib_bonus.h"

//action is the type of text to print:
//F = taken fork S = sleeping T = thinking D = died;

void	eat_sleep_think(long int time, t_args *args)
{
	long int	i;

	i = ft_get_time();
	while (!args->deaths)
	{
		if (ft_time_dif(i, ft_get_time()) >= time)
			break ;
		usleep(50);
	}
}

void	ft_print_phil(t_args *a, long int pnum, char action)
{
	long int	time;

	time = ft_time_dif(a->s_timer, ft_get_time());
	sem_wait(a->print);
	if (!a->deaths)
	{
		if (action == 'F')
			printf("%ld %ld has taken a fork\n", time, pnum);
		else if (action == 'S')
			printf("%ld %ld is sleeping\n", time, pnum);
		else if (action == 'E')
			printf("%ld %ld is eating\n", time, pnum);
		else if (action == 'T')
			printf("%ld %ld is thinking\n", time, pnum);
		else if (action == 'D')
			printf("%ld %ld died\n", time, pnum);
	}
	sem_post(a->print);
}
