/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithread.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:25:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/11/18 02:44:01 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MULTITHREAD_H
# define MULTITHREAD_H

# ifndef THREAD_NUMBER
#  define THREAD_NUMBER 5
# endif

# include <pthread.h>
# include <sys/time.h>
# include "minirt.h"

typedef struct s_thread_v
{
	pthread_t		thread_id;
	t_color			**data;
	t_scene			*scene;
	t_app			*app;
	int				start;
	int				end;
	pthread_mutex_t	*write_mutex;
}	t_thread;

void	*run_thread_pixel(void *thread_info);
void	run_threads(void *(*apply)(void *), t_app *app, t_color **clrs);
#endif
