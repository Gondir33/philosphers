/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lunch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbendu <sbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 19:48:12 by sbendu            #+#    #+#             */
/*   Updated: 2022/06/16 11:33:20 by sbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	show_actions(t_philo *philo, char *message)
{
	int		id;
	long	time;

	time = get_time() - philo->param->time_of_start;
	id = philo->index + 1;
	pthread_mutex_lock(&philo->param->mutex_printf);
	printf("%lu philosopher %d %s\n", time, id, message);
	pthread_mutex_unlock(&philo->param->mutex_printf);
}

void	check_monitor(t_philo *philo)
{
	int		i;
	int		flag_all_eat;

	i = -1;
	flag_all_eat = 0;
	while (++i < philo->param->number_phil)
	{
		if (get_time() - (philo + i)->time_of_eat > philo->param->time_to_die)
		{
			show_actions(philo + i, "is died");
			philo->param->stop = 0;
			break ;
		}
		if ((philo + i)->eat_count >= philo->param->number_of_times)
			flag_all_eat++;
	}
	if (flag_all_eat == philo->param->number_phil)
		philo->param->stop = 0;
}

static void	*get_start(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (philo->param->stop && philo->eat_count \
		!= philo->param->number_of_times)
	{
		show_actions(philo, "is thinking");
		pthread_mutex_lock(philo->fork_left);
		show_actions(philo, "has taken fork");
		pthread_mutex_lock(philo->fork_right);
		show_actions(philo, "has taken fork");
		philo->time_of_eat = get_time();
		show_actions(philo, "is eating");
		my_usleep(philo->param->time_to_eat, philo->param);
		pthread_mutex_unlock(philo->fork_right);
		pthread_mutex_unlock(philo->fork_left);
		if (philo->param->stop)
			philo->eat_count++;
		show_actions(philo, "is sleeping");
		my_usleep(philo->param->time_to_sleep, philo->param);
	}
	return (0);
}

int	lunch(t_philo *philo)
{
	int	i;
	int	num;

	philo->param->time_of_start = get_time();
	i = -1;
	num = philo->param->number_phil;
	while (++i < num)
	{
		(philo + i)->time_of_eat = get_time();
		if (pthread_create(&((philo + i)->pth), \
					NULL, &get_start, philo + i))
			return (ft_error("Error: philo_pthread_create"));
		pthread_detach((philo + i)->pth);
		usleep(50);
	}
	while (philo->param->stop)
		check_monitor(philo);
	i = -1;
	while (++i < num)
		pthread_mutex_destroy(&philo->param->mutex_forks[i]);
	pthread_mutex_destroy(&philo->param->mutex_printf);
	return (0);
}
