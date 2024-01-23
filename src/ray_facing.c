#include "../inc/maths.h"
#include "../inc/ray.h"

int	is_ray_facing_down(float angle)
{
	return (angle > 0 && angle < M_PI);
}

int	is_ray_facing_up(float angle)
{
	return (!is_ray_facing_down(angle));
}

int	is_ray_facing_right(float angle)
{
	return (angle < (M_PI / 2) || angle >(M_PI * 1.5));
}

int	is_ray_facing_left(float angle)
{
	return (!is_ray_facing_right(angle));
}