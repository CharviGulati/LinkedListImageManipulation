// File:        main.cpp
// Date:        2021-05-20 02:53
// Description: Contains basic tests for GridList
//              Please see images in "output" folder as samples for correct output

#include <iostream>
#include "gridlist.h"


using namespace std;

// Block tests
void TestBlockFlipHorizontal();

void TestBlockFlipVertical();

void TestBlockAvgLuminance();

// GridList tests
void TestCopy();

void TestInsertBack();

void TestFlipHorizontal();

void TestFlipVertical();

void TestPrintASCIIfy();

int main() {
    TestBlockFlipHorizontal();
    TestBlockFlipVertical();
    TestBlockAvgLuminance();

    TestInsertBack();
    TestCopy();
    TestFlipHorizontal();
    TestFlipVertical();
    TestPrintASCIIfy();

#ifdef _WIN32
    system("pause");
#endif
    return 0;
}

void TestBlockFlipHorizontal() {
    cout << "Entered TestBlockFlipHorizontal... " << endl;
    PNG checker8x8;
    checker8x8.readFromFile("images/checker8x8.png");
    Block b;
    b.Build(checker8x8, 0, 0, 8);
    b.FlipHorizontal();

    PNG checker8x8_fh = checker8x8;
    b.Render(checker8x8_fh, 0, 0);
    checker8x8_fh.writeToFile("images/checker8x8_fh.png");
    cout << "Leaving TestBlockFlipHorizontal..." << endl;
}

void TestBlockFlipVertical() {
    cout << "Entered TestBlockFlipVertical... " << endl;
    PNG checker8x8;
    checker8x8.readFromFile("images/checker8x8.png");
    Block b;
    b.Build(checker8x8, 0, 0, 8);
    b.FlipVertical();

    PNG checker8x8_fv = checker8x8;
    b.Render(checker8x8_fv, 0, 0);
    checker8x8_fv.writeToFile("images/checker8x8_fv.png");
    cout << "Leaving TestBlockFlipHorizontal..." << endl;
}

void TestBlockAvgLuminance() {
    cout << "Entered TestBlockAvgLuminance... " << endl;
    PNG checker8x8;
    checker8x8.readFromFile("images/checker8x8.png");
    Block b_red, b_green, b_blue, b_white, b_all;
    b_red.Build(checker8x8, 0, 0, 4);
    b_green.Build(checker8x8, 4, 0, 4);
    b_blue.Build(checker8x8, 0, 4, 4);
    b_white.Build(checker8x8, 4, 4, 4);
    b_all.Build(checker8x8, 0, 0, 8);

    cout << "Red corner 4x4 luminance: " << b_red.AvgLuminance() << endl;
    cout << "Green corner 4x4 luminance: " << b_green.AvgLuminance() << endl;
    cout << "Blue corner 4x4 luminance: " << b_blue.AvgLuminance() << endl;
    cout << "White corner 4x4 luminance: " << b_white.AvgLuminance() << endl;
    cout << "Full image 8x8 luminance: " << b_all.AvgLuminance() << endl;

    cout << "Leaving TestBlockAvgLuminance..." << endl;
}

void TestInsertBack() {
    cout << "Entered TestInsertBack... " << endl;
    PNG checker8x8;
    checker8x8.readFromFile("images/checker8x8.png");
    Block b_red, b_green, b_blue, b_white, b_all;
    b_red.Build(checker8x8, 0, 0, 4);
    b_green.Build(checker8x8, 4, 0, 4);
    b_blue.Build(checker8x8, 0, 4, 4);
    b_white.Build(checker8x8, 4, 4, 4);

    GridList gl; // note that this will not have any dimx or dimy set

    // insert the first block and test
    gl.InsertBack(b_red);
    if (gl.GetNorthWest() == NULL || gl.GetSouthEast() == NULL)
        cout << "Corner pointers null after insertion of first Block." << endl;
    else if (gl.GetNorthWest() != gl.GetSouthEast())
        cout << "Corner pointers not equal after insertion of first Block." << endl;

    // insert the second block and test
    gl.InsertBack(b_green);
    if (gl.GetNorthWest() == gl.GetSouthEast())
        cout << "Corner pointers are equal after insertion of second Block." << endl;

    cout << "Leaving TestInsertBack... " << endl;
}

