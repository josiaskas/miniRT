/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 18:54:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/10/05 21:21:22 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_raytracing(t_app *app)
{
	size_t	i;
	t_scene	*scene;

	app->error_code = 0;
	app->error_message = NULL;
	scene = app->scene;
	if (app->data)
		free_array((void **)app->data, W_HEIGHT);
	app->data = (t_color **)ft_calloc((W_HEIGHT), sizeof(t_color *));
	i = 0;
	while (i < W_HEIGHT)
		app->data[i++] = ft_calloc(W_WIDTH, sizeof (t_color));
	if (!scene->selected_camera)
		scene->selected_camera = ft_get_elem(scene->cameras, 0);
}

//t_color	get_pixel_data(t_scene *scene, double x, double y)
//{
//	t_color	color;
//	t_cam	*camera;
//	t_ray	*ray;
//
//	camera = scene->selected_camera;
//	ray = get_viewport_ray(640, 319, camera);
//	printf("orgin: (%lf, %lf, %lf) dir: (%lf, %lf, %lf)\n",
//		   ray->o.x,ray->o.y,ray->o.z,
//		   ray->dir.x,ray->dir.y,ray->dir.z);
//	//color = do_tracing(scene, ray, RAY_T_MAX);
//	(void)x;
//	(void)y;
//	color = v4(1,0,0,1);
//	free(ray);
//	return (color);
//}

bool	render(t_app *app)
{
	init_raytracing(app);

	t_ray	*a = NULL;
	t_ray	*b = NULL;
	t_hittable *sphere = ft_get_elem(app->scene->hittable, 0);
	if (sphere != NULL)
	{
		a = build_ray(v3(0,0,-5), v3(0,0,1));
		transform_sphere(sphere, v3(0,0,-1), v3(0,0,0), v3(2,2,2));
		t_hit *hit = do_intersect(a, sphere);
		if (hit)
		{
			printf("ray O:(%lf, %lf, %lf) V:(%lf, %lf, %lf)\n",
				   a->o.x,a->o.y,a->o.z,
				   a->dir.x,a->dir.y,a->dir.z);
			if (hit->intersection)
			{
				printf("intersected smallest t is %lf of [%lf, %lf]\n",
					   hit->t, hit->t_trace[0], hit->t_trace[1]);
			}
		}
		free(hit);
	}
	free(a);
	free(b);

	return (true);
}
