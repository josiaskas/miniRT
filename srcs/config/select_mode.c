/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:56:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/10/12 18:56:04 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

static inline t_hittable *find_selected_object(t_scene	*scn, int x, int y)
{
	t_array	*records;
	t_hit	*first;
	t_ray	*ray;

	ray = get_viewport_ray( (x + 0.5), (y + 0.5), scn->selected_camera);
	records = do_intersect_objs(scn, ray, false);
	first = get_first_obj_hit(records, RAY_T_MAX);
	if (first)
		return first->object;
	ft_free_d_array(records);;
	free(ray);
	return(NULL);
}

static	inline void	sphere_edition(t_hittable *sphere)
{
	t_color	color;
	t_v3	translate;
	t_v3	scale;
	double	r;

	scale = v3(1,1,1);
	r = 1;
	get_line_vector("translation", &translate);
	get_line_double("scale-radius", &r);
	get_line_color(&color);
	sphere->color = color;
	scale = v3_multi(r, scale);
	transform_sphere(sphere, translate, v3(0,0,0), scale);
}

static	inline void start_edition(t_app *app)
{
	t_hittable	*obj;

	obj = app->conf.selected_obj;
	printf("\033[0;31m-- Edition of %s --\033[0m\n", obj->name);
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
	app->conf.status = 1;
	if (app->conf.selected_obj != NULL)
		start_edition(app);
	else
	{
		obj = find_selected_object(app->scene, x, y);
		if (obj)
		{
			app->conf.status = 0;
			app->conf.selected_obj = obj;
			start_edition(app);
		}
		else
			printf("No object found at that position, try again\n");
	}
}