/**
 * @file filler.cpp
 * Implementation of functions in the filler namespace. 
 *
 */
//#include "filler.h"

animation filler::fillStripeDFS(PNG& img, int x, int y, HSLAPixel fillColor,
                                int stripeSpacing, double tolerance, int frameFreq)
{
    /**
     * @todo Your code here! 
     */
	stripeColorPicker a(fillColor, stripeSpacing);
	return fill<Stack>(img, x, y, a, tolerance, frameFreq);
}

animation filler::fillBorderDFS(PNG& img, int x, int y,
                                    HSLAPixel borderColor, double tolerance, int frameFreq)
{
    /**
     * @todo Your code here! 
     */
	borderColorPicker a(borderColor, img, tolerance, *img.getPixel(x,y));
	return fill<Stack>(img, x, y, a, tolerance, frameFreq);
}

/* Given implementation of a DFS rainbow fill. */
animation filler::fillRainDFS(PNG& img, int x, int y,
                                    long double freq, double tolerance, int frameFreq)
{
    rainbowColorPicker a(freq);
    return fill<Stack>(img, x, y, a, tolerance, frameFreq);
}

animation filler::fillStripeBFS(PNG& img, int x, int y, HSLAPixel fillColor,
                                int stripeSpacing, double tolerance, int frameFreq)
{
    /**
     * @todo Your code here! 
     */
	stripeColorPicker a(fillColor, stripeSpacing);
	return fill<Queue>(img, x, y, a, tolerance, frameFreq);
}

animation filler::fillBorderBFS(PNG& img, int x, int y,
                                    HSLAPixel borderColor, double tolerance, int frameFreq)
{
    /**
     * @todo Your code here! You should replace the following line with a
     */
	borderColorPicker a(borderColor, img, tolerance, *img.getPixel(x, y));
	return fill<Queue>(img, x, y, a, tolerance, frameFreq);
}

/* Given implementation of a BFS rainbow fill. */
animation filler::fillRainBFS(PNG& img, int x, int y,
                                    long double freq, double tolerance, int frameFreq)
{
    rainbowColorPicker a(freq);
    return fill<Queue>(img, x, y, a, tolerance, frameFreq);
}



