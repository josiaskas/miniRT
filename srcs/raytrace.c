/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 14:54:17 by jkasongo          #+#    #+#             */
/*   Updated: 2022/11/18 02:08:17 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static inline unsigned int	get_trgb(t_color *color)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	unsigned int	a;

	if (color->r > 1)
		color->r = 1;
	if (color->g > 1)
		color->g = 1;
	if (color->b > 1)
		color->b = 1;
	if (color->a > 1)
		color->a = 1;
	r = (unsigned int)(color->r * 255);
	g = (unsigned int)(color->g * 255);
	b = (unsigned int)(color->b * 255);
	a = (unsigned int)(color->a);
	return ((a << 24) | (r << 16) | (g << 8) | b);
}

// clear all data stored to prepare a new frame
static inline void	print_clr_to_screen(t_app *app, t_color clr, int x, int y)
{
	int		pos;
	char	*pixel;
	t_image	*img;

	img = app->img;
	if (app->out_fd != 0)
	{
		color_correction(&clr);
		app->data[y][x] = clr;
		print_progress(app->scene->pix_traced);
	}
	else
	{
		pos = (y * img->line_length) + (x * (img->bits_per_pixel / 8));
		pixel = img->data + pos;
		*(unsigned int *)pixel = get_trgb(&clr);
	}
}

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
	first_hit = get_first_obj_hit(scn, ray, 3000, RAY_T_MIN);
	if (first_hit.intersection)
	{
		ft_compute_hit(&first_hit);
		color = shade_hit(scn, &first_hit);
	}
	return (color);
}

bool	render(t_app *app)
{
	int		x;
	int		y;
	t_color	pix_clr;

	y = -1;
	while (++y < W_HEIGHT)
	{
		x = -1;
		while (++x < W_WIDTH)
		{
			pix_clr = get_pixel_clr(app->scene, (x + 0.5), (y + 0.5));
			app->scene->pix_traced++;
			print_clr_to_screen(app, pix_clr, x, y);
		}
	}
	app->scene->pix_traced = 0;
	if (app->out_fd != 0)
		printf("\nRaytracing finished\n");
	return (true);
}
