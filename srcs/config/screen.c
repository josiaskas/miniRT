/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 18:56:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/09/29 18:56:04 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

int	write_info_section(t_app *app, void *mlx, void *win)
{
	int		y;
	int		x;
	char	*fov;
	char	*cam_nbr;

	y = 400;
	x = 1100;
	mlx = app->mlx;
	win = app->window;
	fov = ft_itoa((int)(round(app->scene->selected_camera->fov)));
	cam_nbr = ft_itoa((int)(app->scene->cam_cursor + 1));
	mlx_string_put(mlx, win, x, y += 20, BLUE_LIGHT2, app->file_name);
	if (app->conf.c_mode == 0 || app->conf.c_mode == 2)
		mlx_string_put(mlx, win, (x + 15), y += 30, BLUE_LIGHT, "Normal Mode");
	else if (app->conf.c_mode == e_select_mode)
		mlx_string_put(mlx, win, (x + 15), y += 30, RED_L, "Edition Mode");
	if (app->conf.c_mode == e_clock_wise_mode)
		mlx_string_put(mlx, win, (x + 15), y += 30, RED_L, "clock wise");
	mlx_string_put(mlx, win, (x + 15), y += 40, BLUE_LIGHT2, "fov:");
	mlx_string_put(mlx, win, (x + 50), y, RED_L, fov);
	mlx_string_put(mlx, win, (x + 15), y += 40, WHITE, "cam:");
	mlx_string_put(mlx, win, (x + 50), y, RED_L, cam_nbr);
	free(fov);
	free(cam_nbr);
	return (0);
}

void	light_edition(t_light *light, size_t i)
{
	t_color	color;
	t_v3	translate;
	double	cd;

	color = light->color;
	printf("\033[0;31m-- Light Edition --\033[0m\nLight: %ld\n", i);
	printf("> Apply Translation to this position: (%lf, %lf, %lf)\n",
		light->o.x, light->o.y, light->o.z);
	get_trans_vector(&translate);
	translate = v3_add(light->o, translate);
	get_line_color(&color);
	printf("> Current cd: %lf\n", light->cd);
	get_line_double("New cd:", &cd);
	if (cd > 1)
		cd = 1;
	light->cd = cd;
	light->color = v4_multi(light->cd, color);
	printf("\033[0;31m\n-- End --\033[0m\n");
}

void	cylinder_edition(t_hittable *cyl)
{
	t_color	color;
	t_v3	translate;
	t_v3	ang;
	double	conf[2];

	color = cyl->material.main;
	printf("\033[0;31m-- Cylinder Edition --\033[0m\nName: %s\n", cyl->name);
	printf("> Apply Translation to this position: (%lf, %lf, %lf)\n",
		cyl->trans.x, cyl->trans.y, cyl->trans.z);
	get_trans_vector(&translate);
	translate = v3_add(cyl->trans, translate);
	ang = v3_multi(57.2957795131, cyl->angles);
	printf("> Current object world rotation angles x: %lf, y: %lf, z: %lf)\n",
		ang.x, ang.y, ang.z);
	get_line_angles(&ang);
	get_line_double("Radius scale (1 to keep)", &conf[0]);
	get_line_double("H scale (1 to keep)", &conf[1]);
	get_line_color(&color);
	cyl->material.main = color;
	cyl->radius = conf[0] * cyl->radius;
	cyl->h = conf[1] * cyl->h;
	transform_cy(cyl, translate, ang, (t_v3){1, 1, 1});
}
