// File:        gridlist.cpp
// Date:        2021-05-20 02:56
// Description: Contains partial implementation of GridList class
//              CPSC 221 2021S PA1
//              Function bodies to be completed by yourselves
//
// ADD YOUR FUNCTION IMPLEMENTATIONS IN THIS FILE
//
#include "gridlist.h"


// Creates a PNG of appropriate pixel dimensions according to the GridList's structure
//   and colours each pixel according the each GridNode's Block data.
// The fully coloured PNG is returned.
PNG GridList::Render() const {
    PNG image = PNG(2,3);

    GridNode *currentNode = northwest;
    while(currentNode != nullptr) {
        currentNode = currentNode->next;
    }
    return image;
}

// Allocates a new GridNode containing bdata and
//   attaches it to end of this list.
// Be careful of the special case of inserting into an empty list.
void GridList::InsertBack(const Block &bdata) {
    if (northwest == nullptr) {
        // empty list case
        northwest = new GridNode;
        northwest->data = bdata;
        northwest->next = nullptr;
        southeast = northwest;
    }
    else {
        GridNode *newNode = new GridNode;
        newNode->data = bdata;
        newNode->next = nullptr;
        southeast->next = newNode;
        southeast = newNode;
    }
}

// Rearranges the GridNodes in the list (and the pixel data in each GridNode) so that
//   the complete image data has been flipped/mirrored horizontally (across a vertical axis)
// e.g. for the following list:
// NW -> 1 -> 2 -> 3 -> 4 ->5  5 2 3 4 1    5 4 3 2 1                         1 2 3 4 5 6 7 ->
//    -> 5 -> 6 -> 7 -> 8                                                     8 9 1 2 3 5 6
//    -> 9 ->10 ->11 ->12 <- SE
// The list after flipping horizontally will be:
// NW -> 4 -> 3 -> 2 -> 1
//    -> 8 -> 7 -> 6 -> 5
//    ->12 ->11 ->10 -> 9 <- SE,
//   where the pixel data in each block has also been flipped horizontally
// THIS MUST BE ACHIEVED USING POINTER REASSIGNMENTS.
// DO NOT ALLOCATE OR DELETE ANY NODES IN THIS FUNCTION.
void GridList::FlipHorizontal() {
    for (int x = 0; x < dimx; ++x) {
        //for (int y = 0; y < dimy; ++y) {
            GridNode* current = northwest;
            GridNode* previousNode = NULL;
            GridNode* nextNode = northwest;

                while (current != NULL) {
                    nextNode = nextNode->next;
                    current->next = previousNode;
                    previousNode = current;
                    current = nextNode;

                    current->data.FlipHorizontal();
                    previousNode->data.FlipHorizontal();
                }
                //x = dimx + 1;
            northwest = previousNode;
        //}
    }
}

// Rearranges the GridNodes in the list (and the pixel data in each GridNode) so that
//   the complete image data has been flipped/mirrored vertically (across a horizontal axis)
// e.g. for the following list:
// NW -> 1 -> 2 -> 3 -> 4
//    -> 5 -> 6 -> 7 -> 8
//    -> 9 ->10 ->11 ->12 <- SE
// The list after flipping horizontally will be:
// NW -> 9 ->10 ->11 ->12
//    -> 5 -> 6 -> 7 -> 8
//    -> 1 -> 2 -> 3 -> 4 <- SE,
//   where the pixel data in each block has also been flipped vertically
// THIS MUST BE ACHIEVED USING POINTER REASSIGNMENTS.
// DO NOT ALLOCATE OR DELETE ANY NODES IN THIS FUNCTION.
void GridList::FlipVertical() {
    // enter your code here

}

// Uses the average luminance of each GridNode's block, and sends an
//   ASCII character to a return string.
// The characters in the string, if printed, must match the structural
//   dimensions of the GridList (i.e. insert line breaks at appropriate intervals).
// Use the Lum2ASCII private function for mapping luminance levels to
//   ASCII characters, and the += operator to append a character to
//   an existing string.
string GridList::PrintASCIIfy() const {
    // enter your code here
    return "";
}

// Deallocates any dynamic memory associated with this list
//   and re-initializes this list to an empty state
void GridList::Clear() {
    // enter your code here

}

// Allocates new nodes into this list as copies of all nodes from otherlist
void GridList::Copy(const GridList &otherlist) {
    // enter your code here
    // Copy must use new, so at some point you either forgot to connect a node, or the destructor is forgets to delete a node

}

// IMPLEMENT ANY PRIVATE FUNCTIONS YOU HAVE ADDED BELOW
//
//
