/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbendu <sbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:57:06 by sbendu            #+#    #+#             */
/*   Updated: 2022/06/04 13:40:31 by sbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_param	param;
	t_philo	*philo;
	int		status;

	if (argc < 5 || argc > 6)
		return (ft_error("Error: wrong arguments"));
	parse_param(argc, argv, &param);
	if (phil_set(&param, &philo) == -1)
		return (-1);
	status = lunch(philo);
	free(philo);
	free((&param)->mutex_forks);
	return (status);
}
