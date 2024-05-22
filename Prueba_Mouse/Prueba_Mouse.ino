#include <Mouse.h>


void setup() {
  // put your setup code here, to run once:
Mouse.begin();
Serial.begin();
}

void loop() {
 String hola = Serial.read();
if (Serial.read() == "a"){
  Mouse.move(0,40,0);
  }
}
