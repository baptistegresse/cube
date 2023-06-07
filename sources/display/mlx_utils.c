/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 14:42:09 by bgresse           #+#    #+#             */
/*   Updated: 2023/06/07 12:46:03 by bgresse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		return ;
	dst = data->win.addr + (y * data->win.line_length + x * (data->win.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	loop_hook(t_data *data)
{
	update_player(data);
	mlx_destroy_image(data->win.mlx, data->win.img);
	data->win.img = mlx_new_image(data->win.mlx, WIN_W, WIN_H);
	data->win.addr = mlx_get_data_addr(data->win.img, &(data->win.bits_per_pixel), &(data->win.line_length), &(data->win.endian));
	raycasting(data);
	draw_minimap(data);
	mlx_put_image_to_window(data->win.mlx, data->win.mlx_win, data->win.img, 0, 0);
	return (0);
}

void	display_game(t_data *data)
{
	data->win.mlx = mlx_init();
	load_textures(data);
	data->win.mlx_win = mlx_new_window(data->win.mlx, WIN_W, WIN_H, "cube");
	data->win.img = mlx_new_image(data->win.mlx, WIN_W, WIN_H);
	data->win.addr = mlx_get_data_addr(data->win.img, &(data->win.bits_per_pixel), &(data->win.line_length), &(data->win.endian));
	mlx_hook(data->win.mlx_win, 2, (1L << 0), handle_keypress, data);
	mlx_hook(data->win.mlx_win, 3, (1L << 1), handle_keyrelease, data);
	mlx_loop_hook(data->win.mlx, loop_hook, data);
	mlx_loop(data->win.mlx);
}
