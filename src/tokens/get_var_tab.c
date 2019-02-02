/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 04:27:56 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/02 05:58:55 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "tokens.h"

char 	**get_var_tab(t_var_token **token)
{
	char	**tab;
	t_list	*tmp;
	char	*end;

	if (!(tab = ft_memalloc(sizeof(char *) * 2)))
		quit_shell(EXIT_FAILURE, MALLOC_ERR);
	if ((*token)->is_expansion)
	{
		end = ft_strchr((*token)->token, '=');
		ft_printf("end = %s\n", end);
		manage_expansion(&end);
		ft_printf("apres manage expansion = %s\n", (*token)->token);
	}
	tab[0] = ft_strdup((*token)->token);
	tab[1] = NULL;
	tmp = (*token)->var_lst;
	while (tmp)
	{
		ft_strtab_addend(&tab, get_token_token(tmp->content));
		tmp = tmp->next;
	}
	return (tab);
}
