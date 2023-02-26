/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks_suite.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:04:27 by jkasongo          #+#    #+#             */
/*   Updated: 2023/01/17 23:06:20 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "parser.h"

static void	select_plan_mode(t_app *app)
{
	static int	plan_mode = 0;
	int			left;

	plan_mode++;
	left = plan_mode % 3;
	if (left == 0)
		app->conf.c_mode = e_normal_mode;
	else if (left == 1)
		app->conf.c_mode = e_x_z_mode;
	else
		app->conf.c_mode = e_z_y_mode;
	app->conf.rerender = true;
	render_image(app);
}

static void	light_edition(t_light *light, size_t i)
{
	t_color	color;
	t_v3	translate;

	color = light->color;
	printf("\033[0;31m-- Editing Light: %ld --\033[0m\n", (i + 1));
	printf("> Current light position: (%lf, %lf, %lf)\n",
		light->o.x, light->o.y, light->o.z);
	get_trans_vector(&translate);
	translate = v3_add(light->o, translate);
	light->o = translate;
	printf("Do you want to change the color of the light ? (y/n)\n");
	if (get_line_bool("select"))
	{
		printf("> Current light color: (%lf, %lf, %lf)\n",
			color.r, color.g, color.b);
		get_line_color(&color);
		light->color = color;
	}
	printf("\033[0;31m-- Light: %ld edited --\033[0m\n", (i + 1));
}

static void	select_light_edition(int key, t_app *app)
{
	t_array	*lights;
	t_light	*light;
	size_t	i;

	lights = app->scene->lights;
	if (MAIN_PAD_1 <= key && key <= MAIN_PAD_9)
	{
		light = NULL;
		i = key - MAIN_PAD_1;
		light = (t_light *)ft_get_elem(lights, i);
		if (light)
		{
			light_edition(light, (key - MAIN_PAD_1));
			app->conf.rerender = true;
			render_image(app);
		}
		else
			printf("No light at index %ld", i);
	}
}

static void	move_camera_eye(int key, t_app *app)
{
	t_v3	eye;
	t_cam	*cam;

	cam = app->scene->selected_camera;
	eye = cam->eye;
	if (key == MAIN_PAD_D)
		eye.x += 1.0;
	else if (key == MAIN_PAD_A)
		eye.x -= 1.0;
	else if (key == MAIN_PAD_R)
		eye.y += 1.0;
	else if (key == MAIN_PAD_F)
		eye.y -= 1.0;
	else if (key == MAIN_PAD_W)
		eye.z += 1.0;
	else
		eye.z -= 1.0;
	move_camera(cam, eye, cam->look_at);
	app->conf.rerender = true;
	render_image(app);
}

int	key_pressed_hook_suite(int key, t_app *app)
{
	if (key == MAIN_PAD_V && app->conf.c_mode != e_select_mode)
		select_plan_mode(app);
	else if (MAIN_PAD_1 <= key && key <= MAIN_PAD_9)
		select_light_edition(key, app);
	else if (key == MAIN_PAD_W || key == MAIN_PAD_S || key == MAIN_PAD_A
		|| key == MAIN_PAD_D || key == MAIN_PAD_R || key == MAIN_PAD_F)
		move_camera_eye(key, app);
	return (0);
}
