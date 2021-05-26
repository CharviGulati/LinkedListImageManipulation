// File:        block.h
// Date:        2021-05-20 03:28
// Description: Definition of Block class, CPSC 221 2021S PA1
//
// DO NOT MODIFY THE CONTENTS OF THIS FILE
//

#ifndef _BLOCK_H_
#define _BLOCK_H_

#include <vector>
#include <iostream>
#include "cs221util/PNG.h"
#include "cs221util/HSLAPixel.h"

using namespace std;
using namespace cs221util;

class Block {

public:

    // set values in data attribute, based on a dimension x dimension square region
    //   with upper-left corner at (left, upper) in the input PNG image
    // The orientation of the pixels in the data vector must match the orientation
    //   of the pixels in the PNG.
    // PRE: upper and left (and upper + dimension - 1, left + dimension - 1) are valid
    //        vector indices
    void Build(PNG &im, int upper, int left, int dimension);

    // write the pixel colour data fom data attribute into im,
    //   with upper-left corner at (left, upper)
    // PRE: upper and left (and upper + dimension - 1, left + dimension - 1) are valid
    //        vector indices
    void Render(PNG &im, int upper, int left) const;

    // Mirror this block's pixel data horizontally (along a vertical axis)
    void FlipHorizontal();

    // Mirror this block's pixel data vertically (along a horizontal axis)
    void FlipVertical();

    // Return the horizontal (or vertical) size of the data block's image region
    int Dimension() const;

    // Returns the computed average luminance of the block
    // Compute as the sum of each pixel's luminance value, divided by
    //   the number of pixels in the block
    double AvgLuminance() const;

    // Checks whether other_block's pixel data are the same as this block
    // This is already implemented for you
    bool operator==(const Block &other_block) const {
        bool equal = true;

        for (unsigned int i = 0; i < data.size() && equal; i++) {
            for (unsigned int j = 0; j < data[i].size() && equal; j++) {
                equal = equal &&
                        data[i][j].h == other_block.data[i][j].h &&
                        data[i][j].s == other_block.data[i][j].s &&
                        data[i][j].l == other_block.data[i][j].l &&
                        data[i][j].a == other_block.data[i][j].a;
            }
        }

        return equal;
    }

private:
    // 2D container for pixel data
    // Be aware that a newly declared vector has a size of 0
    // Also be aware that your choice of row-major vs column-major order
    //   affects how you will perform your horizontal or vertical flips.
    vector<vector<HSLAPixel>> data;

};

#endif
