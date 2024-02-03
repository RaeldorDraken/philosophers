/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philolib_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 10:59:12 by eros-gir          #+#    #+#             */
/*   Updated: 2023/01/04 12:02:55 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOLIB_BONUS_H
# define PHILOLIB_BONUS_H

# include<stdio.h>
# include<string.h>
# include<stdlib.h>
# include<unistd.h>
# include<sys/time.h>
# include<fcntl.h>
# include<pthread.h>
# include<sys/wait.h>
# include<signal.h>
# include<semaphore.h>

struct	s_args;

typedef struct s_philo
{
	int				l_fork;
	int				r_fork;
	long int		phil_id;
	long int		t_death;
	long int		eat_count;
	struct s_args	*args;
	pthread_t		death;
	pid_t			prc_id;
}	t_philo;

typedef struct s_args
{
	long int		nbr_phil;
	long int		t_to_die;
	long int		t_to_eat;
	long int		t_to_slp;
	long int		nb_t_eat;
	long int		s_timer;
	long int		timer;
	int				deaths;
	int				tummy_full;
	sem_t			*ate_chk;
	sem_t			*forks;
	sem_t			*print;
	t_philo			philos[255];
}	t_args;

void		eat_sleep_think(long int time, t_args *args);
void		ft_print_phil(t_args *a, long int pnum, char action);
void		*phil_proc(void *void_phil);
void		init_philos(t_args *args);
void		end_loop(t_args *args);
void		*death_check(void *void_phil);
int			ft_isdigit(int c);
int			convert_input(int ac, char **av, t_args *args);
int			initialize_structures(t_args *args, char **av, int ac);
int			start_mutex(t_args *args);
long int	ft_atol(char *input);
long int	ft_get_time(void);
long int	ft_set_delta_time(t_args *args);
long int	ft_time_dif(long int first, long int second);

#endif
