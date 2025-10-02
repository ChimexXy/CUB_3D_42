/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:12:54 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/09/30 18:41:42 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "./get_next_line/gnl.h"

typedef struct s_config		t_config;
typedef struct s_textures	t_textures;
typedef struct s_rgb		t_rgb;
typedef struct s_file		t_file;

typedef struct s_file
{
	char	*line;
	t_file	*next;
}	t_file;

typedef struct s_var
{
	bool	flag;
	int		r;
	int		ret;
	int		n;
}	t_var;

bool	is_valid_map(t_config *config, char *pmap);
bool	_map(t_config *config, t_file *file, char *pmap, int *ln);
int		open_fd(char *file, int fd);
void	p_error(const char *s);
void	skip_space(int *r, char *str);
void	back_space(int *r, char *str);
bool	is_space(char c);
bool	is_player(char c);
bool	is_normal(char c);
bool	just_space(char *line);
bool	is_correct_rgb(int n);
int		number_of_words(char **split);
void	free_node(t_file **file, int n);
int		real_char_len(char *str);
bool	is_all_space(char c);
bool	just_all_space(char *line);
void	skip_all_space(int *r, char *str);
void	delete_just_sps_head(t_file **file);
void	delete_just_sps_last(t_file *file);
bool	first_line_mp(t_config *config, int p_block, int r);
bool	last_line_mp(t_config *config, int p_block, int r);
bool	check_map_walls(t_config *config, int *p_block, int ln, int player);
char	**get_content_map(t_file *file, int *ln);
bool	void_place(char **map);
bool	handle_format(char *path, char *format);
bool	is_valid_config(t_config *config, t_file **file);
bool	floor_color(t_config *config, t_file **file);
bool	ceiling_color(t_config *config, t_file **file);
bool	no_texture(t_config *config, t_file **file);
bool	so_texture(t_config *config, t_file **file);
bool	we_texture(t_config *config, t_file **file);
bool	ea_texture(t_config *config, t_file **file);
void	write_config(char *pmap);
void	p1char(char **ptr);
void	p2char(char ***ptr);
void	t_file_free(t_file *file);
void	free_rgb(t_rgb *rgb);
void	free_all(t_config *config, t_file *file);
t_file	*linked_list(int ln);

#endif