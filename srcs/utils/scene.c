/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 14:30:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/11/10 18:17:00 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

void	print_progress(int count)
{
	double	percentage;
	int		val;
	int		lpad;
	int		rpad;

	percentage = (double)count / (((double)W_HEIGHT - 1) * (double)W_WIDTH);
	val = (int)(percentage * 100);
	lpad = (int)(percentage * PBWIDTH);
	rpad = PBWIDTH - lpad;
	printf("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
}

inline t_scene	*init_scene(void)
{
	t_scene	*scene;

	scene = NULL;
	scene = (t_scene *)ft_calloc(1, sizeof(t_scene));
	if (scene)
	{
		scene->hittable = ft_new_array();
		scene->lights = ft_new_array();
		scene->cameras = ft_new_array();
		scene->ambiant.intensity = 0;
		scene->names = ft_new_array();
	}
	return (scene);
}

// destroy hittable, lights and cameras on the scene
void	free_scene(t_scene *scene)
{
	if (scene)
	{
		ft_free_d_array(scene->hittable);
		ft_free_d_array(scene->lights);
		ft_free_d_array(scene->cameras);
		ft_free_d_array(scene->names);
		free(scene);
	}
}
