/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbendu <sbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:57:06 by sbendu            #+#    #+#             */
/*   Updated: 2022/06/22 12:30:53 by sbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_param	param;
	t_philo	*philo;

	if (argc < 5 || argc > 6)
		return (ft_error("Error: wrong arguments"));
	if (parse_param(argc, argv, &param) == -1)
		return (-1);
	if (phil_set(&param, &philo) == -1)
		return (-1);
	if (param.number_phil == 1)
	{
		printf("0 1 philosopher is thinking\n");
		printf("0 1 philosopher take fork\n");
		printf("%d 1 philosopher died\n", param.time_to_die);
	}
	else
		lunch(philo);
	free(philo);
	free(param.mutex_forks);
	return (0);
}
