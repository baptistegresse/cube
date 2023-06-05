/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_size.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:24:55 by bgresse           #+#    #+#             */
/*   Updated: 2023/06/01 20:50:53 by bgresse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ft_free_size(t_m_free *m_free)
{
	t_free	*tmp;
	int		i;

	i = 0;
	tmp = m_free->list;
	if (tmp)
		i = 1;
	if (!tmp)
		return (i);
	while (tmp->next)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}
