/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithread.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:25:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/09/21 17:36:04 by jkasongo         ###   ########.fr       */
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
	pthread_t	thread_id;
	t_color		**data;
	int			x;
	int			y;
	t_scene		*scene;
}	t_thread;

void	run_threads(void* (*apply)(void *), t_scene *scn, t_color **clrs);
#endif //MULTITHREAD_H
