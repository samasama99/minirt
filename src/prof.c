/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prof.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <orahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 14:39:40 by orahmoun          #+#    #+#             */
/*   Updated: 2022/07/28 14:39:43 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct timeval	t_time;

long	time_now(void)
{
	t_time	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
