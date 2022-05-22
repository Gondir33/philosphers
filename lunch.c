/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lunch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbendu <sbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 19:48:12 by sbendu            #+#    #+#             */
/*   Updated: 2022/05/22 09:31:51 by sbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	time_sleep(t_philo *philo)
{
	long	time_for_die;

	time_for_die = philo->param->time_to_die - \
		philo->param->time_to_eat - philo->param->time_to_sleep;
	if (time_for_die < 0)
		return (-(time_for_die + 1));
	return (philo->param->time_to_sleep);
}

static void	show_actions(t_philo *philo, char *message)
{
	int		id;
	long	time;

	time = get_time() - philo->param->time_of_start;
	id = philo->index + 1;
	printf("%lu %d philosopher %s\n", time, id, message);
}

static void check_die(t_philo *philo)
{
	long	last_eat;
	long	tmp;
	
	last_eat = get_time() - philo->time_of_eat;
	if (philo->param->time_to_die < last_eat)
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
		show_actions(philo,"is thinking");
		pthread_mutex_lock(philo->fork_left);
		show_actions(philo, "take fork");
		pthread_mutex_lock(philo->fork_right);
		show_actions(philo, "take fork");
		usleep(philo->param->time_to_eat * 1000);
		show_actions(philo, "ate");
		philo->time_of_eat = get_time();
		pthread_mutex_unlock(philo->fork_right);
		pthread_mutex_unlock(philo->fork_left);
		philo->eat_count++;
		usleep(time_sleep(philo) * 1000);
		show_actions(philo, "slept");
		check_die(philo);
	}
	philo->param->number_die++;
	if (philo->param->number_die == philo->param->number_phil)
		philo->param->stop = 0;
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
			if (pthread_create(&((philo + i)->pth), NULL, &get_start, philo + i))
				return (ft_error("Error: philo_pthread_create"));
			pthread_detach((philo + i)->pth);
			usleep(50);
	}
	while(philo->param->stop);
	i = -1;
	while (++i < num)
		pthread_mutex_destroy(&philo->param->mutex_forks[i]);
	return (0);
}