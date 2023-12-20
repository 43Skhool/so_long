#include "so_long.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_line(t_data img)
{
	position a = {10, 10};
	position b = {100, 100};
	int m = (a.y - b.y) / (a.x - b.x);
	int intercept = a.y - (m * a.x);
	int x = a.x;
	int y = 0;
	printf("m is %d and intercept is %d", m, intercept);
	while (x < b.x)
	{
		y = (m * x) - intercept;
		my_mlx_pixel_put(&img, x, y, 0xFFFF0000);
		x++;
	}
}

int gcd(int a, int b)
{
	while (b != 0)
	{
		a %= b;
		a ^= b;
		b ^= a;
		a ^= b;
	}

	return a;
}

int	window_close(int keycode, t_vars *vars)
{
	printf("%d: closing window", keycode);
	mlx_destroy_window(vars->mlx, vars->win);
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void draw_line(t_data img, int beginX, int beginY, int endX, int endY, int color)
{
    double deltaX = endX - beginX;
    double deltaY = endY - beginY;
    int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
    deltaX /= pixels;
    deltaY /= pixels;
    double pixelX = beginX;
    double pixelY = beginY;
    while (pixels)
    {
        my_mlx_pixel_put(&img, pixelX, pixelY, color);
        pixelX += deltaX;
        pixelY += deltaY;
        --pixels;
    }
}

void	window_test()
{
	int width = 1920, height = 1080;
	t_vars	vars;
	t_data	img;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, width, height, "Hello world!");
	img.img = mlx_new_image(vars.mlx, width, height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_hook(vars.win, 2, 1L<<0, window_close, &vars);
	mlx_loop(vars.mlx);
}
