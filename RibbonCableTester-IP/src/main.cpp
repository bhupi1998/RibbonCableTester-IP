#include <Arduino.h>
#include "ribbonTester.h"

void setup()
{
  // put your setup code here, to run once:
  testSetup();

}

void loop()
{
  // put your main code here, to run repeatedly:
  int continuityTestResult = continuityTest();
  int adjacentShortTestResult = adjacentShortTest();
  if (continuityTestResult == EXIT_FAILURE || adjacentShortTestResult == EXIT_FAILURE)
  {
    digitalWrite(REDLED, HIGH);
    digitalWrite(GREENLED,LOW);
  }
  else
  {
    digitalWrite(REDLED,LOW);
    digitalWrite(GREENLED, HIGH);
  }
  delay(100);
}
