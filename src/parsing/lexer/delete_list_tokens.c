/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_list_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 00:26:32 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/21 17:45:04 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
**	Delete proprement la liste des tokens
*/

void 	delete_list_tokens(void)
{
	t_shell_data *data;

	data = shell_data_singleton();
	ft_lstdel(&(data->tokens_list), free_token);
}