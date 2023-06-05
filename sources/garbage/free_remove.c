/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_remove.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:22:56 by bgresse           #+#    #+#             */
/*   Updated: 2023/06/01 20:50:51 by bgresse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_remove_if(t_free **begin_list, void *ptr_ref)
{
	t_free	*to_free;

	if (*begin_list)
	{
		if ((*begin_list)->ptr == ptr_ref)
		{
			to_free = *begin_list;
			*begin_list = (*begin_list)->next;
			if (to_free->ptr)
				free(to_free->ptr);
			free(to_free);
			free_remove_if(begin_list, ptr_ref);
		}
		else
			free_remove_if(&(*begin_list)->next, ptr_ref);
	}
}

void	free_remove(t_m_free *m_free, void *ptr)
{
	free_remove_if(&m_free->list, ptr);
}
