
#include "stats.h"


// initialize the private vectors so that, for each color,  entry 
	// (x,y) is the cumulative sum of the the color values from (0,0)
	// to (x,y). Similarly, the sumSq vectors are the cumulative
	// sum of squares from (0,0) to (x,y).
stats::stats(PNG & im){

    // vector< vector< long >> sumRed;
	// vector< vector< long >> sumGreen;
	// vector< vector< long >> sumBlue;
	// vector< vector< long >> sumsqRed;
	// vector< vector< long >> sumsqGreen;
	// vector< vector< long >> sumsqBlue;

//https://stackoverflow.com/questions/15889578/how-can-i-resize-a-2d-vector-of-objects-given-the-width-and-height/44270940 & piazza 
    sumRed.resize(im.width() , vector<long>(im.height()));
    sumGreen.resize(im.width() , vector<long>(im.height()));
    sumBlue.resize(im.width() , vector<long>(im.height()));
    sumsqRed.resize(im.width() , vector<long>(im.height()));
    sumsqGreen.resize(im.width() , vector<long>(im.height()));
    sumsqBlue.resize(im.width() , vector<long>(im.height()));
// YOUR CODE HERE!!
for (unsigned int x = 0;  x < im.width(); x++) {
    for (unsigned int y = 0; y < im.height(); y++) {
        if (x == 0 && y == 0){
            sumRed[x][y] = (im.getPixel(x,y)->r);
            sumGreen[x][y] = (im.getPixel(x,y)->g);
            sumBlue[x][y] = (im.getPixel(x,y)->b);
            sumsqRed[x][y] = (im.getPixel(x,y)->r) * (im.getPixel(x,y)->r);
            sumsqGreen[x][y] = (im.getPixel(x,y)->g) * (im.getPixel(x,y)->g);
            sumsqBlue[x][y] = (im.getPixel(x,y)->b) * (im.getPixel(x,y)->b);
        }
        else if (x == 0 && y != 0) {
            // sum of the pixel plus all the previous sums
            sumRed[x][y] = sumRed[x][y-1] + (im.getPixel(x,y)->r);
            sumGreen[x][y] = sumGreen[x][y-1] + (im.getPixel(x,y)->g);
            sumBlue[x][y] = sumBlue[x][y-1] + (im.getPixel(x,y)->b);
            sumsqRed[x][y] = sumsqRed[x][y-1] + (im.getPixel(x,y)->r) * (im.getPixel(x,y)->r);
            sumsqGreen[x][y] = sumsqGreen[x][y-1] + (im.getPixel(x,y)->g) * (im.getPixel(x,y)->g);
            sumsqBlue[x][y] = sumsqBlue[x][y-1] + (im.getPixel(x,y)->b) * (im.getPixel(x,y)->b);
           
        }
         else if (x != 0 && y == 0) {
            // sum of the pixel plus all the previous sums
            sumRed[x][y] = sumRed[x-1][y] + (im.getPixel(x,y)->r);
            sumGreen[x][y] = sumGreen[x-1][y] + (im.getPixel(x,y)->g);
            sumBlue[x][y] = sumBlue[x-1][y] + (im.getPixel(x,y)->b);
            sumsqRed[x][y] = sumsqRed[x-1][y] + (im.getPixel(x,y)->r) * (im.getPixel(x,y)->r);
            sumsqGreen[x][y] = sumsqGreen[x-1][y] + (im.getPixel(x,y)->g) * (im.getPixel(x,y)->g);
            sumsqBlue[x][y] = sumsqBlue[x-1][y] + (im.getPixel(x,y)->b) * (im.getPixel(x,y)->b);
           
        }
        else if (x != 0 && y != 0) {
            sumRed[x][y] = sumRed[x-1][y] + sumRed[x][y-1] + (im.getPixel(x,y)->r) - sumRed[x-1][y-1];
            sumGreen[x][y] = sumGreen[x-1][y] + sumGreen[x][y-1] + (im.getPixel(x,y)->g) - sumGreen[x-1][y-1];
            sumBlue[x][y] = sumBlue[x-1][y] + sumBlue[x][y-1] + (im.getPixel(x,y)->b) - sumBlue[x-1][y-1];
            sumsqRed[x][y] = sumsqRed[x-1][y] + sumsqRed[x][y-1] + (im.getPixel(x,y)->r) * (im.getPixel(x,y)->r) - sumsqRed[x-1][y-1];
            sumsqGreen[x][y] = sumsqGreen[x-1][y] + sumsqGreen[x][y-1] + (im.getPixel(x,y)->g) * (im.getPixel(x,y)->g) - sumsqGreen[x-1][y-1];
            sumsqBlue[x][y] = sumsqBlue[x-1][y] +  sumsqBlue[x][y-1] + (im.getPixel(x,y)->b) * (im.getPixel(x,y)->b) - sumsqBlue[x-1][y-1] ;
        }
    }
}

}
/* returns the sums of all pixel values across all color channels.
	* useful in computing the score of a rectangle
	* PA3 function
	* @param channel is one of r, g, or b
	* @param ul is (x,y) of the upper left corner of the rectangle 
	* @param lr is (x,y) of the lower right corner of the rectangle */
