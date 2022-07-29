/*
 *     main.cpp - Project 04-pwm
 *
 *         Usando la lectura de un potenciometro conectado
 *         al conversor analogico a digital, se varia
 *         la luminosidad del LED mediante PWM
 *         (modulacion por ancho de pulso)
 */

#include <Arduino.h>

/*
 *     Definiciones
 */

#if 0

#define STR1(x) #x
#define STR(x) STR1(x)

#endif

/*
 *     otra forma de definir constantes
 *     como si fuesen variables inicializadas
 *     que no cambian
 */

/*
 *  Definitions in platformio.ini
 *  LED1        IOport for led
 *  ANAIN       A/D converter IOport
 *  SERIAL_BAUD Serial port baud rate
 */

const long LOOP_DELAY = 250;

#ifdef ESP32

// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 12;

#endif

/*
 *     Funciones
 */

void
setup()
{
    Serial.begin(SERIAL_BAUD);
#ifdef ESP32
    // configure LED PWM functionalitites
    ledcSetup(ledChannel, freq, resolution);

    // attach the channel to the GPIO to be controlled
    ledcAttachPin(LED1, ledChannel);
#endif
}

void
loop()
{
    int sensorValue; //  Local or automatic variable

    sensorValue = analogRead(ANAIN);
#ifdef ESP32
    Serial.print("ESP32: ");
    ledcWrite(ledChannel, sensorValue);
#else
    Serial.print("ESP8266: ");
    analogWrite(LED1, sensorValue);
#endif
    Serial.println(sensorValue);

    delay(LOOP_DELAY);
}
