/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_rule.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 05:55:41 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/28 06:02:06 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "st.h"

/*
**	Regle U prime -> pas de noeud et toujours true (epsilon)
*/

int		u_prime_rule(t_tokens_list **tokens_list_struct, t_ptree **tree)
{
	int		save_index;

	save_index = (*tokens_list_struct)->index;
	if (test_current_token(tokens_list_struct, REDIRECTION_TYPE, tree)
		&& test_current_token(tokens_list_struct, REDIRECTION_ARG_TYPE, tree)
		&& u_prime_rule(tokens_list_struct, tree))
	{
		return (TRUE);
	}
	(*tokens_list_struct)->index = save_index;
	return (TRUE);
}

/*
**	Regle U
*/

int		u_rule(t_tokens_list **tokens_list_struct, t_ptree **tree)
{
	int		id;
	int		save_index;
	t_ptree		**tmp;

	id = ft_ptree_add_child(tree, NULL, U_RULE);
	tmp = ft_ptree_get_node_with_id(tree, id);
	save_index = (*tokens_list_struct)->index;
	if (v_rule(tokens_list_struct, tmp)
		&& u_prime_rule(tokens_list_struct, tmp))
	{
		return (TRUE);
	}
	(*tokens_list_struct)->index = save_index;
	ft_ptree_remove_node_with_id(tree, id);
	return (FALSE);
}