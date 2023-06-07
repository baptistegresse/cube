/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 19:25:03 by jcluzet           #+#    #+#             */
/*   Updated: 2023/06/07 11:36:52 by bgresse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


int main(int argc, char *argv[])
{
	t_data data;
	if (argc != 2)
		return (write(2, "Error\nnot enough args\n", 22), 1);
	if (!strstr(argv[1], ".cub"))
		return (write(1, "Error\nnot a .cub\n", 17), 1);
	data.garbage = free_init();
	if (!init_data(&data))
		return (ft_free(data.garbage), 1);
	if (!cube_parser(&data, argv[1]))
		return (ft_free(data.garbage), 1);
	display_game(&data);
	return (ft_free(data.garbage), 0);
}
