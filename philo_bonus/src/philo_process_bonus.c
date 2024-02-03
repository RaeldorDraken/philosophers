/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_process_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 18:53:23 by eros-gir          #+#    #+#             */
/*   Updated: 2023/02/16 11:05:19 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../incl/philolib_bonus.h"

void	eat_action(t_philo *philo)
{
	t_args	*args;

	args = philo->args;
	sem_wait(args->forks);
	ft_print_phil(args, philo->phil_id, 'F');
	sem_wait(args->forks);
	ft_print_phil(args, philo->phil_id, 'F');
	sem_wait(args->ate_chk);
	ft_print_phil(args, philo->phil_id, 'E');
	philo->t_death = ft_get_time();
	sem_post(args->ate_chk);
	eat_sleep_think(args->t_to_eat, args);
	philo->eat_count ++;
	sem_post(args->forks);
	sem_post(args->forks);
}

void	end_loop(t_args *args)
{
	int	i;
	int	pwt;

	i = -1;
	while (++i < args->nbr_phil && args->nbr_phil > 1)
	{
		waitpid(-1, &pwt, 0);
		if (pwt != 0)
		{
			i = -1;
			while (++i < args->nbr_phil)
				kill(args->philos[i].prc_id, 15);
			break ;
		}
	}
	sem_close(args->ate_chk);
	sem_close(args->forks);
	sem_close(args->print);
	sem_unlink("ph_forks");
	sem_unlink("ph_ate");
	sem_unlink("ph_print");
}

void	*death_check(void *void_phil)
{
	t_philo	*phil;
	t_args	*args;

	phil = (t_philo *)void_phil;
	args = phil->args;
	while (1)
	{
		sem_wait(args->ate_chk);
		if (ft_time_dif(phil->t_death, ft_get_time()) > args->t_to_die)
		{
			ft_print_phil(args, phil->phil_id, 'D');
			args->deaths ++;
			exit(1);
		}
		sem_post(args->ate_chk);
		if (args->deaths)
			break ;
		usleep(500);
		if (args->nb_t_eat != -1 && phil->eat_count >= args->nb_t_eat)
			break ;
	}
	return (NULL);
}

void	*phil_proc(void *void_phil)
{
	t_philo	*philo;
	t_args	*args;

	philo = (t_philo *)void_phil;
	args = philo->args;
	philo->t_death = ft_get_time();
	pthread_create(&philo->death, NULL, death_check, void_phil);
	if (philo->phil_id % 2)
		usleep(15000);
	while (!args->deaths)
	{
		eat_action(philo);
		if (args->nb_t_eat != -1 && philo->eat_count >= args->nb_t_eat)
			break ;
		ft_print_phil(args, philo->phil_id, 'S');
		eat_sleep_think(args->t_to_slp, args);
		ft_print_phil(args, philo->phil_id, 'T');
	}
	pthread_join(philo->death, NULL);
	if (args->deaths != 0)
		exit(1);
	exit (0);
	return (NULL);
}
