# Guía de Instalación Completa

## 1. Instalación de Arduino IDE

### Windows
1. Descarga desde: https://www.arduino.cc/en/software
2. Ejecuta el instalador
3. Sigue los pasos de instalación

### Mac
1. Descarga desde: https://www.arduino.cc/en/software
2. Abre el archivo .zip
3. Arrastra Arduino.app a Aplicaciones

### Linux
```bash
sudo apt-get install arduino
```

## 2. Configurar ESP32 en Arduino IDE

1. **Abre Arduino IDE**

2. **Ve a Preferencias**
   - Windows/Linux: Archivo → Preferencias
   - Mac: Arduino → Preferencias

3. **Añade la URL del gestor de tarjetas**
   - Campo: "URLs de Gestor de Tarjetas Adicionales"
   - Pega: `https://dl.espressif.com/dl/package_esp32_index.json`
   - Click OK

4. **Instala la tarjeta ESP32**
   - Herramientas → Placa → Gestor de tarjetas
   - Busca: "esp32"
   - Instala: "ESP32 by Espressif Systems"
   - Espera a que termine la descarga

5. **Selecciona la placa**
   - Herramientas → Placa → ESP32 Arduino → "ESP32 WROOM 32"

6. **Configura los parámetros**
   - Herramientas → Upload Speed: 921600
   - Herramientas → CPU Frequency: 240MHz
   - Herramientas → Flash Mode: DIO
   - Herramientas → Flash Size: 4MB

## 3. Conectar ESP32

1. Conecta el ESP32 por USB a tu PC
2. Ve a Herramientas → Puerto
3. Selecciona el puerto COM (COM3, COM4, etc.)
   - Windows: COMx
   - Mac/Linux: /dev/ttyUSB0 o /dev/ttyACM0

## 4. Cargar el Código

1. Abre `foco_control_esp32.ino` en Arduino IDE
2. Verifica el código: Sketch → Verify/Compile
3. Sube el código: Sketch → Upload
4. Espera el mensaje: "Done uploading"

## 5. Verificar Conexión

1. Abre Serial Monitor: Herramientas → Serial Monitor
2. Velocidad: 115200 baud
3. Deberías ver:
   ```
   Iniciando ESP32...
   AP IP address: 192.168.4.1
   Servidor iniciado
   ```

## 6. Crear la App en MIT App Inventor

Sigue la guía: `MIT_APP_INVENTOR_SETUP.md`

## 7. Conectar desde tu Teléfono

### WiFi
1. Abre configuración WiFi en tu teléfono
2. Busca red: "ESP32_Foco_Control"
3. Contraseña: "12345678"
4. Conecta

### App
1. Descarga MIT AI2 Companion (Play Store)
2. En MIT App Inventor: Connect → AI Companion
3. Escanea el código QR
4. ¡Prueba la app!

## Troubleshooting

### No aparece el puerto COM
- Instala el driver CH340: https://www.wemos.cc/en/latest/ch340_driver.html
- Reinicia Arduino IDE
- Vuelve a conectar el ESP32

### Error "Failed to connect to COM port"
- Cierra Serial Monitor
- Verifica el puerto correcto
- Prueba con velocidad 115200

### No se conecta a WiFi
- Asegúrate que el código esté correcto
- Verifica que el ESP32 está encendido
- Reconfigura el WiFi en el código si es necesario

### El relé no funciona
- Verifica conexión GPIO 5
- Comprueba alimentación del relé
- Prueba con Serial Monitor para ver estados
