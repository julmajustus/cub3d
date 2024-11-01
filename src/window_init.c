
#include "MLX42.h"
#include "cube.h"

void	window_init(t_caster *c)
{
	c->img->handle = mlx_init(WIDTH, HEIGHT, c->window_title, true);
	if (!c->img->handle)
		exit_failure(c, "mlx_init failed");
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mlx_set_cursor_mode(c->img->handle, MLX_MOUSE_HIDDEN);
	reset_images(c);
	mlx_set_mouse_pos(c->img->handle, WIDTH / 2, HEIGHT / 2);
}
