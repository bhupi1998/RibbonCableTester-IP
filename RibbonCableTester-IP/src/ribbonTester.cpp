#include <Arduino.h>
#include "ribbonTester.h"

// set up io and serial communication
void testSetup()
{
  Serial.begin(9600);
  delay(500); // waiting for serial to initialize
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
    Serial.print("Pin: ");
    Serial.print(inputPinArray[i]);
    Serial.print(" State: ");
    int pinState = digitalRead(inputPinArray[i]);
    Serial.println(IS_HIGH(pinState));
    if (pinState == 0)
    {
      failedPinArray[failedPinArrayIndex] = inputPinArray[i];
      failedPinArrayIndex++;
    }
  }
  if (failedPinArray[0] != 99999)
  {
    Serial.print("No continuity on pins:");
    for (int i = 0; i < (int)(sizeof(failedPinArray) / sizeof(*failedPinArray)); i++)
    {
      Serial.println(failedPinArray[i]);
    }
    free(failedPinArray);
    return EXIT_FAILURE;
  }
  else
  {
    Serial.println("Continuite Test Passed");
  }
  free(failedPinArray);
  return EXIT_SUCCESS;
}

// check for shorts across adjacent wires
// returns 1 if failed
int adjacentShortTest()
{
  int *failedPinArray = (int *)calloc(InputPinArraySize, sizeof(int));
  int failedPinArrayIndex = 0;
  for (int i = 0; i < InputPinArraySize; i++)
  {
    digitalWrite(outputPinArray[i], LOW);
  }

  for (int i = 0; i < InputPinArraySize; i++)
  {
    digitalWrite(outputPinArray[i], HIGH);
    Serial.print("output pin: ");
    Serial.println(outputPinArray[i]);
    Serial.print("Testing input pin: ");
    Serial.println(inputPinArray[i]);
    for (int l = 0; l < InputPinArraySize; l++)
    {
      Serial.print("Pin: ");
      Serial.print(inputPinArray[l]);
      Serial.print(" State: ");
      int pinState = digitalRead(inputPinArray[l]);
      Serial.println(IS_HIGH(pinState));
      if (digitalRead(inputPinArray[l]) == HIGH && l != i)
      {
        failedPinArray[failedPinArrayIndex] = inputPinArray[l];
        failedPinArrayIndex++;
      }
    }
    digitalWrite(outputPinArray[i], LOW);
    Serial.print("\n");
  }
  if (failedPinArray[0] != 0)
  {
    Serial.print("Shorts on pins:");
    for (int i = 0; i < InputPinArraySize; i++)
    {
      Serial.println(failedPinArray[i]);
    }
    free(failedPinArray);
    return EXIT_FAILURE;
  }
  else
  {
    Serial.print("Short Test Passed");
  }
  free(failedPinArray);
  return EXIT_SUCCESS;
}