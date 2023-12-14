#include "primlib.h"
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#define VERTICES 5
#define ROTATION_ANGLE M_PI / 180
#define ANGLE_BETWEEN_SIDES 2.0f * M_PI / VERTICES
#define CENTER_POSITION_X gfx_screenWidth() / 2
#define CENTER_POSITION_Y gfx_screenHeight() / 2
#define MINIMUM_RADIUS 20
#define LOOP 1

int check_radius(int radius, int increase);

int main(int argc, char *argv[])
{
	if (gfx_init())
	{
		exit(3);
	}

	int radius = MINIMUM_RADIUS;

	float current_angle = 0;

	int x_coordinate[VERTICES];
	int y_coordinate[VERTICES];

	int increase = 1;

	while (LOOP)
	{
		for (int coordinate = 0; coordinate < VERTICES; ++coordinate)
		{
			x_coordinate[coordinate] = CENTER_POSITION_X + radius * cos(current_angle + (coordinate)*ANGLE_BETWEEN_SIDES);
			y_coordinate[coordinate] = CENTER_POSITION_Y + radius * sin(current_angle + (coordinate)*ANGLE_BETWEEN_SIDES);
		}

		for (int coordinate = 0; coordinate < VERTICES; ++coordinate)
		{
			if (coordinate == VERTICES - 1)
			{
				gfx_line(x_coordinate[coordinate], y_coordinate[coordinate], x_coordinate[0], y_coordinate[0], YELLOW);
			}
			else
			{
				gfx_line(x_coordinate[coordinate], y_coordinate[coordinate], x_coordinate[coordinate + 1], y_coordinate[coordinate + 1], YELLOW);
			}
		}
		gfx_rect(0, 0, gfx_screenWidth() - 1, gfx_screenHeight() - 1, BLACK);
		current_angle += ROTATION_ANGLE;

		while (current_angle >= (2.0f * M_PI)){
			current_angle = current_angle - 2.0f * M_PI;
		}

		increase = check_radius(radius, increase);

		if (increase)
		{
			radius++;
		}
		else
		{
			radius--;
		}

		gfx_updateScreen();
		SDL_Delay(10);
		gfx_pollkey();
	}

	gfx_getkey();
	return 0;
}

int check_radius(int radius, int increase)
{
	if (radius == CENTER_POSITION_Y)
	{
		increase = 0;
	}
	else if (radius == MINIMUM_RADIUS)
	{
		increase = 1;
	}
	return increase;
}