template <template <class T> class OrderingStructure>
animation filler::fill(PNG& img, int x, int y, colorPicker& fillColor,
                       double tolerance, int frameFreq)
{
    /**
     * @todo You need to implement this function!
     *
     * This is the basic description of a flood-fill algorithm: Every fill
     * algorithm requires an ordering structure, which is passed to this
     * function via its template parameter. For a breadth-first-search
     * fill, that structure is a Queue, for a depth-first-search, that
     * structure is a Stack. To begin the algorithm, you simply place the
     * given point in the ordering structure, marking it processed
     * (the way you mark it is a design decision you'll make yourself).
     * We have a choice to either change the color, if appropriate, when we
     * add the point to the OS, or when we take it off. In our test cases,
     * we have assumed that you will change the color when a point is added
     * to the structure. 
     *
     * Until the structure is empty, you do the following:
     *
     * 1.     Remove a point from the ordering structure, and then...
     *
     *        1.    add its unprocessed neighbors whose color values are 
     *              within (or equal to) tolerance distance from the center, 
     *              to the ordering structure.
     *        2.    use the colorPicker to set the new color of the point.
     *        3.    mark the point as processed.
     *        4.    if it is an appropriate frame, send the current PNG to the
     *              animation (as described below).
     *
     * 2.     When implementing your breadth-first-search and
     *        depth-first-search fills, you will need to explore neighboring
     *        pixels in some order.
     *
     *        For this assignment, each pixel p has 8 neighbors, consisting of 
     *        the 8 pixels who share an edge or corner with p. (We leave it to
     *        you to describe those 8 pixel locations, relative to the location
     *        of p.)
     *
     *        While the order in which you examine neighbors does not matter
     *        for a proper fill, you must use the same order as we do for
     *        your animations to come out like ours! 
     *
     *        The order you should put
     *        neighboring pixels **ONTO** the ordering structure (queue or stack) 
     *        is as follows: **UPRIGHT(+x,-y), UP(-y), UPLEFT(-x,-y), LEFT(-x), 
     *        DOWNLEFT(-x,+y), DOWN(+y), DOWNRIGHT(+x,+y), RIGHT(+x)**
     *
     *        If you do them in a different order, your fill may
     *        still work correctly, but your animations will be different
     *        from the grading scripts!
     *
     *        IMPORTANT NOTE: *UP*
     *        here means towards the top of the image, so since an image has
     *        smaller y coordinates at the top, this is in the *negative y*
     *        direction. Similarly, *DOWN* means in the *positive y*
     *        direction.  
     *
     * 3.     For every k pixels filled, **starting at the kth pixel**, you
     *        must add a frame to the animation, where k = frameFreq.
     *
     *        For example, if frameFreq is 4, then after the 4th pixel has
     *        been filled you should add a frame to the animation, then again
     *        after the 8th pixel, etc.  You must only add frames for the
     *        number of pixels that have been filled, not the number that
     *        have been checked. So if frameFreq is set to 1, a pixel should
     *        be filled every frame.
     * 4.     Finally, as you leave the function, send one last frame to the
     *        animation. This frame will be the final result of the fill, and 
     *        it will be the one we test against.
     */
	OrderingStructure<int> toProcessX;
	OrderingStructure<int> toProcessY;
	animation ani;
	HSLAPixel originalPixel = *img.getPixel(x, y);
	HSLAPixel *ctrPixel = img.getPixel(x, y);
	int processedCounter = 0;
	toProcessX.add(x);
	toProcessY.add(y);
	bool ** processed = new bool *[img.width()];
	for (unsigned int xPos = 0; xPos < img.width(); xPos++)
	{
		processed[xPos] = new bool[img.height()];
		for (unsigned int yPos = 0; yPos < img.height(); yPos++) {
			processed[xPos][yPos] = false;
		}
	}
	*ctrPixel = fillColor(x, y);
	processedCounter++;
	processed[x][y] = true;
	while (!toProcessX.isEmpty() && !toProcessY.isEmpty()) {
		int currX = toProcessX.remove();
		int currY = toProcessY.remove();
		if (currX + 1 < img.width() && currY - 1 >= 0 && img.getPixel(currX + 1, currY - 1)->dist(originalPixel) <= tolerance) {
			if (!processed[currX + 1][currY - 1]) {
				toProcessX.add(currX + 1);
				toProcessY.add(currY - 1);
				processedCounter += 1;
				processed[currX + 1][currY - 1] = true;
				*img.getPixel(currX + 1, currY - 1) = fillColor(currX + 1, currY - 1);
				if (processedCounter % frameFreq == 0) {
					ani.addFrame(img);
				}
			}
		}
		if (currY - 1 >= 0 && img.getPixel(currX, currY - 1)->dist(originalPixel) <= tolerance) {
			if (!processed[currX][currY - 1]) {
				toProcessX.add(currX);
				toProcessY.add(currY - 1);
				processedCounter += 1;
				processed[currX][currY - 1] = true;
				*img.getPixel(currX, currY - 1) = fillColor(currX, currY - 1);
				if (processedCounter % frameFreq == 0) {
					ani.addFrame(img);
				}
			}
		}
		if (currX - 1 >= 0 && currY - 1 >= 0 && img.getPixel(currX - 1, currY - 1)->dist(originalPixel) <= tolerance) {
			if (!processed[currX - 1][currY - 1]) {
				toProcessX.add(currX - 1);
				toProcessY.add(currY - 1);
				processedCounter += 1;
				processed[currX - 1][currY - 1] = true;
				*img.getPixel(currX - 1, currY - 1) = fillColor(currX - 1, currY - 1);
				if (processedCounter % frameFreq == 0) {
					ani.addFrame(img);
				}
			}
		}
		if (currX - 1 >= 0 && img.getPixel(currX - 1, currY)->dist(originalPixel) <= tolerance) {
			if (!processed[currX - 1][currY]) {
				toProcessX.add(currX - 1);
				toProcessY.add(currY);
				processedCounter += 1;
				processed[currX - 1][currY] = true;
				*img.getPixel(currX - 1, currY) = fillColor(currX - 1, currY);
				if (processedCounter % frameFreq == 0) {
					ani.addFrame(img);
				}
			}
		}
		if (currX - 1 >= 0 && currY + 1 < img.height() && img.getPixel(currX - 1, currY + 1)->dist(originalPixel) <= tolerance) {
			if (!processed[currX-1][currY + 1]) {
				toProcessX.add(currX-1);
				toProcessY.add(currY + 1);
				processedCounter += 1;
				processed[currX - 1][currY + 1] = true;
				*img.getPixel(currX - 1, currY + 1) = fillColor(currX - 1, currY + 1);
				if (processedCounter % frameFreq == 0) {
					ani.addFrame(img);
				}
			}
		}
		if (currY + 1 < img.height() && img.getPixel(currX, currY + 1)->dist(originalPixel) <= tolerance) {
			if (!processed[currX][currY + 1]) {
				toProcessX.add(currX);
				toProcessY.add(currY + 1);
				processedCounter += 1;
				processed[currX][currY + 1] = true;
				*img.getPixel(currX, currY + 1) = fillColor(currX, currY + 1);
				if (processedCounter % frameFreq == 0) {
					ani.addFrame(img);
				}
			}
		}
		if (currX + 1 < img.width() && currY + 1 < img.height() && img.getPixel(currX + 1, currY + 1)->dist(originalPixel) <= tolerance) {
			if (!processed[currX + 1][currY + 1]) {
				toProcessX.add(currX + 1);
				toProcessY.add(currY + 1);
				processedCounter += 1;
				processed[currX + 1][currY + 1] = true;
				*img.getPixel(currX + 1, currY + 1) = fillColor(currX + 1, currY + 1);
				if (processedCounter % frameFreq == 0) {
					ani.addFrame(img);
				}
			}
		}
		if (currX + 1 < img.width() && img.getPixel(currX + 1, currY)->dist(originalPixel) <= tolerance) {
			if (!processed[currX + 1][currY]) {
				toProcessX.add(currX + 1);
				toProcessY.add(currY);
				processedCounter += 1;
				processed[currX + 1][currY] = true;
				*img.getPixel(currX + 1, currY) = fillColor(currX + 1, currY);
				if (processedCounter % frameFreq == 0) {
					ani.addFrame(img);
				}
			}
		}
	}
	ani.addFrame(img);
	for (int k = 0; k < img.width(); k++) {
		delete[] processed[k];
	}
	delete[] processed;

	return ani;
} 
