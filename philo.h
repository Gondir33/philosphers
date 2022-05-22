/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbendu <sbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:57:22 by sbendu            #+#    #+#             */
/*   Updated: 2022/05/21 19:23:44 by sbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_param
{
	int				number_phil;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times;
	long			time_of_start;
	int 			stop;
	int				number_die;
	pthread_mutex_t	*mutex_forks;
	pthread_t		check_alive;
}t_param;

typedef struct s_philo
{
	int				index;
	long			time_of_eat;
	int				eat_count;
	int				alive;
	t_param			*param;
	pthread_t		pth;
	pthread_mutex_t *fork_right;
	pthread_mutex_t *fork_left;
}t_philo;

void	parse_param(int argc, char **argv, t_param	*param);
int		phil_set(t_param *param, t_philo **phil);

int		lunch(t_philo *philo);

long	get_time();
int		ft_error(char *s);

#endif