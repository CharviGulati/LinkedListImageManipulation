#include "block.h"

using namespace std;

// set values in data attribute, based on a dimension x dimension square region
//   with upper-left corner at (left, upper) in the input PNG image
// The orientation of the pixels in the data vector must match the orientation
//   of the pixels in the PNG.
// PRE: upper and left (and upper + dimension - 1, left + dimension - 1) are valid
//        vector indices
void Block::Build(PNG &im, int upper, int left, int dimension) {
    for (int x = left; x < left + dimension; ++x) {
        vector<HSLAPixel> pixelData;
        for (int y = upper; y < upper + dimension; ++y) {
            HSLAPixel *pixel = im.getPixel(x, y);
            pixelData.push_back(*pixel);
        }
        this->data.push_back(pixelData);
    }
}


//// write the pixel colour data fom data attribute into im,
////   with upper-left corner at (left, upper)
//// PRE: upper and left (and upper + dimension - 1, left + dimension - 1) are valid
////        vector indices
void Block::Render(PNG &im, int upper, int left) const {
    int dimension = Dimension();
    int upperBoundX = left + dimension;
    int upperBoundY = upper + dimension;
    for (int x = left; x < upperBoundX; ++x) {
        for (int y = upper; y < upperBoundY; ++y) {
            HSLAPixel *currentPixel = im.getPixel(x, y);
            currentPixel->h = data[x - left][y - upper].h;
            currentPixel->s = data[x - left][y - upper].s;
            currentPixel->l = data[x - left][y - upper].l;
            currentPixel->a = data[x - left][y - upper].a;
        }
    }
}


void Block::FlipHorizontal() {
    int dimension = Dimension();
    for (int row = 0; row < dimension / 2; row++) {
        for (int col = 0; col < dimension; col++) {
            int swap = dimension - row - 1;
            HSLAPixel tempPixel = data[row][col];
            data[row][col] = data[swap][col];
            data[swap][col] = tempPixel;
        }
    }
}


// Mirror this block's pixel data vertically (along a horizontal axis)
void Block::FlipVertical() {
    int dimension = Dimension();
    for (int row = 0; row < dimension; row++) {
        for (int col = 0; col < dimension / 2; col++) {
            int swap = dimension - col - 1;
            HSLAPixel tempPixel = data[row][col];
            data[row][col] = data[row][swap];
            data[row][swap] = tempPixel;
        }
    }
}


// Return the horizontal (or vertical) size of the data block's image region
int Block::Dimension() const {
    return data.size();
}


// Returns the computed average luminance of the block
// Compute as the sum of each pixel's luminance value, divided by
//   the number of pixels in the block
double Block::AvgLuminance() const {
    int dimension = Dimension();
    int totalDimension = dimension * dimension;
    double totalLuminance = 0;

    for (int x = 0; x < dimension; ++x) {
        for (int y = 0; y < dimension; ++y) {
            totalLuminance += data[x][y].l;
        }
    }
    return totalLuminance / totalDimension;
}
