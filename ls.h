/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 13:27:10 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/03/17 15:50:04 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LS_H
# define LS_H

#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <dirent.h>
#include "../libft/libft.h"
#include <stdio.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <errno.h>

typedef struct stat t_stat;
typedef struct passwd t_passwd;
typedef struct group t_group;
typedef struct dirent t_dirent;
typedef	struct	s_l
{
	char	*mode;
	long	nb_link;
	char	*name;
	char	*user;
	char	*group_name;
	int	nb_octet;
	char	*time;
	char	type;
	struct s_l *next;
}				t_l;

typedef struct	s_option
{
	int l;
	int R;
	int a;
	int r;
	int t;
	int err;
}				t_option;

void	free_double(char **tab);
void	fill_mod(struct stat *buf, t_l *data);
void	fill_type(struct stat *buf, t_l *data);
t_l		*fill_data(char *path, char *name, t_l *next, t_option *opt);
void	print_l(t_l *data, t_option *opt);
void	print_path(char *path);
void	print_opt(t_option *opt);
void	check_opt(int argc, t_option *opt, char **str);
void	init_option(t_option *opt);
void	start(int argc, char **argv, t_option *opt);
t_l		*ins_start(t_l *begin, t_l *new);
void	ins_middle(t_l *prev, t_l *new, t_l *next);
void	print_dir(char *name, t_option *opt);
void	print_err(char *str);
void	free_data(t_l **data, int mode, t_option *opt);
#endif
