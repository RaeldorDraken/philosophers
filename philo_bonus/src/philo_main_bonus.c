/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 10:55:57 by eros-gir          #+#    #+#             */
/*   Updated: 2023/01/25 10:28:11 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../incl/philolib_bonus.h"

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
		write(2, "Error: No Semaphores avaiable\n", 27);
	else if (errno == 4)
		write(2, "Error: Encountered a problem creating processes\n", 27);
	printf("%s%s%s", s[0], s[1], s[2]);
	exit(errno);
}

void	check_input(int ac, char **av)
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
				end_program(2);
		}
	}
}

int	philo_looping(t_args *args)
{
	long int	i;
	t_philo		*phil;

	i = 0;
	phil = args->philos;
	while (i < args->nbr_phil)
	{
		phil[i].prc_id = fork();
		if (phil[i].prc_id < 0)
			return (1);
		else if (phil[i].prc_id == 0)
			phil_proc(&(phil[i]));
		usleep(100);
		i ++;
	}
	end_loop(args);
	return (0);
}

int	main(int ac, char **av)
{
	int		resv;
	t_args	args;

	args.s_timer = ft_get_time();
	args.timer = ft_get_time();
	if (ac < 5 || ac > 6)
		end_program(1);
	check_input(ac, av);
	resv = initialize_structures(&args, av, ac);
	if (resv)
		end_program(resv);
	if (philo_looping(&args) == 1)
		end_program(4);
	usleep(900000);
	return (0);
}
