/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:25:08 by bgresse           #+#    #+#             */
/*   Updated: 2023/06/01 20:50:45 by bgresse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_m_free	*free_init(void)
{
	t_m_free	*m_free;

	m_free = (t_m_free *)malloc(sizeof(t_m_free));
	if (!m_free)
		return (NULL);
	m_free->list = NULL;
	return (m_free);
}
