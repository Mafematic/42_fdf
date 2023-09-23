/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fszendzi <fszendzi@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 18:48:09 by fszendzi          #+#    #+#             */
/*   Updated: 2023/09/22 18:48:12 by fszendzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <X11/Xutil.h>
# include "mlx.h"
# include "../mlx/mlx_int.h"

# define MY_FLOAT_MAX 3.402823466e+38F
# define MY_FLOAT_MIN -3.402823466e+38F
#define PROJECTION_ISO 1
#define PROJECTION_ORTHO 2

typedef struct s_pixel
{
	int		x;
	int		y;
	int		z;
	float	w_x;
	float	w_y;
	float	iso_x;
	float	iso_y;
}	t_pixel;

typedef struct s_window
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		width;
	int		height;
	int		padding;
}	t_window;

typedef struct s_iso
{
	float	min_iso_x;
	float	max_iso_x;
	float	min_iso_y;
	float	max_iso_y;
}	t_iso;

typedef struct s_ortho {
    float min_ortho_x;
    float max_ortho_x;
    float min_ortho_y;
    float max_ortho_y;
} t_ortho;

typedef struct s_prog_data
{
	t_window	*win;
	t_pixel		***grid;
	t_iso		*iso;
	t_ortho		*ortho;
	int			rows;
	int			cols;
	int 		current_projection;
	float		scale_factor;
}	t_prog_data;

typedef struct s_image {
	char	*data;
	int		size_line;
	int		bits_pixel;
	int		endian;
}	t_image;

typedef struct s_line_vars
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
}	t_line_vars;

void		adapt_iso_pixel(t_prog_data *data);
void		adapt_ortho_pixel(t_prog_data *data);
int			ft_atoi(const char *nptr);
void		apply_zoom(t_prog_data *data, float scale_factor);
int			close_file(int fd);
void		close_window_and_free(t_window *window);
t_pixel		*create_element(t_pixel pt);
void		draw_grid(t_pixel ***grid, t_window *w, t_prog_data *data);
void		draw_line(t_image *img, t_window *w, t_pixel *start, t_pixel *end, int color);
void		put_pixel_to_image(t_image *img, t_window *win, int x, int y, int color);
t_iso		*find_min_max_iso(t_pixel ***grid, t_prog_data *data);
t_ortho		*find_min_max_ortho(t_pixel ***grid, t_prog_data *data);
int			find_rows_cols(t_prog_data *data, char *filename);
void		free_grid(t_pixel ***grid, int num_rows, int num_columns);
void		free_numbers_from_index(char **numbers_in_line, int start_idx);
void		free_words(char **words);
char		**ft_split(char *s, char c);
char		*ft_strdup(char *s);
size_t		ft_strlen(char *str);
char		*ft_substr(char *s, unsigned int start, size_t len);
void		free_grid(t_pixel ***grid, int num_rows, int num_columns);
int			handle_close(void *param);
int			handle_fail(char **line_num, t_pixel ***grid, int x, int y);
int			handle_key(int keycode, t_prog_data *data);
int			handle_overflow_columns(char **numbers_in_line, int y);
t_pixel		***initialize_grid(int num_rows, int num_columns);
int			ft_iswhitespace(char c);
int			open_file(char *file_path);
t_window	*open_window(int width, int height, char *title);
int			parse_file(t_pixel ***grid, t_prog_data *data, char *filename);
void		project_new(t_prog_data *data);

#endif
