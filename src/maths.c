#include "../inc/maths.h"
#include "../inc/constance.h"

void	normalize_angle(float *ray_angle)
{
	*ray_angle = remainder(*ray_angle, M_PI * 2);
	if (*ray_angle < 0)
		*ray_angle = M_PI * 2 + *ray_angle;
}

float	distance_between_points(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}
