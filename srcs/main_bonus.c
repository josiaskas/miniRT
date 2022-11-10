/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 21:44:40 by jkasongo          #+#    #+#             */
/*   Updated: 2022/11/09 21:44:42 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../includes/multithread.h"



int	main(int argc, char *argv[])
{
	if (argc == 2)
		init_app(argv[1], NULL);
	else if (argc == 3)
		init_app(argv[1], argv[2]);
	else
		ft_putendl_fd("Usage: miniRT *.rt", STDOUT_FILENO);
	return (0);
}