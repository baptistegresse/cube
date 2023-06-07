/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 16:47:53 by gusimone          #+#    #+#             */
/*   Updated: 2023/06/07 12:36:36 by bgresse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	rgb_to_int(t_rgb color)
{
	return ((color.red << 16) | (color.green << 8) | color.blue);
}

int	set_color_cell(t_data *data, int x, int y)
{
	if (data->map.array[y][x] == '1')
		return (0x000000);
	else if (data->map.array[y][x] == '0')
		return (0xffd25f);
	else
		return (-1);
}
