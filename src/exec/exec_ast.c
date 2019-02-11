/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 22:53:59 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/11 03:21:46 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static void		exec_cmd(t_btree *tree)
{
	t_list	*old_intern_env;
	t_list	*tmp_intern_env;
	t_shell_data	*data;
	char **tab;

	data = shell_data_singleton();
	if (get_var_token_in_cmd_token(tree->data))
	{
		old_intern_env = data->intern_env_lst;
		tmp_intern_env = ft_lstcpy(data->intern_env_lst, &tmp_intern_env);
		data->intern_env_lst = tmp_intern_env;
		tab = get_var_tab(((t_var_token **)(tree->data)));
		set_builtin(tab);
		ft_strtab_del(&tab);
	}
	tab = get_cmd_tab(((t_cmd_token **)(tree->data)));
	if (!manage_builtins(tab))
		exec_command(tab, data->env_tab);
	ft_strtab_del(&tab);
	if (get_var_token_in_cmd_token(tree->data))
	{
		ft_lstdel(&data->intern_env_lst, del_env_var);
		data->intern_env_lst = old_intern_env;
	}
}

static void		exec_right(t_btree *tree, int *exec, int exec_next, t_shell_data *data)
{
	char	**tab;

	if (get_type_token(tree->data) == AND_TYPE)
	{
		if (WEXITSTATUS(data->last_status) != EXIT_SUCCESS)
			*exec = FALSE;
	}
	else if (get_type_token(tree->data) == OR_TYPE)
	{
		if (WEXITSTATUS(data->last_status) == EXIT_SUCCESS)
			*exec = FALSE;
	}
	else if (get_type_token(tree->data) == CMD_TYPE && exec_next)
		exec_cmd(tree);
	else if (get_type_token(tree->data) == VAR_TYPE && exec_next)
	{
		tab = get_var_tab(((t_var_token **)(tree->data)));
		set_builtin(tab);
		ft_strtab_del(&tab);
	}
	if (tree->right != NULL)
		exec_ast(tree->right, *exec);
}

void 	exec_ast(t_btree *tree, int exec_next)
{
	t_shell_data	*data;
	int			exec;

	data = shell_data_singleton();
	if (tree == NULL)
		return ;
	exec = TRUE;
	if (get_type_token(tree->data) == PIPE_TYPE && exec_next)
	{
		pipe_execution(tree);
		return ;
	}
	else if ((is_redirection(get_type_token(tree->data))
		|| is_aggregation(get_type_token(tree->data))) && exec_next)
	{
		aggr_redir_execution(tree);
		return ;
	}
	else
		if (exec_next)
			if (tree->left != NULL)
				exec_ast(tree->left, exec);
	exec_right(tree, &exec, exec_next, data);
}
