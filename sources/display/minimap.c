/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 14:39:57 by bgresse           #+#    #+#             */
/*   Updated: 2023/06/07 12:45:05 by bgresse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	load_textures(t_data *data)
{
	char	*texture_paths[4];
	int		i;

	texture_paths[0] = data->params.path_to_the_north_texture;
	texture_paths[1] = data->params.path_to_the_south_texture;
	texture_paths[2] = data->params.path_to_the_west_texture;
	texture_paths[3] = data->params.path_to_the_east_texture;
	i = -1;
	while (++i < 4)
	{
		data->text[i].width = 64;
		data->text[i].height = 64;
	}
	i = -1;
	while (++i < 4)
	{
		data->text[i].img = mlx_xpm_file_to_image(data->win.mlx, texture_paths[i], &data->text[i].width, &data->text[i].height);
		if (!data->text[i].img)
		{
			fprintf(stderr, "Failed to load texture: %s\n", texture_paths[i]);
			exit(1);
		}
		data->text[i].data = mlx_get_data_addr(data->text[i].img, &data->text[i].bpp, &data->text[i].size_line, &data->text[i].endian);
	}
	return (true);
}

int	get_minimap_color(t_data *data, int x, int y)
{
	int	color;

	color = 0;
	if (y == (int)data->player.pos.y && x == (int)data->player.pos.x)
		color = 0xFF0000;
	else if (data->map.array[y][x] == '0')
		color = 0xFFFFFF;
	else if (data->map.array[y][x] == '1')
		color = 0x000000;
	return (color);
}

void	draw_minimap(t_data *data)
{
	int		x;
	int		y;
	int		dy;
	int		dx;
	int		color;

	y = -1;
	while (++y < data->map.height)
	{
		x = -1;
		while (++x < data->map.width)
		{
			color = get_minimap_color(data, x, y);
			dy = -1;
			while (++dy < MINIMAP_SIZE)
			{
				dx = -1;
				while (++dx < MINIMAP_SIZE)
					my_mlx_pixel_put(data, x * MINIMAP_SIZE + dx, y * MINIMAP_SIZE + dy, color);
			}
		}
	}
}
