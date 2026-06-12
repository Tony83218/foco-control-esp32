# Control de Foco con MIT App Inventor y ESP32-WROOM-32

## Descripción
Esta aplicación permite controlar una bombilla (foco) mediante una app móvil creada en MIT App Inventor, utilizando un microcontrolador ESP32-WROOM-32 para gestionar el encendido y apagado.

## Componentes necesarios

### Hardware
- **ESP32-WROOM-32**: Microcontrolador principal
- **Relé 5V**: Para controlar el foco
- **Foco LED o incandescente**: 220V o 12V según tu setup
- **Cable USB**: Para programar el ESP32
- **Cable jumper**: Para conexiones
- **Fuente de poder**: 5V para el ESP32

## Circuito

```
ESP32-WROOM-32
│
├─ GPIO 5 ─────────────────────► Relé (Pin IN)
├─ GND ──────────────────────────► Relé (GND)
├─ 5V ───────────────────────────► Relé (VCC)
│

Relé
│
├─ COM ──────────────────────────► Fase del Foco
├─ NO  ──────────────────────────► Foco
└─ GND ──────────────────────────► Foco (Retorno)
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

1. Copia el código de `foco_control_esp32.ino`
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

1. Alimenta el ESP32
2. Abre la app en tu celular
3. Conéctate a la red WiFi del ESP32
4. Presiona "Encender" para prender el foco
5. Presiona "Apagar" para apagar el foco

## Archivos del proyecto

- `foco_control_esp32.ino` - Código del microcontrolador
- `MIT_APP_INVENTOR_SETUP.md` - Guía de MIT App Inventor
- `aia_blocks.txt` - Descripción de los bloques MIT App Inventor
- `circuito_esquema.txt` - Detalles del circuito
- `INSTALACION.md` - Guía de instalación paso a paso

## Autor
Tony83218

## Licencia
MIT
