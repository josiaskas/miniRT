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
	t_array		*records;
	t_hit		*first;
	t_hittable	*selected;
	t_ray		*ray;

	ray = ray_for_pixel(scn->selected_camera, x, y);
	records = do_intersect_objs(scn, ray);
	first = get_first_obj_hit(records, RAY_T_MAX, 0);
	selected = NULL;
	if (first)
		selected = first->object;
	ft_free_d_array(records);
	free(ray);
	return (selected);
}

static void	change_object_color(t_hittable *obj)
{
	t_v4	color;

	color = obj->material.main;
	printf("> Curent color applied on sphere is : (%lf, %lf, %lf)\n",
		   color.r, color.g, color.b);
	printf("> Set new color \n");
	get_line_color(&color);
	obj->material.main = color;
}

static int	select_edition()
{
	bool	is_selected;
	int		edition;

	is_selected = false;
	edition = 0;
	while (is_selected == false)
	{
		printf("what do you want to do with this object ?\n");
		printf("1. Translate\n");
		printf("2. Rotate\n");
		printf("3. Scale\n");
		printf("4. Change Color\n");
		get_line_int("Select", &edition, 1, 4);
		if (edition > 0 && edition < 5)
			is_selected = true;
		else
			printf("Please select a valid option\n");
	}
	return (edition);
}

static void	edit_objects(t_hittable	*selected_obj)
{
	int		edition;
	bool	quit;

	quit = false;
	while (quit == false)
	{
		edition = select_edition();
		if (edition == 1)
			translate_object(selected_obj);
		else if (edition == 2)
			rotate_object(selected_obj);
		else if (edition == 3)
			scale_object(selected_obj);
		else if (edition == 4)
			change_object_color(selected_obj);
		printf("Do you want to continue editing this object ? (y, n)\n");
		if (get_line_bool("Select") == false)
			quit = true;
	}
	printf("Edited %s \n", selected_obj->name);
}

void	start_selecting_mode(t_app *app, int x, int y)
{
	t_hittable	*obj;

	if (app->conf.selected_obj != NULL)
		printf("Object: %s, already selected \n", app->conf.selected_obj->name);
	else
	{
		obj = find_selected_object(app->scene, x, y);
		if (obj)
		{
			printf("Object: %s, selected \n", obj->name);
			edit_objects(obj);
			app->conf.selected_obj = NULL;
			app->conf.c_mode = e_normal_mode;
			app->conf.rerender = true;
		}
		else
			printf("No object found at that position, try again\n");
	}
}
