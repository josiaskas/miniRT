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

static void	run_thread_batch(t_thread	info[], void* (*apply)(void *))
{
	int			nb_t;

	nb_t = 0;
	while (nb_t < THREAD_NUMBER)
	{
		pthread_create(&info[nb_t].thread_id, NULL, apply, &info[nb_t]);
		nb_t++;
	}
	while (nb_t >= 0)
	{
		pthread_join(info[nb_t].thread_id, NULL);
		nb_t--;
	}
	return ;
}

void	run_threads(void *(*apply)(void *), t_app *app, t_color **clrs)
{
	int				i;
	double			delta;
	t_thread		thread_list[THREAD_NUMBER];
	pthread_mutex_t	*write;

	delta = (W_HEIGHT) / THREAD_NUMBER;
	write = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
	i = 0;
	while (i < THREAD_NUMBER)
	{
		thread_list[i].scene = app->scene;
		thread_list[i].app =  app;
		thread_list[i].data = clrs;
		thread_list[i].start = delta * i;
		thread_list[i].end = thread_list[i].start + delta;
		thread_list[i].write_mutex = write;
		i++;
	}
	run_thread_batch(thread_list, apply);
	pthread_mutex_destroy(write);
	free(write);
}
