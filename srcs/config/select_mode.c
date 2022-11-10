/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:56:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/10/23 14:49:50 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

static inline t_hittable	*find_selected_object(t_scene	*scn, int x, int y)
{
	t_array	*records;
	t_hit	*first;
	t_ray	*ray;

	ray = ray_for_pixel(scn->selected_camera, x, y);
	records = do_intersect_objs(scn, ray);
	first = get_first_obj_hit(records, RAY_T_MAX, 0);
	if (first)
		return (first->object);
	ft_free_d_array(records);
	free(ray);
	return (NULL);
}

static	inline void	sphere_edition(t_hittable *sphere)
{
	t_color	color;
	t_v3	translate;
	t_v3	scale;
	double	r;

	scale = (t_v3){1, 1, 1};
	r = 1;
	printf("\033[0;31m-- Sphere Edition --\033[0m\nName: %s", sphere->name);
	printf("Current position: (%lf, %lf, %lf)\n",
		   sphere->trans.x, sphere->trans.y, sphere->trans.z);
	get_line_vector("translation", &translate);
	printf("Current scale(equal for a perfect sphere): (%lf, %lf, %lf)\n",
		   sphere->scale.x, sphere->scale.y, sphere->scale.z);
	get_line_double("scale-radius", &r);
	get_line_color(&color);
	sphere->material.main = color;
	scale = v3_multi(r, scale);
	transform_sphere(sphere, translate, (t_v3){0, 0, 0}, scale);
}

static	inline void	start_edition(t_app *app)
{
	t_hittable	*obj;

	obj = app->conf.selected_obj;
	app->conf.status = 0;
	if (obj->type == e_hit_sphere)
		sphere_edition(obj);
	app->conf.status = 0;
	app->conf.selected_obj = NULL;
	render(app);
	app->conf.c_mode = e_normal_mode;
	app->conf.rerender = true;
	printf("\033[0;31m\n-- End --\033[0m\n");
}

void	start_selecting_mode(t_app *app, int x, int y)
{
	t_hittable	*obj;

	if (app->conf.selected_obj != NULL)
		start_edition(app);
	else
	{
		obj = find_selected_object(app->scene, x, y);
		if (obj)
		{
			app->conf.selected_obj = obj;
			start_edition(app);
		}
		else
			printf("No object found at that position, try again\n");
	}
}
