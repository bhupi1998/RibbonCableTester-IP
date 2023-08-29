#include <Arduino.h>
#include "ribbonTester.h"

// set up io and serial communication
void testSetup()
{
  for (int i = 0; i < (int)(sizeof(inputPinArray) / sizeof(*inputPinArray)); i++)
  {
    pinMode(inputPinArray[i], INPUT_PULLDOWN);
    pinMode(outputPinArray[i], OUTPUT);
  }

  // led setup
  pinMode(REDLED, OUTPUT);
  pinMode(GREENLED, OUTPUT);
}

// check for continuity across all wires
int continuityTest()
{
  int *failedPinArray = (int *)calloc(InputPinArraySize, sizeof(int));
  failedPinArray[0] = 99999;
  for (int i = 0; i < InputPinArraySize; i++)
  {
    digitalWrite(outputPinArray[i], HIGH);
  }
  int failedPinArrayIndex = 0;
  for (int i = 0; i < InputPinArraySize; i++)
  {
    int pinState = digitalRead(inputPinArray[i]);
    if (pinState == 0) // means in input is low even when all outputs are set to high, indicating a short
    {
    return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}

// check for shorts across adjacent wires
// returns 1 if failed
int adjacentShortTest()
{
  int numHighInputs= 0; // there should only be one input high at the time
  // resetting all inputs
  for (int i = 0; i < InputPinArraySize; i++)
  {
    digitalWrite(outputPinArray[i], LOW);
  }

  for (int i = 0; i < InputPinArraySize; i++)
  {
    digitalWrite(outputPinArray[i], HIGH);
    for (int l = 0; l < InputPinArraySize; l++)
    {
      int pinState = digitalRead(inputPinArray[l]);
      if (digitalRead(inputPinArray[l]) == HIGH)
      {
        numHighInputs++;
        if(numHighInputs>1){
          return EXIT_FAILURE;
        }
      }
    }
    digitalWrite(outputPinArray[i], LOW);
    numHighInputs = 0; //resetting for next pin
  }
  return EXIT_SUCCESS;
}