/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 14:31:53 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/03/21 16:21:03 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	fill_modsst(t_l *data, t_stat *buf)
{
	if (buf->st_mode & S_ISUID && data->mode[2] == 'x')
		data->mode[2] = 's';
	else if (buf->st_mode & S_ISUID && data->mode[2] == '-')
		data->mode[2] = 'S';
	if (buf->st_mode & S_ISGID && data->mode[5] == 'x')
		data->mode[5] = 's';
	else if (buf->st_mode & S_ISGID && data->mode[5] == '-')
		data->mode[5] = 'S';
	if (buf->st_mode & S_ISVTX && data->mode[8] == 'x')
		data->mode[8] = 't';
	else if (buf->st_mode & S_ISVTX && data->mode[8] == '-')
		data->mode[8] = 'T';
}

void	fill_mod(t_stat *buf, t_l *data)
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
	fill_modsst(data, buf);
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

char	*ft_readlink(char *path, int size)
{
	int		r;
	char	*link_name;

	r = 0;
	link_name = (char *)ft_memalloc(sizeof(char) * size + 1);
	r = readlink(path, link_name, size + 5);
	link_name[r] = '\0';
	return (link_name);
}
