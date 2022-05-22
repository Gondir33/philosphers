/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbendu <sbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 15:08:37 by sbendu            #+#    #+#             */
/*   Updated: 2022/05/21 19:09:22 by sbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(char *s)
{
	int len;

	len = 0;
	while (s[len])
		++len;
	write(2, s, len);
	write(2, "\n", 1);
	return (-1);
}

long	get_time()
{
	struct timeval t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}
