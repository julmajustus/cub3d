
#include "cube.h"

void	window_init(t_caster *c)
{
	c->img->handle = mlx_init(WIDTH, HEIGHT, c->window_title, true);
	if (!c->img->handle)
		exit_failure(c, "mlx_init failed");
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	reset_images(c);
}
