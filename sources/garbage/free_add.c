/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:20:12 by bgresse           #+#    #+#             */
/*   Updated: 2023/06/01 20:50:41 by bgresse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	free_add_value(t_m_free *m_free, t_free *new, t_free *tmp)
{
	if (m_free->list)
	{
		tmp = m_free->list;
		while (tmp->next)
		{
			if (tmp->ptr == new->ptr)
				return (0);
			tmp = tmp->next;
		}
		if (tmp->ptr == new->ptr)
			return (0);
		tmp->next = new;
		return (1);
	}
	else
	{
		m_free->list = new;
		return (1);
	}
	return (0);
}

int	free_add(t_m_free *m_free, void *ptr)
{
	t_free	*new;
	t_free	*tmp;

	if (ptr)
	{
		new = (t_free *)malloc(sizeof(t_free));
		tmp = NULL;
		new->ptr = ptr;
		new->next = NULL;
		if (free_add_value(m_free, new, tmp))
			return (1);
		else
			free(new);
	}
	return (0);
}
