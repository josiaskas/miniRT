/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_creation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 14:52:10 by jkasongo          #+#    #+#             */
/*   Updated: 2022/10/31 20:32:53 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"
#include "parser.h"


// clear all data stored to prepare a new frame
static inline void	init_raytracing(t_app *app)
{
	size_t	i;
	t_scene	*scene;

	app->error_code = 0;
	app->error_message = NULL;
	scene = app->scene;
	if (!app->data && (app->out_fd != 0))
	{
		app->data = (t_color **)ft_calloc((W_HEIGHT), sizeof(t_color *));
		i = 0;
		while (i < W_HEIGHT)
			app->data[i++] = ft_calloc(W_WIDTH, sizeof (t_color));
	}
	if (!scene->selected_camera)
		scene->selected_camera = ft_get_elem(scene->cameras, 0);
}

bool	check_config_file(t_app *app)
{
	t_array	*cams;
	t_array	*lights;

	cams = app->scene->cameras;
	lights = app->scene->lights;
	app->error_message = "Error during parsing";
	app->error_code = 4;
	if (app->scene->hittable->length < 1)
	{
		app->error_message = "No Object on the scene";
		return (false);
	}
	app->error_message = "number of Light(s) on the scene";
	if ((lights->length == 0) || (!IS_BONUS && (lights->length >= 2)))
		return (false);
	app->error_message = "Number of cameras on the scene";
	if ((cams->length == 0) || (!IS_BONUS && (cams->length >= 2)))
		return (false);
	init_raytracing(app);
	printf("config file checked\n");
	return (true);
}

char	*add_name(t_scene *scene, char	*name, bool parsed)
{
	static int	n = 0;
	char		*made_name;
	char		*number;

	n++;
	made_name = name;
	if (parsed)
	{
		number = ft_itoa(n);
		made_name = ft_strjoin(made_name, number);
		free(number);
	}
	ft_push(scene->names, made_name);
	return (made_name);
}

/*
 * Build a normal object material with
 * colors, specular coefficient , diffuse coefficient and phong shines
 */
t_material	build_default_material(t_color clr, double s, double d, double ph)
{
	t_material	m;

	m.type = e_plastic;
	m.specular = s;
	m.diffuse = d;
	m.shininess = ph;
	m.reflexive = 1.0;
	m.main = clr;
	m.pattern = e_normal_pattern;
	return (m);
}

/*
 * Build a stripped object material with
 * colors, specular coefficient , diffuse coefficient and phong shines
 */
t_material	build_stripped(t_color clr[], double s, double d, double ph)
{
	t_material	m;

	m.type = e_plastic;
	m.specular = s;
	m.diffuse = d;
	m.shininess = ph;
	m.reflexive = 1;
	m.main = clr[0];
	m.second = clr[1];
	m.pattern = e_stripped_pattern;
	return (m);
}
