# Actividad 2 - Sistema de control y actuación en función del clima
- **Asignatura**: Electrónica e Instrumentación Básicas
- ***Alumnos***:
  - Javier Gutiérrez Rodríguez
  - David Viñuela Reyes
  - Javier Sánchez Redondo
    
 *Máster Universitario en Ingeniería de Telecomunicación*

 ## Introducción al sistema de control y actuación en función del clima

 ## Diseño del sistema

 ### Hardware
 #### Diagrama de conexiones
 ![Diagrama del circuito](Esquemático.PNG)

 #### Bill of Materials
 [📄 Componentes.csv](BOM.csv)
 ### Software

El software realizado durante esta actividad tiene varias partes. Se ha partido de inicializar todas las librerías, pines y crear objetos utilizando la placa base Arduino Uno. 

![image](https://github.com/user-attachments/assets/5951f1cc-c17e-435b-a7ee-c005dfce4604)

A continuación, en la función setup() hemos inicializado el sistema, dando por el LCD un mensaje introductorio "MONITORIZACIÓN CLIMA". Además, se han inicializado los pines de los LEDs, el sensor DHT, el botón y el servomotor.


![image](https://github.com/user-attachments/assets/2a8b781c-f9f8-4416-8682-05ef09d776a9)

Una vez realizados estos pasos previos al funcionamiento final del sistema, se pasa a crear funciones que se utilizarán dentro de la función loop(). Las funciones son:

- Una función que calcule la cantidad de LEDs a encender en función del valor registrado por el LDR.

  ![image](https://github.com/user-attachments/assets/d00dc5a4-4599-471c-b65f-7e3742b59692)

- Varias funciones que imprimen por pantalla la información recogida por los distintos sensores:

  ![image](https://github.com/user-attachments/assets/c6ab0124-e39e-4844-9735-56c6b3c8f37b)

- Una función para cambiar la información que se muestra por el LCD cuando se pulse el botón rojo:

  ![image](https://github.com/user-attachments/assets/715d565b-02f8-4a1b-894c-47527dfff736)

- Una función que cambia la posición de un servomotor según la temperatura registrada por el sensor DHT22:

  ![image](https://github.com/user-attachments/assets/4a3d87d5-6241-4885-a8f7-6295557be9f4)



## Conclusiones

## Licencia
