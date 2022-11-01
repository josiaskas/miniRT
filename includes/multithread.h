/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithread.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:25:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/10/31 18:56:44 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MULTITHREAD_H
# define MULTITHREAD_H

# ifndef THREAD_NUMBER
#  define THREAD_NUMBER 4
# endif

# include <pthread.h>
# include <sys/time.h>
# include "raytrace.h"

typedef struct s_thread_v
{
	pthread_t		thread_id;
	t_color			**data;
	t_scene			*scene;
	int				start;
	int				end;
	pthread_mutex_t	*write_mutex;
}	t_thread;

void	run_threads(void *(*apply)(void *), t_scene *scn, t_color **clrs);
#endif
