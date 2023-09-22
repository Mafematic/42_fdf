#include <unistd.h>
#include <stdlib.h>
#include "mlx.h"
#include <math.h>
#include <float.h>
#include <stdio.h>
#include "../mlx/mlx_int.h"
#include <X11/Xutil.h>

//#define NUM_ROWS 116
//#define NUM_COLUMNS 200

typedef struct s_pixel
{
	int x;
    int y;
    int z;
    float wX;
	float wY;
	float isoX;
	float isoY;
} t_pixel;

typedef struct s_window {
    void *mlx_ptr;
    void *win_ptr;
    int width;
    int height;
	int padding;
} t_window;

typedef struct s_iso
{
	float min_iso_x;
    float max_iso_x;
    float min_iso_y;
    float max_iso_y;
} t_iso;

typedef struct s_prog_data
{
    t_window *win;
    t_pixel ***grid;
    t_iso *iso;
	int rows;
	int cols;
} t_prog_data;

typedef struct s_image {
    char *data;
    int size_line;
	int bits_pixel;
	int endian;
} t_image;

typedef struct  s_line_vars
{
    int x0;
    int y0;
    int x1;
    int y1;
    int dx;
    int dy;
    int sx;
    int sy;
    int err;
} t_line_vars;

int			ft_atoi(const char *nptr);
int			close_file(int fd);
void		close_window_and_free(t_window *window);
t_pixel* 	create_element(t_pixel pt);
void 		draw_grid(t_pixel ***grid, t_window *w, t_prog_data *data);
void		draw_line(t_image *img, t_pixel *start, t_pixel *end, int color);
t_iso		*find_min_max_iso(t_pixel ***grid, t_prog_data *data);
int			find_rows_cols(t_prog_data *data, char *filename);
char		**ft_split(char *s, char c);
char		*ft_strdup(char *s);
size_t		ft_strlen(char *str);
char		*ft_substr(char *s, unsigned int start, size_t len);
void		free_grid(t_pixel ***grid, int num_rows, int num_columns);
t_pixel 	***initialize_grid(int num_rows, int num_columns);
void		isopixel(t_pixel ***grid, t_window *w, t_iso *iso, t_prog_data *data);
int			ft_iswhitespace(char c);
int			open_file(char *file_path);
t_window 	*open_window(int width, int height, char *title);
int			parse_file(t_pixel ***grid, t_prog_data *data, char *filename);
void		put_pixel_to_image(t_image *img, int x, int y, int color);