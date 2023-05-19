#ifndef RIBBON_TESTER_H_
#define RIBBON_TESTER_H_

static const int inputPinArray[20] =  {30,29,28,27,26,25,24,11,12,10, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};//{0,1,2,3,4,5,6,7,8,9,10,11,12,24,25,26,27,28,29,30};
static const int outputPinArray[20] = {21,20,19,18,17,16,15,14,13,41,40,39,38,37,36,35,34,33,32,31};

#define IS_HIGH(x) ((x) == 1) ? "HIGH" : "LOW"
#define InputPinArraySize (int)(sizeof(inputPinArray)/sizeof(*inputPinArray))
#define REDLED 23
#define GREENLED 22
// set up io and serial communication
void testSetup();

// check for continuity across all wires
int continuityTest();

// check for shorts across adjacent wires
int adjacentShortTest();

#endif //RIBBON_TESTER_H_