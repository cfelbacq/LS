/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 11:47:39 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/03/17 15:54:32 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	fill_mod(struct stat *buf, t_l *data)
{
	data->mode = (char *)ft_memalloc(sizeof(char) * 10);
	ft_memset(data->mode, '-', 9);
	data->mode[9] = '\0';
	if (buf->st_mode & S_IRUSR)
		data->mode[0] = 'r';
	if (buf->st_mode & S_IWUSR)
		data->mode[1] = 'w';
	if (buf->st_mode & S_IXUSR)
		data->mode[2] = 'x';
	if (buf->st_mode & S_IRGRP)
		data->mode[3] = 'r';
	if (buf->st_mode & S_IWGRP)
		data->mode[4] = 'w';
	if (buf->st_mode & S_IXGRP)
		data->mode[5] = 'x';
	if (buf->st_mode & S_IROTH)
		data->mode[6] = 'r';
	if (buf->st_mode & S_IWOTH)
		data->mode[7] = 'w';
	if (buf->st_mode & S_IXOTH)
		data->mode[8] = 'x';
}

void	fill_type(struct stat *buf, t_l *data)
{
	if ((buf->st_mode & S_IFMT) == S_IFDIR)
		data->type = 'd';
	else if ((buf->st_mode & S_IFMT) == S_IFREG)
		data->type = '-';
	else if ((buf->st_mode & S_IFMT) == S_IFBLK)
		data->type = 'b';
	else if ((buf->st_mode & S_IFMT) == S_IFCHR)
		data->type = 'c';
	else if ((buf->st_mode & S_IFMT) == S_IFLNK)
		data->type = 'l';
	else if ((buf->st_mode & S_IFMT) == S_IFIFO)
		data->type = 'p';
	else if ((buf->st_mode & S_IFMT) == S_IFSOCK)
		data->type = 's';
}

t_l		*fill_data(char *path, char *name, t_l *next, t_option *opt)
{
	t_l			*data;
	t_stat		buf;
	t_passwd	*get;
	t_group		*getgrp;

	data = (t_l *)ft_memalloc(sizeof(t_l));
	lstat(path, &buf);
	data->name = (char *)ft_memalloc(sizeof(char) * ft_strlen(name) + 1);
	data->name = ft_strcpy(data->name, name);
	fill_type(&buf, data);
	if (opt->l == 1)
	{
		getgrp = getgrgid(buf.st_gid);
		get = getpwuid(buf.st_uid);
		fill_mod(&buf, data);
		data->nb_octet = buf.st_size;
		data->user = (char *)ft_memalloc(sizeof(char) * \
				ft_strlen(get->pw_name));
		data->group_name = (char *)ft_memalloc(sizeof(char) *\
				ft_strlen(getgrp->gr_name + 1));
		data->nb_link = buf.st_nlink;
		ft_strcpy(data->user, get->pw_name);
		ft_strcpy(data->group_name, getgrp->gr_name);
	}
	data->next = next;
	return (data);
}

t_list	*fill_str(char *str)
{
	t_list *argv;

	argv = (t_list *)ft_memalloc(sizeof(t_list));
	argv->content = (char *)ft_memalloc(sizeof(char) * ft_strlen(str) + 1);
	argv->content = ft_strcpy(argv->content, str);
	argv->next = NULL;
	return (argv);
}