long stats::getSum(char channel, pair<int,int> ul, pair<int,int> lr){

// YOUR CODE HERE!!
    long sum = 0;
    if (channel == 'r'){
        if (ul.first == 0 && ul.second == 0){
            sum = sumRed[lr.first][lr.second];
        }
        else if (ul.first == 0 && ul.second != 0) {
            sum = sumRed[lr.first][lr.second] - sumRed[lr.first][ul.second-1];
        }
        else if (ul.first != 0 && ul.second == 0) {
            sum = sumRed[lr.first][lr.second] - sumRed[ul.first-1][lr.second];
        }
        else if (ul.first != 0 && ul.second != 0) {
            long rect1 = sumRed[lr.first][ul.second-1];
            long rect2 = sumRed[ul.first-1][lr.second];
            sum = sumRed[lr.first][lr.second] - (rect1 + rect2 - sumRed[ul.first-1][ul.second-1]);
            // 
            //sum = sumRed[lr.first][lr.second] - (sumRed[lr.first][ul.second-1] + sumRed[ul.first-1][lr.second] - sumRed[ul.first-1][ul.second-1])
        }
    }
    else if (channel == 'g'){
        if (ul.first == 0 && ul.second == 0){
            sum = sumGreen[lr.first][lr.second];
        }
        else if (ul.first == 0 && ul.second != 0) {
            sum = sumGreen[lr.first][lr.second] - sumGreen[lr.first][ul.second-1];
        }
        else if (ul.first != 0 && ul.second == 0) {
            sum = sumGreen[lr.first][lr.second] - sumGreen[ul.first-1][lr.second];
        }
        else if (ul.first != 0 && ul.second != 0) {
            long rect1 = sumGreen[lr.first][ul.second-1];
            long rect2 = sumGreen[ul.first-1][lr.second];
            sum = sumGreen[lr.first][lr.second] - (rect1 + rect2 - sumGreen[ul.first-1][ul.second-1]);
        }
    }
    else if (channel == 'b'){
        if (ul.first == 0 && ul.second == 0){
            sum = sumBlue[lr.first][lr.second];
        }
        else if (ul.first == 0 && ul.second != 0) {
            sum = sumBlue[lr.first][lr.second] - sumBlue[lr.first][ul.second-1];
        }
        else if (ul.first != 0 && ul.second == 0) {
            sum = sumBlue[lr.first][lr.second] - sumBlue[ul.first-1][lr.second];
        }
        else if (ul.first != 0 && ul.second != 0) {
            long rect1 = sumBlue[lr.first][ul.second-1];
            long rect2 = sumBlue[ul.first-1][lr.second];
            sum = sumBlue[lr.first][lr.second] - (rect1 + rect2 - sumBlue[ul.first-1][ul.second-1]);
        }
    }
    return sum;

}
/* returns the sums of squares of all pixel values across all color channels.
	* useful in computing the score of a rectangle
	* PA3 function
	* @param channel is one of r, g, or b
	* @param ul is (x,y) of the upper left corner of the rectangle 
	* @param lr is (x,y) of the lower right corner of the rectangle */
