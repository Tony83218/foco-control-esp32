@echo off
REM Script de instalación para Control de LED con Sensor de Movimiento - ESP32-WROOM-32
REM Autor: Tony83218
REM Descripción: Este script automatiza la instalación de Arduino IDE y configuración del ESP32

setlocal enabledelayedexpansion
color 0A
cls

echo.
echo ========================================
echo    INSTALACION - LED + SENSOR PIR
echo    ESP32-WROOM-32
echo ========================================
echo.

REM Verificar si Python está instalado
python --version >nul 2>&1
if errorlevel 1 (
    echo [!] Python no encontrado. Descargar desde https://www.python.org/
    pause
    exit /b 1
)

REM Crear directorio de proyecto
if not exist "%USERPROFILE%\LED_Control_ESP32" (
    mkdir "%USERPROFILE%\LED_Control_ESP32"
    echo [+] Directorio creado: %USERPROFILE%\LED_Control_ESP32
)

cls
echo.
echo ========================================
echo    PASO 1: INSTALACION DE ARDUINO IDE
echo ========================================
echo.
echo [1] Descargar Arduino IDE desde:
echo     https://www.arduino.cc/en/software
echo.
echo [2] Ejecutar el instalador
echo.
echo [3] Seleccionar componentes a instalar
echo.
pause
echo.

cls
echo.
echo ========================================
echo    PASO 2: CONFIGURAR ESP32 EN ARDUINO
echo ========================================
echo.
echo Sigue estos pasos en Arduino IDE:
echo.
echo [1] Ve a Archivo > Preferencias
echo [2] En "URLs de Gestor de Tarjetas Adicionales" pega:
echo     https://dl.espressif.com/dl/package_esp32_index.json
echo [3] Click OK
echo [4] Ve a Herramientas > Placa > Gestor de tarjetas
echo [5] Busca "esp32" e instala
echo [6] Espera a que termine la instalación
echo.
pause
echo.

cls
echo.
echo ========================================
echo    PASO 3: SELECCIONAR LA PLACA
echo ========================================
echo.
echo En Arduino IDE:
echo [1] Ve a Herramientas > Placa
echo [2] Selecciona: ESP32 Arduino > ESP32 WROOM 32
echo [3] Ve a Herramientas > Upload Speed: 921600
echo [4] Ve a Herramientas > CPU Frequency: 240MHz
echo [5] Ve a Herramientas > Flash Mode: DIO
echo [6] Ve a Herramientas > Flash Size: 4MB
echo.
pause
echo.

cls
echo.
echo ========================================
echo    PASO 4: CONECTAR ESP32
echo ========================================
echo.
echo [1] Conecta el ESP32 por USB a tu PC
echo [2] Ve a Herramientas > Puerto
echo [3] Selecciona el puerto COM (ej: COM3)
echo [4] Si no aparece, instala driver CH340:
echo     https://www.wemos.cc/en/latest/ch340_driver.html
echo.
pause
echo.

cls
echo.
echo ========================================
echo    PASO 5: CARGAR EL CODIGO
echo ========================================
echo.
echo [1] Abre Arduino IDE
echo [2] Abre el archivo: led_motion_control_esp32.ino
echo [3] Verifica: Sketch > Verify/Compile
echo [4] Si todo está bien, Sube: Sketch > Upload
echo [5] Espera el mensaje: "Done uploading"
echo.
pause
echo.

cls
echo.
echo ========================================
echo    PASO 6: VERIFICAR CONEXION
echo ========================================
echo.
echo [1] En Arduino IDE abre: Herramientas > Serial Monitor
echo [2] Velocidad: 115200 baud
echo [3] Deberías ver:
echo     "Iniciando ESP32..."
echo     "AP IP address: 192.168.4.1"
echo     "Servidor iniciado"
echo.
pause
echo.

cls
echo.
echo ========================================
echo    PASO 7: CREAR APP EN MIT APP INVENTOR
echo ========================================
echo.
echo [1] Ve a https://appinventor.mit.edu/
echo [2] Inicia sesión con tu cuenta Google
echo [3] Click en "Create apps!"
echo [4] Nombre: ControlLED
echo [5] Click en "Create"
echo [6] Sigue la guía en: MIT_APP_INVENTOR_SETUP.md
echo.
pause
echo.

cls
echo.
echo ========================================
echo    PASO 8: CONECTAR DESDE EL TELEFONO
echo ========================================
echo.
echo WiFi:
echo [1] Abre configuración WiFi en tu teléfono
echo [2] Busca red: "ESP32_LED_Control"
echo [3] Contraseña: "12345678"
echo [4] Conecta
echo.
echo App:
echo [1] Descarga "MIT AI2 Companion" desde Play Store
echo [2] En MIT App Inventor: Connect > AI Companion
echo [3] Escanea el código QR
echo [4] ¡Prueba la app!
echo.
pause
echo.

cls
echo.
echo ========================================
echo    INFORMACIÓN IMPORTANTE
echo ========================================
echo.
echo CIRCUITO:
echo  - GPIO 5 (LED) con resistencia 220 ohm a GND
echo  - GPIO 4 (Sensor PIR OUT) a 5V
echo  - GND común a todos los componentes
echo.
echo WIFI:
echo  - SSID: ESP32_LED_Control
echo  - Contraseña: 12345678
echo  - IP: 192.168.4.1
echo.
echo SENSOR PIR (HC-SR501):
echo  - Necesita 30-60 segundos para calibrar
echo  - Rango: 5-20 metros
echo  - Ángulo: 110 grados
echo.
echo TROUBLESHOOTING:
echo  - Si no aparece puerto COM, instala driver CH340
echo  - Si LED no brilla, verifica polaridad
echo  - Si sensor no detecta, verifica alimentación 5V
echo.
pause
echo.

cls
echo.
echo ========================================
echo    INSTALACION COMPLETADA
echo ========================================
echo.
echo ✓ Sistema listo para usar
echo.
echo Archivos importantes:
echo  - led_motion_control_esp32.ino
echo  - MIT_APP_INVENTOR_SETUP.md
echo  - circuito_esquema.txt
echo  - README.md
echo.
echo Para más información:
echo  https://github.com/Tony83218/foco-control-esp32
echo.
pause
echo.
