"""
import serial
import time
import speech_recognition as sr
import pyttsx3

# Inicializar el reconocimiento de voz y el motor de texto a voz
recognizer = sr.Recognizer()
engine = pyttsx3.init()

# Configurar el puerto serie para la comunicación con Arduino
puerto_serie = serial.Serial('COM3', 9600)  # Ajusta el nombre del puerto COM según corresponda

# Flag para indicar si la función escuchar_y_hablar() está en ejecución
en_ejecucion = False

def escuchar_y_hablar():
    global en_ejecucion
    en_ejecucion = True
    with sr.Microphone() as source:
        print("Escuchando...")
        # Ajustar el ruido ambiental para mejorar la precisión
        recognizer.adjust_for_ambient_noise(source)
        audio = recognizer.listen(source)

        try:
            # Reconocer el habla usando Google Web Speech API
            texto = recognizer.recognize_google(audio, language='es-ES')
            print(f"Tú dijiste: {texto}")

            # Decir en voz alta el texto reconocido
            engine.say(texto)
            engine.runAndWait()

        except sr.UnknownValueError:
            print("No se pudo entender el audio")
        except sr.RequestError as e:
            print(f"No se pudo solicitar los resultados del servicio de reconocimiento de voz; {e}")

    # Restablecer el estado de la bandera después de que la función haya terminado
    en_ejecucion = False

def esperar_boton():
    global en_ejecucion
    while True:
        if puerto_serie.in_waiting > 0 and not en_ejecucion:
            mensaje = puerto_serie.readline().decode().strip()
            if mensaje == '1':
                escuchar_y_hablar()
                time.sleep(5)  # Espera 5 segundos para evitar la repetición rápida si el botón está presionado
                puerto_serie.flushInput()  # Borra la información del puerto serie

if __name__ == "__main__":
    esperar_boton() """

import serial
import time
import speech_recognition as sr
import pyttsx3

# Inicializar el reconocimiento de voz y el motor de texto a voz
recognizer = sr.Recognizer()
engine = pyttsx3.init()

# Configurar el puerto serie para la comunicación con Arduino
puerto_serie = serial.Serial('COM3', 9600)  # Ajusta el nombre del puerto COM según corresponda

# Flag para indicar si la función escuchar_y_hablar() está en ejecución
en_ejecucion = False
texto_actual = ""
def escuchar_y_hablar(detener_escucha=False):
    global en_ejecucion
    en_ejecucion = True
    with sr.Microphone() as source:
        print("Escuchando...")
        # Ajustar el ruido ambiental para mejorar la precisión
        recognizer.adjust_for_ambient_noise(source)
        if detener_escucha:
            return '2'  # Retorna '2' si se debe detener la escucha
        audio = recognizer.listen(source)

        try:
            # Reconocer el habla usando Google Web Speech API
            if(detener_escucha):
                return "2"                
            texto = recognizer.recognize_google(audio, language='es-ES')
            print(f"Tú dijiste: {texto}")
            texto_actual = texto
            # Decir en voz alta el texto reconocido
            engine.say(texto)
            engine.runAndWait()

        except sr.UnknownValueError:
            print("No se pudo entender el audio")
        except sr.RequestError as e:
            print(f"No se pudo solicitar los resultados del servicio de reconocimiento de voz; {e}")

    
    en_ejecucion = False

def esperar_boton():
    global en_ejecucion
    while True:
        if puerto_serie.in_waiting > 0 and not en_ejecucion:
            mensaje = puerto_serie.readline().decode().strip()
            if mensaje == '1':
                detener_escucha = False
                escuchar_y_hablar(detener_escucha)
                time.sleep(5) 
                puerto_serie.flushInput()  
            elif mensaje == '2':
                detener_escucha = True
                escuchar_y_hablar(detener_escucha)

if __name__ == "__main__":
    esperar_boton() 

