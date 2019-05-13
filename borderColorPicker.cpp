#include "borderColorPicker.h"

borderColorPicker::borderColorPicker(HSLAPixel fillColor, PNG & img, double tolerance,HSLAPixel center)
{
	color = fillColor;
	im = img;
	tol = tolerance;
	ctr = center;
/* Your code here! */
}

HSLAPixel borderColorPicker::operator()(int x, int y)
{
	bool isBorder = false;
	for (int i = -3; i <= 3; i++) {
		for (int j = -3; j <= 3; j++) {
			if (i * i + j * j <= 9) {
				if (x + i < 0 || x + i >= im.width()
					|| y + j < 0 || y + j >= im.height()
					|| im.getPixel(x + i, y + j)->dist(ctr) > tol) {
					return color;
				}
			}
		}
	}
	return *im.getPixel(x,y);
/* Your code here! */
}