/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 18:53:23 by eros-gir          #+#    #+#             */
/*   Updated: 2023/01/30 12:20:56 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../incl/philolib.h"

void	eat_action(t_philo *philo)
{
	t_args	*args;

	args = philo->args;
	pthread_mutex_lock(&args->forks[philo->l_fork]);
	ft_print_phil(args, philo->phil_id, 'F');
	pthread_mutex_lock(&args->forks[philo->r_fork]);
	ft_print_phil(args, philo->phil_id, 'F');
	pthread_mutex_lock(&args->ate_chk);
	ft_print_phil(args, philo->phil_id, 'E');
	philo->t_death = ft_get_time();
	pthread_mutex_unlock(&args->ate_chk);
	eat_sleep_think(args->t_to_eat, args);
	philo->eat_count ++;
	pthread_mutex_unlock(&args->forks[philo->l_fork]);
	pthread_mutex_unlock(&args->forks[philo->r_fork]);
}

void	end_loop(t_args *args, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < args->nbr_phil)
	{
		pthread_mutex_unlock(&args->forks[philo[i].l_fork]);
		pthread_mutex_unlock(&args->forks[philo[i].r_fork]);
		pthread_join(philo[i].thread_id, NULL);
	}
	i = -1;
	while (++i < args->nbr_phil)
		pthread_mutex_destroy(&args->forks[i]);
	pthread_mutex_destroy(&args->printing);
}

void	death_check(t_args *args, t_philo *philo)
{
	int	i;

	while (!args->tummy_full)
	{
		i = -1;
		while (++i < args->nbr_phil && !args->deaths)
		{
			pthread_mutex_lock(&args->ate_chk);
			if (ft_time_dif(philo->t_death, ft_get_time()) > args->t_to_die)
			{
				ft_print_phil(args, i, 'D');
				args->deaths ++;
			}
			pthread_mutex_unlock(&args->ate_chk);
			usleep(100);
		}
		if (args->deaths)
			break ;
		i = 0;
		while (args->nb_t_eat != -1 && i < args->nbr_phil
			&& philo[i].eat_count >= args->nb_t_eat)
			i ++;
		if (i >= args->nbr_phil)
			args->tummy_full ++;
	}
}

void	*phil_proc(void *void_phil)
{
	int		i;
	t_philo	*philo;
	t_args	*args;

	i = 0;
	philo = (t_philo *)void_phil;
	args = philo->args;
	if (philo->phil_id % 2)
		usleep(15000);
	while (!args->deaths)
	{
		eat_action(philo);
		if (args->tummy_full)
			break ;
		ft_print_phil(args, philo->phil_id, 'S');
		eat_sleep_think(args->t_to_slp, args);
		ft_print_phil(args, philo->phil_id, 'T');
		i ++;
	}
	return (NULL);
}
