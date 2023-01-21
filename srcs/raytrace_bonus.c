/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 14:54:39 by jkasongo          #+#    #+#             */
/*   Updated: 2022/11/18 02:20:12 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../includes/multithread.h"

inline t_color	shade_hit(t_scene *world, t_hit *hit)
{
	t_color	color;
	t_light	*light;
	size_t	i;

	color = (t_v4){0, 0, 0, 1};
	i = 0;
	while (i < world->lights->length)
	{
		light = ft_get_elem(world->lights, i);
		color = v4_add(color, lighting(world, hit, light));
		i++;
	}
	return (color);
}

t_color	get_pixel_clr(t_scene *scn, double x, double y)
{
	t_color	color;
	t_cam	*cam;
	t_hit	first_hit;
	t_ray	ray;

	color = (t_v4){0, 0, 0, 1};
	cam = (t_cam *)scn->selected_camera;
	ray = ray_for_pixel(cam, x, y);
	first_hit = get_first_obj_hit(scn, ray, 5000, RAY_T_MIN);
	if (first_hit.intersection)
	{
		ft_compute_hit(&first_hit);
		color = shade_hit(scn, &first_hit);
	}
	return (color);
}

bool	render(t_app *app)
{
	app->scene->pix_traced = 0;
	run_threads(run_thread_pixel, app, app->data);
	app->scene->pix_traced = 0;
	app->conf.rerender = true;
	if (app->out_fd != 0)
		printf("\nRaytracing finished\n");
	return (true);
}