void TestCopy() {
    cout << "Entered TestCopy... " << endl;
    PNG checker8x8;
    checker8x8.readFromFile("images/checker8x8.png");
    GridList checkerlist(checker8x8, 4);

    GridNode *origNW = checkerlist.GetNorthWest();
    GridNode *origNE = origNW->next;
    GridNode *origSW = origNE->next;
    GridNode *origSE = origSW->next;

    GridList copylist(checkerlist);

    if (copylist.Length() != 4)
        cout << "Copied list length is incorrect." << endl;

    if (copylist.GetNorthWest() == copylist.GetSouthEast())
        cout << "Copied list NW and SE nodes are physically the same." << endl;

    if (copylist.GetNorthWest() == origNW || copylist.GetSouthEast() == origSE)
        cout << "Copied list nodes are the same physical nodes as original." << endl;

    cout << "Leaving TestCopy... " << endl;
}

void TestFlipHorizontal() {
    cout << "Entered TestFlipHorizontal... " << endl;
    PNG asl2;
    asl2.readFromFile("images/asl2-320x224.png");
    GridList origlist(asl2, 16); // dimensions 20 x 14 blocks

    GridNode *origNW = origlist.GetNorthWest();
    GridNode *origNE = origNW;
    for (int i = 0; i < 19; i++)
        origNE = origNE->next;
    GridNode *origSW = origNW;
    for (int i = 0; i < 260; i++)
        origSW = origSW->next;
    GridNode *origSE = origlist.GetSouthEast();

    GridList copylist(origlist);

    Block origNEBlock;
    origNEBlock.Build(asl2, 0, 304, 16);
    Block origSWBlock;
    origSWBlock.Build(asl2, 208, 0, 16);

    origlist.FlipHorizontal();

    GridNode *hflipNW = origlist.GetNorthWest();
    GridNode *hflipSE = origlist.GetSouthEast();

    if (hflipNW != origNE || hflipSE != origSW)
        cout << "Flipped corners not matching to original corresponding corners." << endl;
    if (copylist.GetNorthWest()->data == origNEBlock || copylist.GetSouthEast()->data == origSWBlock)
        cout << "Pixel data in blocks not flipped";

    PNG hflipoutput = origlist.Render();
    hflipoutput.writeToFile("images/asl2-320x224-fh.png");

    cout << "Leaving TestFlipHorizontal... " << endl;
}

void TestFlipVertical() {
    cout << "Entered TestFlipVertical... " << endl;
    PNG rt;
    rt.readFromFile("images/rt-600x420.png");
    GridList origlist(rt, 15); // dimensions 40 x 28 blocks

    GridNode *origNW = origlist.GetNorthWest();
    GridNode *origNE = origNW;
    for (int i = 0; i < 39; i++)
        origNE = origNE->next;
    GridNode *origSW = origNW;
    for (int i = 0; i < 1080; i++)
        origSW = origSW->next;
    GridNode *origSE = origlist.GetSouthEast();

    GridList copylist(origlist);

    Block origNEBlock;
    origNEBlock.Build(rt, 0, 585, 15);
    Block origSWBlock;
    origSWBlock.Build(rt, 405, 0, 15);

    origlist.FlipVertical();

    GridNode *vflipNW = origlist.GetNorthWest();
    GridNode *vflipSE = origlist.GetSouthEast();

    if (vflipNW != origSW || vflipSE != origNE)
        cout << "Flipped corners not matching to original corresponding corners." << endl;
    if (origlist.GetNorthWest()->data == origNEBlock || origlist.GetSouthEast()->data == origSWBlock)
        cout << "Pixel data in blocks not flipped";

    PNG vflipoutput = origlist.Render();
    vflipoutput.writeToFile("images/rt-600x420-fv.png");

    cout << "Leaving TestFlipVertical... " << endl;
}

void TestPrintASCIIfy() {
    cout << "Entered TestPrintASCIIfy... \n" << endl;
    PNG cmkm;
    cmkm.readFromFile("images/cmkm-84x126.png");
    GridList cmkmlist(cmkm, 3); // dimensions 28 x 43 blocks

    string cmkm_s = cmkmlist.PrintASCIIfy();

    cout << cmkm_s << "\n" << endl;

    PNG pkm;
    pkm.readFromFile("images/pkm-120x144.png");
    GridList pkmlist(pkm, 3); // dimensions 40 x 48 blocks

    string pkm_s = pkmlist.PrintASCIIfy();

    cout << pkm_s << "\nLeaving TestPrintASCIIfy... " << endl;
}