/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbendu <sbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:57:06 by sbendu            #+#    #+#             */
/*   Updated: 2022/05/17 11:44:24 by sbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_param	param;
	t_philo	*philo;
	
	if (argc < 5 || argc > 6)
		return(ft_error("Error: wrong arguments"));
	parse_param(argc, argv, &param);
	if (phil_set(&param, &philo) == -1)
		return(-1);
	if (lunch(philo))
		return (-1);
	return (0);
}
