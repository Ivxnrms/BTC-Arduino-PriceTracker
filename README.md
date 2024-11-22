# Tracker del precio del BTC a tiempo real con ESP8266 
Este programa es un tracker del precio del BTC, el cual se muestra a tiempo real gracias al ESP8266(wifi) y un Adrafruit_SSD1306. Usando el módulo WiFi se convierte en cliente, accediendo a la API de CoinDesk mediante HTTP, y a su vez leyendo los datos de la API, para mostrar en pantalla en precio del Bitcoin en USD cada segundo 💲

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

*LIBRERIAS*

- Adafruit_SSD1306 (https://github.com/adafruit/Adafruit_SSD1306)
- Wire.h (Viene incluida en Arduino IDE)
- ESP8266 Core (https://github.com/esp8266/Arduino/tree/master)
- ArduinoJson (https://github.com/arduino-libraries/Arduino_JSON)

  ⚠ Nota: Siga los pasos de instalación de cada librería, y procure cumplir los requisitos de cada una.

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

PASOS A SEGUIR:

- Seleccionar la placa "Generic ESP8266 Module"
- Seleccionar el puerto serie
- Cambiar los parámetros en las variables de las líneas 14 y 15
- Cambiar los parámetros en la pestaña "secrets.h"

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

CABLEADO

![wire-diagram](https://github.com/Ivxn-Rms/Precio-de-BTC-con-ESP8266-a-tiempo-real/assets/74296930/f5933080-764a-4733-8b97-98c53725967c)

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

RESULTADO FINAL

![image](https://github.com/Ivxn37/Precio-del-BTC-con-ESP8266-a-tiempo-real/assets/74296930/aa1000d4-6751-48d8-9ba8-4e7c019293a5)

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
