/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lunch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbendu <sbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 19:48:12 by sbendu            #+#    #+#             */
/*   Updated: 2022/05/17 11:41:24 by sbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/*
static long	time_sleep(t_philo *philo)
{
	long	time_for_die;

	time_for_die = philo->param->time_to_die - \
		philo->param->time_to_eat - philo->param->time_to_sleep;
	if (time_for_die)
}
*/
static void	show_actions(t_philo *philo, char *message)
{
	int		id;
	long	time;

	time = get_time() - philo->param->time_of_start;
	id = philo->index;
	printf("%lu %d philosopher %s", time, id, message);
}

static void check_die(t_philo *philo)
{
	long	last_eat;
	long	tmp;
	long	think;
	
	last_eat = get_time() - philo->time_of_eat;
	tmp = philo->param->time_to_eat + philo->param->time_to_sleep;
	if (last_eat >= tmp)
	{
		show_actions(philo, "is thinking");
		think = last_eat - tmp;
		usleep(think);
	}
	else
	{
		show_actions(philo, "died");
		philo->alive = 0;
	}
}

static void *get_start(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (philo->alive && philo->eat_count != philo->param->number_of_times)
	{
		pthread_mutex_lock(philo->fork_left);
		show_actions(philo, "take fork");
		pthread_mutex_lock(philo->fork_right);
		show_actions(philo, "take fork");
		show_actions(philo, "is eating");
		usleep(philo->param->time_to_eat);
		philo->time_of_eat = get_time();
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
		++philo->eat_count;
		show_actions(philo, "is sleeping");
		usleep(philo->param->time_to_sleep); // исправить потом
		check_die(philo);
	}
	return (0);
}

int	lunch(t_philo *philo)
{
	int	i;

	philo->param->time_of_start = get_time();
	i = -1;
	while (++i < philo->param->number_phil)
	{
		if (i % 2 == 0)
		{
			if (pthread_create(&((philo + i)->pth), NULL, get_start, philo))
				return (ft_error("Error: philo_pthread_create"));
			pthread_detach((philo + i)->pth);
		}
	}
	i = -1;
	while (++i < philo->param->number_phil)
	{
		if (i % 2 == 1)
		{
			if (pthread_create(&((philo + i)->pth), NULL, get_start, philo))
				return (ft_error("Error: philo_pthread_create"));
			pthread_detach((philo + i)->pth);
		}
	}
	i = -1;
	while (++i < philo->param->number_phil)
		pthread_mutex_destroy(&philo->param->mutex_forks[i]);
	return (0);
}