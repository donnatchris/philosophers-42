/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:41:34 by nifromon          #+#    #+#             */
/*   Updated: 2025/01/18 14:13:21 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//START
#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static t_list	*store[200000];
	t_list			*error;
	char			*queue;

	if (fd < 0 || fd > 200000 || BUFFER_SIZE <= 0)
		return (NULL);
	queue = NULL;
	if (inventory(store, fd) == -1)
	{
		while (store[fd])
		{
			error = store[fd]->next;
			free(store[fd]->content);
			free(store[fd]);
			store[fd] = error;
		}
		store[fd] = NULL;
	}
	if (!store[fd])
		return (NULL);
	queue = fetch_queue(store[fd]);
	cutting_in(&store[fd]);
	return (queue);
}

int	inventory(t_list **store, int fd)
{
	int		bill;
	char	*product;

	bill = 0;
	while (!search_newline(store[fd]))
	{
		product = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!product)
			return (bill);
		bill = read(fd, product, BUFFER_SIZE);
		if (bill <= 0)
		{
			free(product);
			product = NULL;
			return (bill);
		}
		product[bill] = '\0';
		stock_replenishment(store, product, fd);
	}
	return (bill);
}

void	stock_replenishment(t_list **store, char *product, int fd)
{
	t_list	*new_product;
	t_list	*last_product;

	last_product = ft_lstlast(store[fd]);
	new_product = (t_list *)malloc(sizeof(t_list));
	if (!new_product)
		return ;
	if (!last_product)
		store[fd] = new_product;
	else
		last_product->next = new_product;
	new_product->content = product;
	new_product->next = NULL;
}

char	*fetch_queue(t_list *store)
{
	int		queue_len;
	char	*next_queue;

	if (!store)
		return (NULL);
	queue_len = lstlen_till_newline(store);
	next_queue = (char *)malloc(sizeof(char) * (queue_len + 1));
	if (!next_queue)
		return (NULL);
	cpylst_to_str(store, next_queue);
	return (next_queue);
}

void	cutting_in(t_list **store)
{
	t_list	*last_product;
	t_list	*clean_store;
	int		i;
	int		j;
	char	*product;

	product = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	clean_store = (t_list *)malloc(sizeof(t_list));
	if (!product || !clean_store)
		return ;
	last_product = ft_lstlast(*store);
	i = 0;
	j = 0;
	while (last_product->content[i] && last_product->content[i] != '\n')
		i++;
	while (last_product->content[i] && last_product->content[++i])
		product[j++] = last_product->content[i];
	product[j] = '\0';
	clean_store->content = product;
	clean_store->next = NULL;
	free_store(store, clean_store, product);
}

//END
