/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 18:56:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/10/05 19:33:22 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include "../../includes/multithread.h"

static int	run_thread_batch(int x, int y, t_thread	info[], void* (*apply)(void *))
{
	int			nb_t;

	nb_t = 0;
	while ((nb_t < THREAD_NUMBER) && (x < W_WIDTH))
	{
		info[nb_t].x = x;
		info[nb_t].y = y;
		pthread_create(&info[nb_t].thread_id, NULL, apply, &info[nb_t]);
		nb_t++;
		x++;
	}
	while (nb_t >= 0)
	{
		pthread_join(info[nb_t].thread_id, NULL);
		nb_t--;
	}
	return (x);
}

void	run_threads(void *(*apply)(void *), t_scene *scn, t_color **clrs)
{
	int			x;
	int			y;
	int			i;
	t_thread	thread_list[THREAD_NUMBER];

	i = 0;
	while (i < THREAD_NUMBER)
	{
		thread_list[i].scene = scn;
		thread_list[i].data = clrs;
		i++;
	}
	y = 0;
	while (y < W_HEIGHT)
	{
		x = 0;
		while (x < W_WIDTH)
			x = run_thread_batch(x, y, thread_list, apply);
		y++;
	}
}
