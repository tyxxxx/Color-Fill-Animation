#include "customColorPicker.h"

customColorPicker::customColorPicker(PNG & img, double tolerance)
{
	/* your code here! */
	im = img;
	tol = tolerance;
}

HSLAPixel customColorPicker::operator()(int x, int y)
{
	for (int k = 1; k < 6; k++) {
		for (int i = -6*k; i <= 6*k; i++) {
			for (int j = -6*k; j <= 6*k; j++) {
				if (i * i + j * j <= 36*k*k) {
					if (x + i < 0 || x + i >= im.width()
						|| y + j < 0 || y + j >= im.height()
						|| im.getPixel(x + i, y + j)->dist(*im.getPixel(x, y)) > tol) {
						im.getPixel(x, y)->l = (im.getPixel(x+i, y+j )->l - im.getPixel(x, y)->l) * (9-k) / 10 + im.getPixel(x, y)->l;
						return *im.getPixel(x, y);
					}
				}
			}
		}
	}
	
	return *im.getPixel(x, y);
}
