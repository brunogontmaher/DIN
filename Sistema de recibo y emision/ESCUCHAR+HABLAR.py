import speech_recognition as sr
import pyttsx3

# Inicializar el reconocimiento de voz y el motor de texto a voz
recognizer = sr.Recognizer()
engine = pyttsx3.init()

def datos(datos):
    texto1 = ["Hola como estas"]
    return texto1

def escuchar_y_hablar():
    with sr.Microphone() as source:
        print("Escuchando...")
        # Ajustar el ruido ambiental para mejorar la precisión
        recognizer.adjust_for_ambient_noise(source)
        audio = recognizer.listen(source)

        try:
            # Reconocer el habla usando Google Web Speech API
            texto = recognizer.recognize_google(audio, language='es-ES')
            print(f"Tú dijiste: {datos(1)}")

            # Decir en voz alta el texto reconocido
            engine.say() #CAMBIAR ESTO: HAY QUE RECIBIR EL NUEVO TEXTO GENERADO PARA HACER QUE EL PARLANTE EMITA ESO
            engine.runAndWait()

        except sr.UnknownValueError:
            print("No se pudo entender el audio")
        except sr.RequestError as e:
            print(f"No se pudo solicitar los resultados del servicio de reconocimiento de voz; {e}")

if __name__ == "__main__":
    escuchar_y_hablar()