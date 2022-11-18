/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 18:56:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/11/18 02:42:32 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include "../../includes/multithread.h"

static void	run_thread_batch(t_thread	info[], void *(*apply)(void *))
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

// clear all data stored to prepare a new frame
static inline void	print_clr_to_screen(t_thread *t, t_color clr, int x, int y)
{
	int		pos;
	char	*pixel;
	t_image	*img;

	img = t->app->img;
	if (t->app->out_fd != 0)
	{
		t->data[y][x] = clr;
	}
	else
	{
		pos = (y * img->line_length) + (x * (img->bits_per_pixel / 8));
		pixel = img->data + pos;
		*(unsigned int *)pixel = get_trgb(clr);
	}
}

void	*run_thread_pixel(void *thread_info)
{
	t_thread	*t;
	int			y;
	int			x;
	t_color		pix_clr;

	t = thread_info;
	y = t->start;
	while (y < t->end)
	{
		x = 0;
		while (x < W_WIDTH)
		{
			pix_clr = get_pixel_clr(t->scene, (x + 0.5), (y + 0.5));
			pthread_mutex_lock(t->write_mutex);
			t->scene->pix_traced++;
			print_clr_to_screen(t, pix_clr, x, y);
			pthread_mutex_unlock(t->write_mutex);
			x++;
		}
		y++;
	}
	return (t);
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
		thread_list[i].app = app;
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
