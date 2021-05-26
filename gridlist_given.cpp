// File:        gridlist_given.cpp
// Date:        2021-05-20 02:53
// Description: Contains partial implementation of GridList class
//              CPSC 221 2021S PA1
//
// DO NOT MODIFY THE CONTENTS OF THIS FILE
//

#include "gridlist.h"

// Default constructor
// Assigns appropriate default values to member attributes
//   to indicate an empty list
GridList::GridList() {
    northwest = NULL;
    southeast = NULL;
    dimx = 0;
    dimy = 0;
}

// Parameterized constructor
// PARAMETERS: img - input PNG
//             blockdim - desired length of a block's side (in pixels)
// PRE:  img's horizontal and vertical resolutions are both evenly divisible by blockdim
// POST: if either horizontal or vertical resolutions are not evenly divisible by blockdim,
//         then assign default values to member attributes
//       otherwise assign the horizontal and vertical block dimensions, and populate the list
//         using the input image data.
//         Requires correct implementation of Block::Build, and GridList::InsertBack
GridList::GridList(PNG &img, int blockdim) {
    // check if dimensions are evenly divisible by blockdim
    if (!(img.width() % blockdim == 0 && img.height() % blockdim == 0)) {
        northwest = NULL;
        southeast = NULL;
        dimx = 0;
        dimy = 0;
    } else {
        // create GridList from image data
        dimx = img.width() / blockdim;
        dimy = img.height() / blockdim;
        northwest = NULL;
        southeast = NULL;
        // loop variables determine the (x,y) position of the block within the image
        for (int block_y = 0; block_y < dimy; block_y++) {
            for (int block_x = 0; block_x < dimx; block_x++) {
                // create a block from image data and add to the back of the list
                Block b;
                b.Build(img, block_y * blockdim, block_x * blockdim, blockdim);
                InsertBack(b);
            }
        }
    }
}

// Copy constructor
// Creates a new list whose contents are duplicated from otherlist
// Requires correct implementation of GridList::Copy
GridList::GridList(const GridList &otherlist) {
    Copy(otherlist);
}

// Overloaded assignment operator
// If an existing list is being reassigned, ensure that any existing
//   dynamic memory is released, before copying the data from rhs
// Requires correct implementations of GridList::Clear and GridList::Copy
GridList &GridList::operator=(const GridList &rhs) {
    // if this object and the argument do not reside at the same physical memory address
    //   (they are different objects)
    if (this != &rhs) {
        Clear();
        Copy(rhs);
    }
    return *this;
}

// Destructor
// Releases any dynamic memory associated with this list.
// Is called automatically when a GridList object goes out of scope
// Requires correct implementation of GridList::Clear
GridList::~GridList() {
    Clear();
}

// Returns the number of GridNode elements in this list
// An empty list contains 0 elements
int GridList::Length() const {
    return dimx * dimy;
}

// Returns TRUE if the list is empty
// The northwest (and southeast) member attributes are NULL for an empty list
bool GridList::IsEmpty() const {
    return (northwest == NULL);
}

// GridNode default constructor
GridNode::GridNode() : data(Block()), next(NULL) {
    // empty
}

// GridNode parameterized constructor
GridNode::GridNode(const Block &bdata) : data(bdata), next(NULL) {
    // empty
}

// Maps the provided HSLA luminance value into an ASCII character
// PRE:  lum is a value within the valid luminance range of the HSLA specification
char GridList::Lum2ASCII(double lum) const {
    // ramp has 142 levels
    const int ramp_length = 142;
    char ramp_neg[] = "MMMMMMM@@@@@@@WWWWWWWWWBBBBBBBB000000008888888ZZZZZZZZZZaaaaaaa2222222SSSSSSSXXXXXXXXXXX7777777rrrrrrr;;;;;;;;iiiiiiiii:::::::,,,,,,,.........       ";
    char ramp[] = "       .........,,,,,,,:::::::iiiiiiiii;;;;;;;;rrrrrrr7777777XXXXXXXXXXXSSSSSSS2222222aaaaaaaZZZZZZZZZZ888888800000000BBBBBBBBWWWWWWWWW@@@@@@@MMMMMMM";

    // first clamp the luminance value to the valid range
    if (lum < 0.0)
        lum = 0.0;
    else if (lum > 1.0)
        lum = 1.0;

    // Take the luminance value ranged [0.0, 1.0] and apply the linear map to the integer range [0,141]
    int ramp_index = (int) (lum * (ramp_length - 1));

    return ramp[ramp_index];
}

// returns the northwest pointer
// THIS IS USED FOR TESTING YOUR SUBMITTED CODE ONLY
GridNode *GridList::GetNorthWest() {
    return northwest;
}

// returns the southeast pointer
// THIS IS USED FOR TESTING YOUR SUBMITTED CODE ONLY
GridNode *GridList::GetSouthEast() {
    return southeast;
}