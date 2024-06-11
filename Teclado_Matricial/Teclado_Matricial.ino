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

  delay(200); // Esperar 100 milisegundos
}

char leerTecla() {
  for (int fila = 0; fila < filas; fila++) { // Recorrer las filas
    digitalWrite(pinesFilas[fila], LOW); // Poner la fila en LOW

    for (int columna = 0; columna < columnas; columna++) { // Recorrer las columnas
      bool teclaPresionada = false; // Variable para indicar si se presionó una tecla
      int tiempoPresionada = 0; // Contador de tiempo para debouncing

      while (digitalRead(pinesColumnas[columna]) == LOW) { // Leer la columna
        delay(10); // Retardo para debouncing
        tiempoPresionada++;

        if (tiempoPresionada >= DEBOUNCE_DELAY) { // Tiempo mínimo para considerar la tecla presionada
          teclaPresionada = true;
          break;
        }
      }

      if (teclaPresionada) {
        return teclas[fila][columna]; // Devolver el carácter de la tecla
      }
    }

    digitalWrite(pinesFilas[fila], HIGH); // Poner la fila en HIGH
  }

  return 0; // No se presionó ninguna tecla
}
