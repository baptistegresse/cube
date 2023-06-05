/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 19:25:03 by jcluzet           #+#    #+#             */
/*   Updated: 2023/06/05 13:12:27 by bgresse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	put_pxl_img(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *) dst = color;
}

int	error(t_data *data, char *string)
{
	ft_free(data->garbage);
	write(2, "Error\n", 6);
	write(2, string, strlen(string));
	return (EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
	t_data data;
	if (argc != 2)
		return (write(2, "Error\nnot enough args\n", 22), 1);
	if (!strstr(argv[1], ".cub"))
		return (write(1, "Error\nnot a .cub\n", 17), 1);
	data.garbage = free_init();
	init_data(&data);
	if (!cube_parser(&data, argv[1]))
		return (ft_free(data.garbage), 1);
	display_game(&data);
	return (ft_free(data.garbage), 0);
}
