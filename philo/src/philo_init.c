/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 19:05:26 by eros-gir          #+#    #+#             */
/*   Updated: 2023/01/10 11:17:35 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../incl/philolib.h"

int	convert_input(int ac, char **av, t_args *args)
{
	args->nbr_phil = ft_atol(av[1]);
	args->t_to_die = ft_atol(av[2]);
	args->t_to_eat = ft_atol(av[3]);
	args->t_to_slp = ft_atol(av[4]);
	if (ac == 6)
		args->nb_t_eat = ft_atol(av[5]);
	else
		args->nb_t_eat = -1;
	if (args->nbr_phil < 1 || args->t_to_die < 0 || args->t_to_eat < 0
		|| args->t_to_slp < 0 || (ac == 6 && args->nb_t_eat < 0)
		|| args->nbr_phil > 250)
		return (1);
	return (0);
}

int	start_mutex(t_args *args)
{
	int	i;

	i = args->nbr_phil;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(args->forks[i]), NULL))
			return (1);
	}
	if (pthread_mutex_init(&(args->ate_chk), NULL))
		return (1);
	if (pthread_mutex_init(&(args->printing), NULL))
		return (1);
	return (0);
}

void	init_philos(t_args *args)
{
	int	i;

	i = args->nbr_phil;
	while (--i >= 0)
	{
		args->philos[i].l_fork = i;
		args->philos[i].r_fork = (i + 1) % args->nbr_phil;
		args->philos[i].phil_id = i;
		args->philos[i].t_death = 0;
		args->philos[i].eat_count = 0;
		args->philos[i].args = args;
	}
}

int	initialize_structures(t_args *args, char **av, int ac)
{
	if (convert_input(ac, av, args))
		return (2);
	args->deaths = 0;
	args->tummy_full = 0;
	if (start_mutex(args))
		return (3);
	init_philos(args);
	return (0);
}
