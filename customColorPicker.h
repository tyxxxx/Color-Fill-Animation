#ifndef CUSTOMCOLORPICKER_H
#define CUSTOMCOLORPICKER_H

#include "colorPicker.h"

class customColorPicker : public colorPicker
{
public:

	customColorPicker(PNG & img, double tolerance);

	/**
	 * Picks the color for pixel (x, y). If the x or y coordinate is
	 * near the border of the fill, or the border of the image,
	 * the fillColor will be returned.
	 * Otherwise, the current color of (x,y) will be returned.
	 *
	 * @param x The x coordinate to pick a color for.
	 * @param y The y coordinat to pick a color for.
	 * @return The color chosen for (x, y).
	 */
	virtual HSLAPixel operator()(int x, int y);

private:
	PNG im;
	double tol;
};

#endif