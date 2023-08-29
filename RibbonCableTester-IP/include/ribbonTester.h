#ifndef RIBBON_TESTER_H_
#define RIBBON_TESTER_H_

static const int inputPinArray[20] =  {33,34,35,36,37,38,39,40,41,14,15,16,17,18,19,20,21,22,23,0};
static const int outputPinArray[20] = {1,2,3,4,5,6,7,8,9,10,11,24,25,26,27,28,29,30,31,32};//{32,31,30,29,28,27,26,25,24,11,10,9,8,7,6,5,4,3,2,1};

#define IS_HIGH(x) ((x) == 1) ? "HIGH" : "LOW"
#define InputPinArraySize (int)(sizeof(inputPinArray)/sizeof(*inputPinArray))
#define REDLED 13
#define GREENLED 12
// set up io and serial communication
void testSetup();

// check for continuity across all wires
int continuityTest();

// check for shorts across adjacent wires
int adjacentShortTest();

#endif //RIBBON_TESTER_H_