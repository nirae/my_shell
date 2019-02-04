/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_check_tokens_list.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 00:10:05 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/04 04:12:53 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int		not_terminal_type(t_list *lst)
{
	int		type;

	if (!lst)
		return (TRUE);
	type = get_type_token(lst->content);
	if (type == PIPE_TYPE
		|| type == D_QUOTE_TYPE
		|| type == S_QUOTE_TYPE
		|| type == AND_TYPE
		|| type == OR_TYPE)
		return (FALSE);
		// unexpected_token_error(get_token_token(lst->content));
	return (TRUE);
}

static void		not_started_type(t_list *lst)
{
	int		type;

	if (!lst)
		return ;
	type = get_type_token(lst->content);
	if (type == PIPE_TYPE
		|| type == DOTCOMMA_TYPE
		|| type == AND_TYPE
		|| type == OR_TYPE)
		unexpected_token_error(get_token_token(lst->content));
}

static void		operators(t_list *lst)
{
	int		type;

	if (lst->next)
	{
		type = get_type_token(lst->next->content);
		if (is_operator(type))
			unexpected_token_error(get_token_token(lst->content));
	}
	else
	{
		if (is_operator(get_type_token(lst->content)))
			unexpected_token_error(get_token_token(lst->content));
	}
}

static void		manage_type(t_list **tmp, int *end_vars)
{
	if (is_aggregation(get_type_token((*tmp)->content)))
		aggregations((*tmp));
	else if (is_redirection(get_type_token((*tmp)->content)))
		redirections((*tmp));
	else if (is_operator(get_type_token((*tmp)->content)))
	{
		operators((*tmp));
		*end_vars = FALSE;
	}
	else if (ft_strchr(get_token_token((*tmp)->content), '=') && !(*end_vars))
	{
		variables((*tmp));
		*end_vars = TRUE;
	}
	else if (type_cmp(get_type_token((*tmp)->content), NUMBER_TYPE))
		set_type_token((*tmp)->content, WORD_TYPE);
	else
		*end_vars = TRUE;
}

int 	first_check_tokens_list(t_list *lst)
{
	t_list		*tmp;
	int			end_vars;

	end_vars = FALSE;
	tmp = lst;
	not_started_type(tmp);
	while (tmp)
	{
		manage_type(&tmp, &end_vars);
		if (tmp->next == NULL)
			return (not_terminal_type(tmp));
		tmp = tmp->next;
	}
	return (TRUE);
}
