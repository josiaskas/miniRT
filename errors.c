/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 18:54:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/08/14 18:54:04 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_print_error(char *error_message, int code)
{
	ft_putstr_fd("miniRT: code:", STDERR_FILENO);
	ft_putnbr_fd(code, STDERR_FILENO);
	ft_putchar_fd(' ', STDERR_FILENO);
	ft_putendl_fd(error_message, STDERR_FILENO);
}