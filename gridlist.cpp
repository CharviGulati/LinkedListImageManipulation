// File:        gridlist.cpp
// Date:        2021-05-20 02:56
// Description: Contains partial implementation of GridList class
//              CPSC 221 2021S PA1
//              Function bodies to be completed by yourselves
//
// ADD YOUR FUNCTION IMPLEMENTATIONS IN THIS FILE
//
#include <stack>
#include "gridlist.h"



// Creates a PNG of appropriate pixel dimensions according to the GridList's structure
//   and colours each pixel according the each GridNode's Block data.
// The fully coloured PNG is returned.
PNG GridList::Render() const {
    GridNode *currentNode = northwest;
    int gridNodesPlaced = 0;
    int blockDimension = northwest->data.Dimension();

    int width = dimx * blockDimension; // #blocks * size of each block
    int height = dimy * blockDimension;
    PNG image(width, height);

    while (currentNode != nullptr) {
        int xCoordinate = (gridNodesPlaced % dimx) * blockDimension;
        int yCoordinate = (gridNodesPlaced / dimx) * blockDimension;
        currentNode->data.Render(image, yCoordinate, xCoordinate);
        currentNode = currentNode->next; // traverse to next node, now that we've rendered this one
        gridNodesPlaced++;
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
    } else {
        GridNode *newNode = new GridNode;
        newNode->data = bdata;
        newNode->next = nullptr;
        southeast->next = newNode;
        southeast = newNode;
    }
}


// I had trouble finding how to do this, so I ended up reading many articles
// and adapting different sets of code blocks as needed.
GridNode *reverseSegmentOfList(GridNode *head, int start, int end) {
    GridNode *current = head;
    GridNode *last = current;
    GridNode *previous = nullptr;
    GridNode *first = nullptr;
    GridNode *temp = nullptr;

    int count = 0;

    while (current != nullptr && count < end) {
        count++;
        if (count >= start) {
            temp = current->next;
            current->next = previous;
            previous = current;
            current = temp;
            continue;
        }
        first = current;
        current = current->next;
        last = current;
    }

    if (start == 1) {
        head = previous;
    } else {
        first->next = previous;
    }
    last->next = current;
    return head;
}


// Rearranges the GridNodes in the list (and the pixel data in each GridNode) so that
//   the complete image data has been flipped/mirrored horizontally (across a vertical axis)
// e.g. for the following list:
// NW -> 1 -> 2 -> 3 -> 4
//    -> 5 -> 6 -> 7 -> 8
//    -> 9 ->10 ->11 ->12 <- SE
// The list after flipping horizontally will be:
// NW -> 4 -> 3 -> 2 -> 1
//    -> 8 -> 7 -> 6 -> 5
//    ->12 ->11 ->10 -> 9 <- SE,
//   where the pixel data in each block has also been flipped horizontally
// THIS MUST BE ACHIEVED USING POINTER REASSIGNMENTS.
// DO NOT ALLOCATE OR DELETE ANY NODES IN THIS FUNCTION.
void GridList::FlipHorizontal() {
    // First, flip each node's data
    int startCount = 1;
    int count = 0;
    int endCount = dimx;

    while (count < dimy) {
        northwest = reverseSegmentOfList(northwest, startCount, endCount);
        startCount += dimx;
        endCount += dimx;
        count++;
    }

    GridNode *headNode = northwest;
    while (headNode != nullptr) {
        headNode->data.FlipHorizontal();
        headNode = headNode->next;
    }
}

//// For debugging
//int llsize(GridNode *head) {
//    int size = 0;
//    GridNode *node = head;
//    while (node != nullptr) {
//        node = node->next;
//        size++;
//    }
//    return size;
//}


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

    vector<GridNode *> rowOfGridNodes;
    stack<vector<GridNode *>> newRows;
    GridNode *current = northwest;

    for (int row = 0; row < dimx * dimy; row++) {
        rowOfGridNodes.push_back(current);
        current = current->next;
        if (rowOfGridNodes.size() == (unsigned long) dimx) {
            newRows.push(rowOfGridNodes);
            rowOfGridNodes.clear();
        }
    }

    vector<vector<GridNode *>> vectors;
    while (!newRows.empty()) {
        vectors.push_back(newRows.top());
        newRows.pop();
    }

    for (int i = 0; i < dimy; i++) { // rows
        for (int j = 0; j < dimx; j++) { // cols
            if (j == 0 && i != 0) {
                vectors[i - 1][dimx - 1]->next = vectors[i][j];
            }
        }
    }

    vectors[dimy - 1][dimx - 1]->next = nullptr;
    northwest = vectors[0][0];
    southeast = vectors[dimy - 1][dimx - 1];

    GridNode *headNode = northwest;
    while (headNode != nullptr) {
        headNode->data.FlipVertical();
        headNode = headNode->next;
    }
}

// Uses the average luminance of each GridNode's block, and sends an
//   ASCII character to a return string.
// The characters in the string, if printed, must match the structural
//   dimensions of the GridList (i.e. insert line breaks at appropriate intervals).
// Use the Lum2ASCII private function for mapping luminance levels to
//   ASCII characters, and the += operator to append a character to
//   an existing string.
string GridList::PrintASCIIfy() const {
    GridNode *current = northwest;
    string ASCIIString = "";

    while (current != nullptr) {
        for (int i = 0; i < dimx; i++) {
            ASCIIString += Lum2ASCII(current->data.AvgLuminance());
            current = current->next;
        }
        ASCIIString += "\n";
    }
    return ASCIIString;
}

// Deallocates any dynamic memory associated with this list
//   and re-initializes this list to an empty state
void GridList::Clear() {
    GridNode *current = northwest;

    northwest = nullptr;
    southeast = nullptr;

    while (current != nullptr) {
        GridNode *temp = current;
        current = current->next;
        delete temp;
        temp = nullptr;
    }
}


// Allocates new nodes into this list as copies of all nodes from otherlist
void GridList::Copy(const GridList &otherlist) {
    if (otherlist.northwest == nullptr) {
        northwest = nullptr;
    } else {
        northwest = new GridNode(otherlist.northwest->data);
        GridNode *current = northwest;
        GridNode *newHead = otherlist.northwest;
        GridNode *currOtherList = newHead;

        while (currOtherList->next != nullptr) {
            current->next = new GridNode(currOtherList->next->data);
            currOtherList = currOtherList->next;
            current = current->next;
        }
        dimx = otherlist.dimx;
        dimy = otherlist.dimy;
    }
}

// IMPLEMENT ANY PRIVATE FUNCTIONS YOU HAVE ADDED BELOW
//
//