long stats::getSumSq(char channel, pair<int,int> ul, pair<int,int> lr){

// YOUR CODE HERE!!
  long sumsq = 0;
    if (channel == 'r'){
        if (ul.first == 0 && ul.second == 0){
            sumsq = sumsqRed[lr.first][lr.second];
        }
        else if (ul.first == 0 && ul.second != 0) {
            sumsq = sumsqRed[lr.first][lr.second] - sumsqRed[lr.first][ul.second-1];
        }
        else if (ul.first != 0 && ul.second == 0) {
            sumsq = sumsqRed[lr.first][lr.second] - sumsqRed[ul.first-1][lr.second];
        }
        else if (ul.first != 0 && ul.second != 0) {
            long rect1 = sumsqRed[lr.first][ul.second-1];
            long rect2 = sumsqRed[ul.first-1][lr.second];
            sumsq = sumsqRed[lr.first][lr.second] - (rect1 + rect2 - sumsqRed[ul.first-1][ul.second-1]);
        }
    }
    else if (channel == 'g'){
        if (ul.first == 0 && ul.second == 0){
            sumsq = sumsqGreen[lr.first][lr.second];
        }
        else if (ul.first == 0 && ul.second != 0) {
            sumsq = sumsqGreen[lr.first][lr.second] - sumsqGreen[lr.first][ul.second-1];
        }
        else if (ul.first != 0 && ul.second == 0) {
            sumsq = sumsqGreen[lr.first][lr.second] - sumsqGreen[ul.first-1][lr.second];
        }
        else if (ul.first != 0 && ul.second != 0) {
            long rect1 =  sumsqGreen[lr.first][ul.second-1];
            long rect2 =  sumsqGreen[ul.first-1][lr.second];
            sumsq = sumsqGreen[lr.first][lr.second] - (rect1 + rect2 - sumsqGreen[ul.first-1][ul.second-1]);
        }
    }
    else if (channel == 'b'){
        if (ul.first == 0 && ul.second == 0){
            sumsq = sumsqBlue[lr.first][lr.second];
        }
        else if (ul.first == 0 && ul.second != 0) {
            sumsq = sumsqBlue[lr.first][lr.second] - sumsqBlue[lr.first][ul.second-1];
        }
        else if (ul.first != 0 && ul.second == 0) {
            sumsq = sumsqBlue[lr.first][lr.second] - sumsqBlue[ul.first-1][lr.second];
        }
        else if (ul.first != 0 && ul.second != 0) {
            long rect1 = sumsqBlue[lr.first][ul.second-1];
            long rect2 = sumsqBlue[ul.first-1][lr.second];
            sumsq = sumsqBlue[lr.first][lr.second] - (rect1 + rect2 - sumsqBlue[ul.first-1][ul.second-1]);
        }
    }
    return sumsq;

}

// given a rectangle, return the number of pixels in the rectangle
	/* @param ul is (x,y) of the upper left corner of the rectangle 
	* @param lr is (x,y) of the lower right corner of the rectangle */

long stats::rectArea(pair<int,int> ul, pair<int,int> lr){

// YOUR CODE HERE!!

long width = lr.first - ul.first + 1 ; 
long height = lr.second - ul.second + 1;
long area = width* height;

return area;

}

// given a rectangle, compute its sum of squared deviations from mean, over all color channels.
// given a rectangle, compute its sum of squared deviations from mean, over all color channels.
	/* @param ul is (x,y) of the upper left corner of the rectangle 
	* @param lr is (x,y) of the lower right corner of the rectangle */
long stats::getScore(pair<int,int> ul, pair<int,int> lr){

    long area = rectArea(ul, lr);
    long redScore = getSumSq('r', ul, lr) - ((getSum('r', ul, lr)*getSum('r', ul, lr))/area);
    long greenScore = getSumSq('g', ul, lr) - ((getSum('g', ul, lr)*getSum('g', ul, lr))/area);
    long blueScore = getSumSq('b', ul, lr) - ((getSum('b', ul, lr)*getSum('b', ul, lr))/area);

    long total = redScore + greenScore + blueScore;
    return total;

// YOUR CODE HERE!!

}

	// given a rectangle, return the average color value over the rectangle as a pixel.
	/* Each color component of the pixel is the average value of that component over
	* the rectangle.
	* @param ul is (x,y) of the upper left corner of the rectangle 
	* @param lr is (x,y) of the lower right corner of the rectangle */		
RGBAPixel stats::getAvg(pair<int,int> ul, pair<int,int> lr) {

// YOUR CODE HERE!!
long area = rectArea(ul, lr);
long averageRed = getSum('r', ul, lr)/area;
long averageGreen = getSum('g', ul, lr)/area;
long averageBlue= getSum('b', ul, lr)/area;

RGBAPixel pixel = RGBAPixel(averageRed, averageGreen, averageBlue);

return pixel;



}
