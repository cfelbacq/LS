/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 15:48:31 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/03/20 13:31:37 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	get_major_minor(t_l *data, t_stat buf)
{
	data->major = major(buf.st_rdev);
	data->minor = minor(buf.st_rdev);
}

void	get_user_grp(t_l *data, t_stat buf)
{
	t_passwd	*get;
	t_group		*getgrp;

	get = getpwuid(buf.st_uid);
	getgrp = getgrgid(buf.st_gid);
	data->user = (char *)ft_memalloc(sizeof(char) * \
			ft_strlen(get->pw_name));
	data->group_name = (char *)ft_memalloc(sizeof(char) *\
			ft_strlen(getgrp->gr_name + 1));
	data->nb_link = buf.st_nlink;
	ft_strcpy(data->user, get->pw_name);
	ft_strcpy(data->group_name, getgrp->gr_name);
}

void	get_path_name(t_l *data, char *path, char *name)
{
	data->path = (char *)ft_memalloc(sizeof(char) * ft_strlen(path) + 1);
	data->path = ft_strcpy(data->path, path);
	data->name = (char *)ft_memalloc(sizeof(char) * ft_strlen(name) + 1);
	data->name = ft_strcpy(data->name, name);
}

void	get_time_sec(t_l *data, t_stat buf)
{
		(data->time_sec).tv_sec = (buf.st_mtimespec).tv_sec;
		(data->time_sec).tv_nsec = (buf.st_mtimespec).tv_nsec;
}
