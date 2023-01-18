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

static inline void	write_info_mode(int *x, int *y, t_app *app)
{
	void	*mlx;
	void	*win;

	mlx = app->mlx;
	win = app->window;
	if (app->conf.c_mode == e_normal_mode)
		mlx_string_put(mlx, win, (*x += 15), (*y += 30), BLUE_LIGHT,
			"Normal Mode");
	if (app->conf.c_mode == e_select_mode)
		mlx_string_put(mlx, win, (*x += 15), (*y += 30), RED_L,
			"Edition Mode");
	else if (app->conf.c_mode == e_x_z_mode)
		mlx_string_put(mlx, win, (*x += 15), (*y += 30), RED_L,
			"X - Z Plan mode");
	else if (app->conf.c_mode == e_z_y_mode)
		mlx_string_put(mlx, win, (*x += 15), (*y += 30), RED_L,
			"Z - Y Plan mode");
}

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
	write_info_mode(&x, &y, app);
	mlx_string_put(mlx, win, (x + 15), y += 40, BLUE_LIGHT2, "fov:");
	mlx_string_put(mlx, win, (x + 50), y, RED_L, fov);
	mlx_string_put(mlx, win, (x + 15), y += 40, WHITE, "cam:");
	mlx_string_put(mlx, win, (x + 50), y, RED_L, cam_nbr);
	free(fov);
	free(cam_nbr);
	return (0);
}

void	translate_object(t_hittable *obj)
{
	t_v3	translate;

	if (obj->type == e_hit_sphere || obj->type == e_hit_plane)
	{
		printf("> Apply Translation to this position: (%lf, %lf, %lf)\n",
			obj->o.x, obj->o.y, obj->o.z);
		get_trans_vector(&translate);
		translate = v3_add(obj->o, translate);
		obj->o = translate;
	}
	else if (obj->type == e_hit_cylinder)
	{
		printf("> Curent translation applied on cylinder is : (%lf, %lf, %lf)\n",
			obj->trans.x, obj->trans.y, obj->trans.z);
		get_trans_vector(&translate);
		translate = v3_add(obj->trans, translate);
		transform_cy(obj, translate, obj->angles, obj->scale);
	}
}

void	scale_object(t_hittable *obj)
{
	double	radius;
	double	height;

	if (obj->type == e_hit_sphere || obj->type == e_hit_cylinder)
	{
		printf("> Curent radius applied on object is : %lf\n", obj->radius);
		get_line_double("radius", &radius);
		if (radius > 0)
			obj->radius = radius;
		else
			printf("radius must be > 0, current radius is %lf\n", obj->radius);
	}
	if (obj->type == e_hit_cylinder)
	{
		printf("> Curent height applied on cylinder is : %lf\n", obj->h);
		get_line_double("height", &height);
		if (height > 0)
			obj->h = height;
		else
			printf("height must be > 0, current height is %lf\n", obj->h);
	}
}

void	rotate_object(t_hittable *obj)
{
	t_v4	rotate;
	t_v3	angles;
	t_m4	rot_matrix;

	if (obj->type == e_hit_sphere)
		printf("Can't rotate a sphere\n");
	if (obj->type == e_hit_plane)
	{
		printf("> Set rotation angles \n");
		get_line_angles(&angles);
		rot_matrix = get_tr_matrix((t_v3){0, 0, 0}, angles, (t_v3){1, 1, 1},
				false);
		rotate = multiply_m4_v4(rot_matrix,
				(t_v4){obj->dir.x, obj->dir.y, obj->dir.z, 1});
		obj->dir = (t_v3){rotate.r, rotate.g, rotate.b};
	}
	else if (obj->type == e_hit_cylinder)
	{
		printf("> Curent angles applied on cylinder is : (%lf, %lf, %lf)\n",
			obj->angles.x, obj->angles.y, obj->angles.z);
		get_line_angles(&angles);
		transform_cy(obj, obj->trans, angles, obj->scale);
	}
}
