/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dclst.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:13:11 by christophed       #+#    #+#             */
/*   Updated: 2025/01/27 13:50:16 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DCLST_H
# define DCLST_H

// Libraries
# include <stdlib.h>

// Structures
typedef struct s_dclst
{
	void			*data;
	struct s_dclst	*prev;
	struct s_dclst	*next;
}					t_dclst;

// Functions
t_dclst	*dclst_create_node(void *data);
t_dclst	*dclst_add_back(t_dclst **head, void *data);
t_dclst	*dclst_add(t_dclst **head, void *data);
void	dclst_remove_node(t_dclst **head, t_dclst *node);
void	dclst_clear(t_dclst **head);
int		dclst_count_nodes(t_dclst *head);
int		dclst_find_node_pos(t_dclst *head, t_dclst *node);
t_dclst	*dclst_find_node_with_pos(t_dclst *head, int position);
void	dclst_move_node(t_dclst **origin, t_dclst **destination, t_dclst *node);
int		dclst_swap_nodes(t_dclst **head, t_dclst *node1, t_dclst *node2);

#endif