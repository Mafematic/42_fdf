#include "../includes/get_next_line.h"
#include "../includes/fdf.h"

int handle_key(int keycode, void *param)
{
	t_program_data *data = (t_program_data *)param;
	printf("Keycode: %d\n", keycode);

    if (keycode == 65307) 
    {   
        close_window_and_free(data->window);
        free_grid(data->grid, data->rows, data->cols);
        free(data->iso);
        exit(0); 
    }
    return (0);
}

int handle_close(void *param)
{
    t_program_data *data = (t_program_data *)param;
    
    close_window_and_free(data->window);
    free_grid(data->grid, data->rows, data->cols);
    free(data->iso);
    
    exit(0);
    return (0); // Return value is often not checked for the close event, but it's good practice to have it.
}

void close_window_and_free(t_window *window) 
{
    if (window) 
    {
        if (window->win_ptr) 
        {
            mlx_destroy_window(window->mlx_ptr, window->win_ptr);
        }

        // This is the added part: closing the display.
        if (window->mlx_ptr) 
        {
            t_xvar *xvar = (t_xvar *)window->mlx_ptr;
            if (xvar && xvar->display) 
            {
                XCloseDisplay(xvar->display);
            }
            free(window->mlx_ptr);
        }
        
        free(window);
    }
}


int main(void)
{
	t_program_data data;
	t_window *w;
	t_pixel ***grid;

	if (!find_rows_cols(&data))
	{
		return 1;
	}
	printf("Rows: %d\n", data.rows);
	printf("Cols: %d\n", data.cols);
	w = open_window(800, 600, "Frido's Window");
	if (!w)
	{
		return (1);
	}
	grid = initialize_grid(data.rows, data.cols);
	if (!grid) 
	{
		close_window_and_free(w);
        return 1;
    }
	if (!parse_file(grid, w, &data))
	{
		close_window_and_free(w);
		free_grid(grid, data.rows, data.cols);
    	return 1;
	}

	t_iso_bounds *iso = find_min_max_iso(grid, &data);
	if (!iso) 
	{  // Checking if memory allocation failed
		printf("Failed to allocate memory for iso bounds\n");
		close_window_and_free(w);
		free_grid(grid, data.rows, data.cols);
    	return 1;
	}

	isopixel(grid, w, iso, &data); 
	draw_grid(grid, w, &data);

	data.window = w;
    data.grid = grid;
    data.iso = iso;

    mlx_hook(w->win_ptr, 2, 1L<<0, handle_key, &data);
	mlx_hook(w->win_ptr, 17, 1L<<17, handle_close, &data);


    mlx_loop(w->mlx_ptr);
    return 0;
}