#include "../includes/get_next_line.h"
#include "../includes/fdf_bonus.h"

void apply_zoom(t_prog_data *data, float scale_factor) 
{
    for (int i = 0; i < data->rows; i++) {
        for (int j = 0; j < data->cols; j++) {
            t_pixel *cur_pixel = data->grid[i][j];
            cur_pixel->iso_x *= scale_factor;
            cur_pixel->iso_y *= scale_factor;
        }
    }
}
