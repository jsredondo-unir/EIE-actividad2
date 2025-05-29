// UNIR - MUIT
// Electrónica e Instrumentación Básicas - Actividad 2
// Autores:
// - Javier Gutiérrez Rodríguez
// - David Viñuela Reyes
// - Javier Sánchez Redondo


#include <LiquidCrystal_I2C.h> // Librería para el manejo de la pantalla LCD
#include <DHT.h> // Libreria para sensor DHT de temperatura y humedad
#include <math.h>

#define DHTPIN 2 // En este pin es donde conectamos el sensor
#define DHTTYPE DHT22 // Usaremos el detector DHT22
#define BUTTON A2 // En este pin es donde conectamos el botón


LiquidCrystal_I2C lcd(0x27, 16, 2); // Creación del objeto de la pantalla LCD
DHT dht(DHTPIN, DHTTYPE); // Creacion del objeto del sensor DHT


// Inicializamos valores
int ValorLDR = 0; 
int brilloLED = 0;
byte cantidad_LEDs = 0;
byte pinesLED[5] = {3, 5, 9, 10, 11}; // En este array contiene los pines conectados a los LEDs
bool status = true;
int menu = 0;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("MONITORIZACION");
  lcd.setCursor(5, 1);
  lcd.print("CLIMA");
  delay(4000);
  lcd.clear();
  dht.begin();
  for (byte i = 0; i < 5; i++) {
    pinMode(pinesLED[i], OUTPUT);
  }
  pinMode(BUTTON, INPUT_PULLUP);
}

void loop() {
  float humidity = dht.readHumidity(); // Leemos el valor de la humedad del sensor DHT
  float temperature = dht.readTemperature(); // Leemos la temperatura en grados celsius

  int ValorLDR = analogRead(A0); // Leemos el valor del sensor de luz
  float voltage = ValorLDR / 1024. * 5; // Convertimos el valor a voltaje
  float resistance = 2000 * voltage / (1 - voltage / 5); // Calculamos la resistencia
  float lux = pow(50 * 1e3 * pow(10, 0.7) / resistance, (1 / 0.7)); // Calculamos el nivel de luz en lux

  // Determinamos los LEDs que encender en función del valor recogido por el LDR

  cantidad_LEDs = calcular_cantidad_leds(ValorLDR);

  brilloLED = map(ValorLDR, 1023, 0, 0, 255); // Ponemos el valor LDR a brillo PWM

  // Encendemos los LEDs según los valores recogidos  
  for (byte i = 0; i < 5; i++) {
    if (i < cantidad_LEDs) {
      analogWrite(pinesLED[i], brilloLED); // Encendemos LEDs ajustando brillo
    } else {
      analogWrite(pinesLED[i], 0); // Apagamos LEDs
    }
  }

  if (status) {
    // Comprobamos si el botón ha sido pulsado
    if (digitalRead(BUTTON) == LOW) {
      lcd.clear();
      while (digitalRead(BUTTON) == LOW); // Esperamos a soltar el botón, para evitar más de un cambio por pulsación
      cambiar_informacion_lcd();
    }
  }

  // Mostramos la información correspondiente al menú actual
  if(status) {
    if (menu == 0) {
      mostrar_temperatura(temperature);
    } else if (menu == 1) {
      mostrar_humedad(humidity);
    } else if (menu == 2) {
      mostrar_lux(lux);
    }
  }

}

// Creamos una funcion para calcular la cantidad de LEDs que hay que encender
int calcular_cantidad_leds(int ValorLDR) {
  if (ValorLDR > 845) {
    cantidad_LEDs = 5;
  } else if (ValorLDR > 675) {
    cantidad_LEDs = 4;
  } else if (ValorLDR > 505) {
    cantidad_LEDs = 3;
  } else if (ValorLDR > 335) {
    cantidad_LEDs = 2;
  } else if (ValorLDR > 165) {
    cantidad_LEDs = 1;
  } else {
    cantidad_LEDs = 0;
  }

  return cantidad_LEDs;
}

// Creamos una funcion que nos muestre la temperatura medida por el sensor por el LCD
void mostrar_temperatura(float temperature) {
  lcd.setCursor(0,0);
  lcd.print("Temperatura: ");
  lcd.setCursor(0,1);
  lcd.print(temperature);
  lcd.print(" *C");
}

// Creamos una funcion que nos muestre la humedad medida por el sensor por el LCD
void mostrar_humedad(float humidity) {
  lcd.setCursor(0,0); // Posicionamiento de cursor
  lcd.print("Humedad: ");
  lcd.setCursor(0,1);
  lcd.print(humidity);
  lcd.print(" %");
}

// Creamos una funcion que nos muestre el nivel de lux medido por el fotoresistor por el LCD
void mostrar_lux(float lux) {
  lcd.setCursor(0,0);
  lcd.print("Nivel de luz: ");
  lcd.setCursor(0,1);
  lcd.print(lux);
  lcd.print(" lux ");
}

// Creamos una funcion que vaya cambiando de menú (usada al pulsar el botón)
void cambiar_informacion_lcd() {
  menu = menu >= 2 ? 0 : menu + 1;
  delay(50);
}