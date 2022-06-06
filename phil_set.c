/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbendu <sbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:01:06 by sbendu            #+#    #+#             */
/*   Updated: 2022/06/06 12:35:34 by sbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_phil(t_philo *philo, t_param *param, int i, pthread_mutex_t *forks)
{
	philo->index = i;
	philo->param = param;
	philo->eat_count = 0;
	philo->time_of_eat = get_time();
	philo->alive = 1;
	if (i == 0)
	{
		philo->fork_left = forks + param->number_phil - 1;
		philo->fork_right = forks;
	}
	else
	{
		philo->fork_left = forks + i - 1;
		philo->fork_right = forks + i;
	}
}

static int	init_forks(t_param *param)
{
	int	i;

	i = -1;
	param->mutex_forks = (pthread_mutex_t *)ft_calloc(\
			param->number_phil, sizeof(pthread_mutex_t));
	if (!param->mutex_forks)
		return (-1);
	while (++i < param->number_phil)
	{
		if (pthread_mutex_init((param->mutex_forks + i), NULL))
		{
			while (--i >= 0)
				pthread_mutex_destroy(&param->mutex_forks[i]);
			free(param->mutex_forks);
			return (ft_error("Error:mutex_forks_init"));
		}	
	}
	return (0);
}

int	phil_set(t_param *param, t_philo **phil)
{
	int		i;
	t_philo	*tmp;

	if (init_forks(param) == -1)
		return (-1);
	tmp = (t_philo *)ft_calloc(sizeof(t_philo), \
					param->number_phil);
	if (tmp == NULL)
		return (ft_error("Error: ft_calloc philo"));
	i = -1;
	while (++i < param->number_phil)
		init_phil(tmp + i, param, i, param->mutex_forks);
	*phil = tmp;
	return (0);
}
