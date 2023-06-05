/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:21:56 by bgresse           #+#    #+#             */
/*   Updated: 2023/06/01 20:50:56 by bgresse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_free(t_m_free *m_free)
{
	t_free	*tmp;

	while (m_free->list)
	{
		tmp = m_free->list;
		m_free->list = m_free->list->next;
		if (tmp->ptr)
			free(tmp->ptr);
		free(tmp);
	}
	free(m_free);
}
