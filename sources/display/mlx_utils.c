/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 14:42:09 by bgresse           #+#    #+#             */
/*   Updated: 2023/06/05 13:17:09 by bgresse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char *dst;

    if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		  return ;
    dst = data->win.addr + (y * data->win.line_length + x * (data->win.bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}
