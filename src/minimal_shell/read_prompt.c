/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 16:42:39 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/31 22:32:06 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static int		final_return(char **s, int n_lus)
{
	char	*temp;

	if (n_lus == 0 && !(*s))
	{
		ft_strdel(s);
		return (0);
	}
	temp = *s;
	*s = ft_strsub(temp, ft_strpos(temp, '\n'), (int)ft_strlen(temp));
	ft_strdel(&temp);
	ft_strdel(s);
	return (1);
}

int				read_prompt(const int fd, char **line)
{
	char		*buff;
	char		*final_buff;
	int			n_lus;
	char		*tmp;

	if ((n_lus = read(fd, "", 0)) == -1)
		return (-1);
	if (!(buff = ft_strnew(1)))
		return (-1);
	final_buff = NULL;
	while (!ft_strchr(final_buff, '\n') && (n_lus = read(fd, buff, 1)) > 0)
	{
		if (!final_buff)
			final_buff = ft_strdup(buff);
		else
		{
			tmp = final_buff;
			final_buff = ft_strjoin(tmp, buff);
			ft_strdel(&tmp);
		}
		ft_strclr(buff);
	}
	ft_strdel(&buff);
	*line = ft_strsub(final_buff, 0, ft_strpos(final_buff, '\n'));
	return (final_return(&final_buff, n_lus));
}