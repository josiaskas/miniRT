/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 11:54:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/08/30 11:54:04 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parser.h"

bool	parse_sphere(char **tokens, t_app *app)
{
	t_hittable	*sphere;

	sphere = (t_hittable *)ft_calloc(1, sizeof(t_hittable));
	ft_push(app->scene->hittable, sphere);
	sphere->type = e_hit_sphere;
	if (!tokens_has_valid_params_nbr(tokens, 4))
		return (false);
	if (!parse_a_vector(tokens[1], &sphere->origin))
		return (false);
	if (!parse_double_from_str(tokens[2], &sphere->conf_data_1))
		return (false);
	if (!parse_a_vector(tokens[3], &sphere->color))
		return (false);
	if (!all_vector_coord_are_in_range(0, 255, &sphere->color))
		return (false);
	return (true);
}

bool	parse_camera(char **tokens, t_app *app)
{
	t_cam		*camera;
	t_point		origin;
	t_point		orientation;
	double		angle;

	angle = 0;
	if (!tokens_has_valid_params_nbr(tokens, 4))
		return (false);
	if (!parse_a_vector(tokens[1], &origin))
		return (false);
	if (!parse_a_vector(tokens[2], &orientation))
		return (false);
	if (!parse_double_from_str(tokens[3], &angle))
		return (false);
	if (!all_vector_coord_are_in_range(-1, 1, &orientation))
		return (false);
	if (angle < 0 || angle > 180)
		return (false);
	camera = build_camera(origin, orientation, angle);
	ft_push(app->scene->cameras, camera);
	return (true);
}

bool	parse_file_line(char *line, t_app *app)
{
	char	**tokens;
	bool	status;

	status = true;
	if (!ft_strlen(line))
		return (true);
	tokens = ft_split(line, ' ');
	if (ft_strncmp(tokens[0], "sp", 2) == 0)
		status = parse_sphere(tokens, app);
	else if (ft_strncmp(tokens[0], "C", 1) == 0)
		status = parse_camera(tokens, app);
	ft_free_splitted(tokens);
	return (status);
}

bool	parse_rt_file(t_app *app)
{
	char	*line;
	int		res;

	line = NULL;
	app->scene  = init_scene();
	app->error_message = "Error during parsing";
	app->error_code = 2;
	ft_putendl_fd("Start File parsing", STDOUT_FILENO);
	res = get_next_line(app->in_fd, &line);
	while (res > 0)
	{
		if (!parse_file_line(line, app))
		{
			free(line);
			return (false);
		}
		free(line);
		res = get_next_line(app->in_fd, &line);
	}
	free(line);
	app->error_message = NULL;
	return (true);
}