#include "minishell.h"

// void	insert_into_tree(t_tree *tree, char *content)
// {
// 	if (!tree)
// 	{
// 		tree = malloc (sizeof(t_tree));
// 		if (!tree)
// 			return ;
// 		tree->data = content;
// 		tree->right = NULL;
// 		tree->left = NULL;
		
// 	}
// }

// t_list	*new_doubly(char *content)
// {
// 	t_list	*new;

// 	new = malloc(sizeof(t_list *));
// 	if (!new)
// 		return (NULL);
	
// }
// void	insert_into_doubly(t_list *head_d_list, t_elem *new)
// {
// 	t_elem		*cursor;
// 	t_list		*node;

// 	node = malloc(sizeof(t_list));
	
// 	if (!head_d_list->next && !head_d_list->prev)
// 	{
// 		node->prev = NULL;
// 		node->next = NULL;
// 		node = ne
// 		head_d_list = node;
// 	}
// 	cursor = head_d_list->next;
// 	while (cursor->next)
// 		cursor = cursor->next;
// 	node->prev = cursor;
// 	cursor->next = new;
// }

// void	split_list(t_elem *head_list, char c, t_list *tree)
// {
// 	t_elem		*cursor;

// 	cursor = head_list;
// 	while (cursor)
// 	{
// 		if (!ft_strcmp(cursor->content, &c))
// 			insert_into_tree(tree, &c);
// 		cursor = cursor->next;
// 	}
// }

// void	to_doubly_list(t_elem *elem, t_list *d_list)
// {
// 	t_elem	*cursor;

// 	cursor = elem;
// 	if (!d_list)
// 	{
// 		d_list = malloc(sizeof(t_list));
// 		if (!d_list)
// 			return ;
// 	}
// 	while (cursor)
// 	{

// 		cursor = cursor->next;
// 	}
// }