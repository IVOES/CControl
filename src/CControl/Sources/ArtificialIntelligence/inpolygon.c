/*
 * inpolygon.c
 *
 *  Created on: 27 dec. 2021
 *      Author: Daniel Mårtensson
 */

#include "../../Headers/Functions.h"

/*
 * Check if the coordinates x and y are inside the polygon px and py
 * px[p] - Points in x-axis
 * py[p] - Points in y-axis
 * Return 1 or 0 if the coordinate x,y is inside the polygon px, py
 */
uint8_t inpolygon(float x, float y, float px[], float py[], uint8_t p){
	/* Get the max y, min y, max x, min y */
	float max_y = py[0];
	float max_x = px[0];
	float min_y = py[0];
	float min_x = px[0];
	uint8_t i;
	for(i = 0; i < p; i++){
		max_y = vmax(py[i], max_y);
		max_x = vmax(px[i], max_x);
		min_y = vmin(py[i], min_y);
		min_x = vmin(px[i], min_x);
	}

	/* Check if we are outside the polygon */
	if (y < min_y || y > max_y || x < min_x || x > max_x) {
		return 0;
	}

	/* Do a better check */
	uint8_t ok = 0;
	i = 0;
	uint8_t j = p - 1;
	while (i < p) {
		max_x = px[i];
		min_x = px[j];
		max_y = py[i];
		min_y = py[j];
		if (((max_x > x) != (min_x > x)) && (y < (min_y - max_y) * (x - max_x) / (min_x - max_x) + max_y)) {
			ok = !ok;
		}

		/* Old code
		if (((px[i] > x) != (px[j] > x)) && (y < (py[j] - py[i]) * (x - px[i]) / (px[j] - px[i]) + py[i])) {
			ok = !ok;
		}*/

		j = i;
		i++;
	}
	return ok;
}
