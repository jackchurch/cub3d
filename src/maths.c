#include "../inc/maths.h"
#include "../inc/constance.h"

void	normalizeAngle(float *rayAngle)
{
	*rayAngle = remainder(*rayAngle, M_PI * 2);
	if (*rayAngle < 0)
		*rayAngle = M_PI * 2 + *rayAngle;
}

float distanceBetweenPoints(float x1, float y1, float x2, float y2)
{
	return (sqrt( (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) ) );
}
