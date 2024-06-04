import speech_recognition as sr
import pyttsx3
import serial
import time

# Inicializar el reconocimiento de voz y el motor de texto a voz
recognizer = sr.Recognizer()
engine = pyttsx3.init()

def escuchar_y_hablar():
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
            engine.say(texto) #CAMBIAR ESTO: HAY QUE RECIBIR EL NUEVO TEXTO GENERADO PARA HACER QUE EL PARLANTE EMITA ESO
            engine.runAndWait()

        except sr.UnknownValueError:
            print("No se pudo entender el audio")
        except sr.RequestError as e:
            print(f"No se pudo solicitar los resultados del servicio de reconocimiento de voz; {e}")

if __name__ == "__main__":
    escuchar_y_hablar()