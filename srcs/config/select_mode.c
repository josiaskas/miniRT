/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:56:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/11/18 15:22:24 by jkasongo         ###   ########.fr       */
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

void	sphere_edition(t_hittable *sphere)
{
	t_color	color;
	t_v3	translate;
	t_v3	scale;
	double	r;

	scale = sphere->scale;
	color = sphere->material.main;
	printf("\033[0;31m-- Sphere Edition --\033[0m\nName: %s\n", sphere->name);
	printf("Apply Translation to this position: (%lf, %lf, %lf)\n",
		sphere->trans.x, sphere->trans.y, sphere->trans.z);
	get_trans_vector(&translate);
	translate = v3_add(sphere->trans, translate);
	get_line_double("Radius scale (1 to keep)", &r);
	get_line_color(&color);
	sphere->material.main = color;
	scale = v3_multi(r, scale);
	transform_sphere(sphere, translate, (t_v3){0, 0, 0}, scale);
}

void	plan_edition(t_hittable *plan)
{
	t_color	color;
	t_v3	translate;
	t_v3	angles;

	color = plan->material.main;
	printf("\033[0;31m-- Plan Edition --\033[0m\nName: %s\n", plan->name);
	printf("Apply Translation to this position: (%lf, %lf, %lf)\n",
		plan->trans.x, plan->trans.y, plan->trans.z);
	get_trans_vector(&translate);
	translate = v3_add(plan->trans, translate);
	angles = v3_multi(57.2957795131, plan->angles);
	printf("> Current object world rotation angles x: %lf, y: %lf, z: %lf)\n",
		angles.x, angles.y, angles.z);
	get_line_angles(&angles);
	get_line_color(&color);
	plan->material.main = color;
	transform_plane(plan, translate, angles, (t_v3){1, 1, 1});
}

void	start_edition(t_app *app)
{
	t_hittable	*obj;

	obj = app->conf.selected_obj;
	app->conf.status = 0;
	if (obj->type == e_hit_sphere)
		sphere_edition(obj);
	else if (obj->type == e_hit_cylinder)
		cylinder_edition(obj);
	else if (obj->type == e_hit_plane)
		plan_edition(obj);
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
