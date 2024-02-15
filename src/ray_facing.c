#include "../inc/maths.h"
#include "../inc/ray.h"

int	is_ray_facing_down(float angle)
{
	return (angle > 0 && angle < M_PI);
}

int	is_ray_facing_up(float angle)
{
	return (angle > M_PI && angle < (M_PI * 2));
}

int	is_ray_facing_left(float angle)
{
	return (angle > (M_PI / 2) && angle < ((M_PI * 3) / 2));
}

int	is_ray_facing_right(float angle)
{
	return ((angle < (M_PI / 2) && angle > 0)
		|| ((angle > (M_PI * 3) / 2) && angle < (M_PI * 2)));
}
