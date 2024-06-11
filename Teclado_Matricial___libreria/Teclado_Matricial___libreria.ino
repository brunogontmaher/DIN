const int filas = 4; // Número de filas del teclado
const int columnas = 4; // Número de columnas del teclado

const int pinesFilas[filas] = {9, 8, 7, 6}; // Pines conectados a las filas
const int pinesColumnas[columnas] = {5, 4, 3, 2}; // Pines conectados a las columnas

const int DEBOUNCE_DELAY = 20; // Tiempo mínimo de debouncing en milisegundos

char teclas[filas][columnas] = { // Matriz para almacenar los caracteres de las teclas
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

void setup() {
  Serial.begin(9600); // Inicializar la comunicación serial

  // Configurar las filas como salidas
  for (int i = 0; i < filas; i++) {
    pinMode(pinesFilas[i], OUTPUT);
  }

  // Configurar las columnas como entradas con pullup
  for (int i = 0; i < columnas; i++) {
    pinMode(pinesColumnas[i], INPUT_PULLUP);
  }
}

void loop() {
  char tecla = leerTecla(); // Leer la tecla presionada

  if (tecla) {
    Serial.print("Tecla presionada: ");
    Serial.println(tecla);
  }

  delay(100); // Esperar 100 milisegundos
}

char leerTecla() {
  // Variables para almacenar la tecla y el estado de debouncing
  char teclaPresionada = 0;
  bool teclaDebounce = false;
  int tiempoPresionada = 0;

  // Recorrer las filas del teclado
  for (int fila = 0; fila < filas; fila++) {
    digitalWrite(pinesFilas[fila], LOW); // Poner la fila en LOW

    // Recorrer las columnas del teclado
    for (int columna = 0; columna < columnas; columna++) {
      // Leer el estado de la columna actual
      if (digitalRead(pinesColumnas[columna]) == LOW) {
        teclaPresionada = teclas[fila][columna]; // Almacenar el carácter de la tecla
        tiempoPresionada = 0; // Reiniciar el contador de debouncing
        teclaDebounce = true; // Marcar que se presionó una tecla
      }
    }

    // Implementar debouncing
    if (teclaDebounce) {
      while (digitalRead(pinesColumnas[columnas]) == LOW) { // Esperar mientras la tecla esté presionada
        delay(10); // Retardo para debouncing
        tiempoPresionada++;

        if (tiempoPresionada >= DEBOUNCE_DELAY) { // Tiempo mínimo de debouncing
          break; // Salir del bucle si se alcanza el tiempo de debouncing
        }
      }

      teclaDebounce = false; // Marcar que terminó el debouncing
    }

    digitalWrite(pinesFilas[fila], HIGH); // Poner la fila en HIGH
  }

  // Devolver la tecla presionada o 0 si no se presionó ninguna
  return teclaPresionada;
}
