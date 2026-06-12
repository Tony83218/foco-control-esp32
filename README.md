# Control de LED con Sensor de Movimiento - ESP32-WROOM-32

## Descripción
Esta aplicación permite controlar un LED mediante una app móvil creada en MIT App Inventor y un sensor de movimiento (PIR), utilizando un microcontrolador ESP32-WROOM-32 para gestionar el encendido automático y manual del LED.

## Características
- ✅ Control manual del LED desde la app móvil
- ✅ Activación automática por sensor de movimiento (PIR)
- ✅ Visualización de estado en tiempo real
- ✅ Interfaz web integrada en el ESP32
- ✅ Conexión WiFi

## Componentes necesarios

### Hardware
- **ESP32-WROOM-32**: Microcontrolador principal
- **LED RGB o LED blanco**: Para indicación luminosa
- **Resistencia 220Ω**: Para limitar corriente del LED
- **Sensor PIR (HC-SR501)**: Sensor de movimiento
- **Cable USB**: Para programar el ESP32
- **Cable jumper**: Para conexiones
- **Fuente de poder**: 5V para el ESP32

## Circuito

```
ESP32-WROOM-32
├─ GPIO 5 ──────────────────────── LED (a través de resistencia)
├─ GPIO 4 ──────────────────────── Sensor PIR (OUT)
├─ GND ──────────────────────────── Masa común
└─ 5V ───────────────────────────── Alimentación

Sensor PIR (HC-SR501)
├─ VCC ──────────────────────────── 5V
├─ GND ──────────────────────────── GND
└─ OUT ──────────────────────────── GPIO 4

LED
├─ Ánodo (+) ───────────────────── GPIO 5 (a través de resistencia 220Ω)
└─ Cátodo (-) ──────────────────── GND
```

## Instalación

### 1. Configurar Arduino IDE para ESP32

1. Abre Arduino IDE
2. Ve a **Preferencias** → **URLs de gestor de tarjetas adicionales**
3. Añade: `https://dl.espressif.com/dl/package_esp32_index.json`
4. Ve a **Herramientas** → **Placa** → **Gestor de tarjetas**
5. Busca "esp32" e instala
6. Selecciona: **Herramientas** → **Placa** → **ESP32 Arduino** → **ESP32 WROOM 32**

### 2. Cargar el código en ESP32

1. Copia el código de `led_motion_control_esp32.ino`
2. Pega en Arduino IDE
3. Conecta el ESP32 por USB
4. Selecciona el puerto COM correcto
5. Click en **Subir**

### 3. Crear la app en MIT App Inventor

1. Ve a https://appinventor.mit.edu/
2. Inicia sesión
3. Crea un nuevo proyecto
4. Sigue las instrucciones en `MIT_APP_INVENTOR_SETUP.md`

## Uso

### Activación automática por movimiento:
1. El sensor PIR detecta movimiento
2. El LED se enciende automáticamente
3. Se apaga después de 30 segundos sin movimiento (configurable)

### Control manual desde la app:
1. Alimenta el ESP32
2. Abre la app en tu celular
3. Conéctate a la red WiFi del ESP32
4. Presiona "Encender" para prender el LED
5. Presiona "Apagar" para apagar el LED

## Archivos del proyecto

- `led_motion_control_esp32.ino` - Código del microcontrolador
- `MIT_APP_INVENTOR_SETUP.md` - Guía de MIT App Inventor
- `aia_blocks.txt` - Descripción de los bloques MIT App Inventor
- `circuito_esquema.txt` - Detalles del circuito
- `INSTALACION.md` - Guía de instalación paso a paso
- `INSTALACION.bat` - Script de instalación automatizado para Windows

## Especificaciones Técnicas

### Sensor PIR (HC-SR501)
- Voltaje: 5V
- Rango de detección: 5-20 metros
- Ángulo de detección: 110°
- Tiempo de activación: 2-3 segundos
- GPIO: 4

### LED
- Voltaje: 3.3V o 5V (según configuración)
- Corriente máxima: 20mA
- GPIO: 5
- Resistencia limitadora: 220Ω

### WiFi
- SSID: `ESP32_LED_Control`
- Contraseña: `12345678`
- IP: `192.168.4.1`

## Configuración personalizada

Puedes modificar en el código:
```cpp
const int LED_PIN = 5;              // GPIO del LED
const int MOTION_SENSOR_PIN = 4;    // GPIO del sensor PIR
const int MOTION_TIMEOUT = 30;      // Segundos antes de apagar por inactividad
const char* ssid = "ESP32_LED_Control";
const char* password = "12345678";
```

## Troubleshooting

### El sensor no detecta movimiento
- Verifica la conexión del sensor
- Asegúrate que el sensor tiene alimentación 5V
- El sensor necesita 30-60 segundos para calibrar al iniciar
- Aumenta la sensibilidad con el potenciómetro del sensor (si tiene)

### El LED no se enciende
- Verifica la conexión GPIO 5
- Comprueba que la resistencia está correcta (220Ω)
- Verifica polaridad del LED
- Prueba el LED directamente con una fuente 3.3V

### No se conecta a la app
- Verifica WiFi: ESP32_LED_Control
- Comprueba la IP: 192.168.4.1
- Reinicia el ESP32
- Verifica el puerto serial a 115200 baud

## Autor
Tony83218

## Licencia
MIT
