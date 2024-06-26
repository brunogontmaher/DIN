#include <Keyboard.h>
#include <Mouse.h>

const int ROWS = 2; // Number of rows in the matrix (2 for your case)
const int COLS = 2; // Number of columns in the matrix (2 for your case)

int rowPins[ROWS] = {3, 4}; // Array to hold row pin connections
int colPins[COLS] = {5, 6}; // Array to hold column pin connections
int buttonMatrix[ROWS][COLS]; // 2D array to store button states (0 for not pressed, 1 for pressed)
int prevPressedButton = -1; // Track the previously pressed button

unsigned long lastMoveTime = 0; // Time of the last mouse movement

void setup() {
  for (int i = 0; i < ROWS; i++) {
    pinMode(rowPins[i], INPUT); // Set row pins as input
  }
  for (int i = 0; i < COLS; i++) {
    pinMode(colPins[i], INPUT_PULLUP); // Set column pins as input with pull-up
  }
  Mouse.begin(); // Initialize Mouse library
  Serial.begin(9600); // Initialize serial communication for debugging
}

void loop() {
  scanMatrix(); // Read the state of each button

  // Iterate through the button matrix
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      if (buttonMatrix[i][j] == 0) {
        int buttonIndex = i * COLS + j; // Calculate unique button index
      

      //  if (buttonIndex != prevPressedButton) {  // Check for button press change
        //  prevPressedButton = buttonIndex;

          // Define your custom functionality for each button here:
          switch (buttonIndex) {
            case 0:  // Handle button 0 (e.g., move left-up)
              moveMouse(-50, 0);
              break;
            case 1:  // Handle button 1 (e.g., move up)
              moveMouse(0, -50);
              break;
            case 2:  // Handle button 2 (e.g., move right-up)
              moveMouse(50, 0);
              break;
            case 3:  // Handle button 3 (e.g., left click)
              moveMouse(0, 50);
              break;
            // You can add more cases for other buttons (4, 5, ..., 3)
            default:
              Serial.println("Unhandled button press"); // Optional for debugging
              break;
          }
        }
      }
    }
  }
// }

void scanMatrix() {
  for (int i = 0; i < ROWS; i++) {
    pinMode(rowPins[i], OUTPUT); // Set row pin as output
    digitalWrite(rowPins[i], LOW); // Set row pin to LOW

    for (int j = 0; j < COLS; j++) {
      buttonMatrix[i][j] = digitalRead(colPins[j]); // Read column pin state
    }

    pinMode(rowPins[i], INPUT); // Set row pin back to input
  }
}

void moveMouse(int x, int y) {
  // Add debouncing logic here (optional) to prevent rapid button presses
  // from causing excessive mouse movement.
  if (millis() - lastMoveTime >= 50) {
    Mouse.move(x, y);
    lastMoveTime = millis();
  }
}
