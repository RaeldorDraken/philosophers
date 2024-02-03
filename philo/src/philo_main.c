/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 10:55:57 by eros-gir          #+#    #+#             */
/*   Updated: 2023/03/18 00:22:56 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../incl/philolib.h"

//errno:
//	1 = wrong number of arguments; 2 = arguments on wrong forma;t
void	end_program(int errno)
{
	char	*s[3];

	s[0] = "Input format (only unsigned int): ./philo number_of_philosophers ";
	s[1] = "time_to_die time_to_eat time_to_sleep ";
	s[2] = "[number_of_times_each_philosiopher_must_eat]\n";
	if (errno == 1)
		write(2, "Error: Wrong number of arguments\n", 33);
	else if (errno == 2)
		write(2, "Error: Arguments are invalid\n", 29);
	else if (errno == 3)
		write(2, "Error: Mutex uninitialized\n", 27);
	printf("%s%s%s", s[0], s[1], s[2]);
}

int	check_input(int ac, char **av)
{
	int	i;
	int	j;

	i = 0;
	while (++i < ac)
	{
		j = -1;
		while (av[i][++j] != '\0')
		{
			if (!ft_isdigit(av[i][j]))
			{
				end_program(2);
				return (2);
			}
		}
	}
	return (0);
}

void	philo_looping(t_args *args)
{
	long int	d_time;
	long int	i;
	t_philo		*philo;

	i = 0;
	philo = args->philos;
	d_time = ft_set_delta_time(args);
	while (i < args->nbr_phil)
	{
		if (pthread_create(&(philo[i].thread_id), NULL, phil_proc, &(philo[i])))
			return ;
		philo[i].t_death = ft_get_time();
		i ++;
	}
	death_check(args, args->philos);
	end_loop(args, philo);
}

int	main(int ac, char **av)
{
	int		resv;
	t_args	args;

	args.s_timer = ft_get_time();
	args.timer = ft_get_time();
	if (ac < 5 || ac > 6)
	{
		end_program(1);
		return (1);
	}
	resv = check_input(ac, av);
	if (resv)
		return (resv);
	resv = initialize_structures(&args, av, ac);
	if (resv)
	{
		end_program(resv);
		return (resv);
	}
	philo_looping(&args);
	return (0);
}
