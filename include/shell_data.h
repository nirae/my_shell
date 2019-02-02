/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_data.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 02:22:51 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/02 05:33:51 by aroblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_DATA_H
# define SHELL_DATA_H

// # include "st.h"
# include "../libft/include/libft.h"

typedef struct			s_ptree
{
	int				id;
	char			*data;
	int				type;
	t_list			*childs_lst;
	int				nb_childs;
	t_btree			*ast;
}						t_ptree;

/*
**	Main structure
*/

typedef struct		s_shell_data
{
	pid_t			pid;
	int				last_status;
	int				exec_next;
	char			*shell;
	int				options;
	t_list			*env_lst;
	char			**env_tab;
	t_list			*intern_env_lst;
	t_list			*tokens_list;
	t_ptree			*parse_tree;
	t_btree			*ast;
	t_list			*history;
}					t_shell_data;

t_shell_data		*shell_data_singleton();
void				quit_shell(int status, int err);

#endif