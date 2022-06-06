/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbendu <sbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 13:37:44 by sbendu            #+#    #+#             */
/*   Updated: 2022/06/06 13:59:34 by sbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	odd_check(t_philo *philo)
{
	if (philo->index % 2 == 1)
	{
		if (philo->param->time_to_die < \
			philo->param->time_to_eat)
		{
			usleep(philo->param->time_to_die * 1000);
			show_actions(philo, "died");
			philo->alive = 0;
		}
	}
}

static void	last_check(t_philo *philo)
{
	if (philo->param->number_phil % 2 == 1)
	{
		if (philo->index == philo->param->number_phil - 1)
		{
			if (philo->param->time_to_die < \
				philo->param->time_to_eat)
			{
				usleep(philo->param->time_to_die * 1000);
				show_actions(philo, "died");
				philo->alive = 0;
			}
		}
		if (philo->index == philo->param->number_phil - 2)
		{
			if (philo->param->time_to_die < \
				2 * philo->param->time_to_eat)
			{
				usleep(philo->param->time_to_die * 1000);
				show_actions(philo, "died");
				philo->alive = 0;
			}
		}
	}
}

void	smart_think(t_philo *philo)
{
	odd_check(philo);
	last_check(philo);
}
