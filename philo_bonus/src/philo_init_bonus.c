/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 19:05:26 by eros-gir          #+#    #+#             */
/*   Updated: 2023/01/25 10:48:45 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../incl/philolib_bonus.h"

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
		|| args->nbr_phil > 255)
		return (1);
	return (0);
}

int	start_semaphore(t_args *args)
{
	sem_unlink("ph_forks");
	sem_unlink("ph_print");
	sem_unlink("ph_ate");
	args->ate_chk = sem_open("ph_ate", O_CREAT, S_IRWXU, args->nbr_phil);
	args->forks = sem_open("ph_forks", O_CREAT, S_IRWXU, args->nbr_phil);
	args->print = sem_open("ph_print", O_CREAT, S_IRWXU, 1);
	if (args->forks == NULL || args->print == NULL || args->ate_chk == NULL)
		return (1);
	return (0);
}

void	init_philos(t_args *args)
{
	int	i;

	i = args->nbr_phil;
	while (--i >= 0)
	{
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
	if (start_semaphore(args))
		return (3);
	init_philos(args);
	return (0);
}
