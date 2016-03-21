/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 13:27:10 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/03/21 16:57:56 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
# define LS_H

# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <stdlib.h>
# include <dirent.h>
# include "../libft/libft.h"
# include <stdio.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
# include <errno.h>

typedef struct stat	t_stat;
typedef struct passwd	t_passwd;
typedef struct group	t_group;
typedef struct dirent	t_dirent;
typedef	struct	s_l
{
	char				*path;
	char				*mode;
	long				nb_link;
	char				*name;
	char				*user;
	char				*group_name;
	int					nb_octet;
	unsigned int		major;
	unsigned int		minor;
	char				*time;
	char				type;
	char				*link;
	struct timespec		time_sec;
	struct s_l			*next;
}				t_l;

typedef struct	s_option
{
	int l;
	int re;
	int a;
	int r;
	int t;
	int un;
	int err;
}				t_option;

void			print_maj_min(t_l *data);
void			check_len_ar(int argc, char **argv);
void			ls(t_l *data, t_option *opt);
int				round_total(float nb);
int				total(t_l *data);
t_l				*check_file(t_l *ar, t_option *opt);
int				check_flag(char *str);
t_l				*remove_link(t_l *ar, char *name, t_option *opt);
void			get_time_sec(t_l *data, t_stat buf);
void			get_path_name(t_l *data, char *path, char *name);
void			get_user_grp(t_l *data, t_stat buf);
void			get_major_minor(t_l *data, t_stat buf);
t_l				*check_file(t_l *ar, t_option *opt);
void			init_option(t_option *opt);
int				sort_time(t_l *new, t_l *tmp);
void			check_opt(int argc, t_option *opt, char **str);
void			start(int argc, char **argv, t_option *opt);
t_l				*fill_data(char *path, char *name, t_l *next, t_option *opt);
void			fill_type(struct stat *buf, t_l *data);
void			fill_mod(struct stat *buf, t_l *data);
char			*ft_readlink(char *path, int size);
void			init_file(t_l *ar, t_option *opt, int *nb_file, int *nb_rep);
void			init_rep(t_l *ar, t_option *opt, int nb_file, int nb_rep);
void			print_dir(char *name, t_option *opt);
t_l				*ins_start(t_l *begin, t_l *new);
void			ins_middle(t_l *prev, t_l *new, t_l *next);
t_l				*reverse(t_l *data);
void			print_err(char *str);
void			print_err_ar(char *str);
void			print_l(t_l *data, t_option *opt);
void			print_path(char *path);
void			print_opt(t_option *opt);
void			free_double(char **tab);
void			free_data(t_l **data, int mode, t_option *opt);
#endif
