#include <Keyboard.h>
#include <Mouse.h>

const int F = 3; // (filas)
const int C = 3 // (columnas)

int filas[] = {3, 4, 5}; 
int columnas[] = {6, 7, 8}; 
int matriz[F][C]; 
int prevPressedButton = -1; // Trackear el boton anteriormente presionado

unsigned long tiempo = 0;

void setup() {
  for (int i = 0; i < F; i++) {
    pinMode(filas[i], INPUT); 
  }
  for (int i = 0; i < C; i++) {
    pinMode(columnas[i], INPUT_PULLUP); // Configure column pins as input with pull-up
  }
  Mouse.begin(); // Initialize Mouse library
  Serial.begin(9600); // Initialize serial communication (for debugging)
}

void leerMatriz() {
  for (int i = 0; i < F; i++) {
    pinMode(filas[i], OUTPUT); )
    digitalWrite(filas[i], LOW);

    
    for (int j = 0; j < C; j++) {
      pinMode(columnas[j], INPUT_PULLUP); 
      matriz[i][j] = digitalRead(columnas[j]); 
      pinMode(columnas[j], INPUT); 
    }
    pinMode(filas[i], INPUT); 
  }
}


void Funciones_Botones (int row, int col) {
  int buttonIndex = row * C + col; // indice del boton
  
  if (buttonIndex != prevPressedButton) { 
    prevPressedButton = buttonIndex; 

    int movementX = 0; 
    int movementY = 0;

 
    switch (buttonIndex) {
      case 0: // Arriba izquierda)
        movementX = -50; 
        movementY = -50; 
        break;
      case 1: // Arriba
        movementY = -50; 
        break;
      case 2: // Arriba derecha
        movementX = 50; 
        movementY = -50; 
        break;
      case 3: // Izquierda
        movementX = -50;
        break;
      case 4: // Nada
        break;
      case 5: // Derecha
        movementX = 50; 
        break;
      case 6: // Izquierda abajo
        movementX = -50;
        movementY = 50; 
        break;
      case 7: // Abajo
        movementY = 50; // Mover abajo
        break;
      case 8: // Derecha Abajo
        movementX = 50; 
        movementY = 50; 
        break;
    }

if (movementX != 0 || movementY != 0) {
 // millis para no cortar la comunicacion entre arduino y computadora
  if (millis() - tiempo >= 50) {
    Mouse.move(movementX, movementY); // Mover el mouse
    lastMoveTime = millis();
  }
}
  }
}

void loop() {
  leerMatriz(); // Leer la matriz de botones

// Iterar en la matriz para apretar los botones de direccion del mouse
  for (int i = 0; i < F; i++) {
    for (int j = 0; j < C; j++) {
      if (matriz[i][j] == 1) {
        Funciones_Botones(i, j); 
      }
    }
  }

  // Print matrix for debugging (uncomment if needed)
  // Serial.println();
  // for (int i = 0; i < F; i++) {
