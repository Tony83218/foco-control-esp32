# Guía: Crear la App en MIT App Inventor

## Paso 1: Crear el Proyecto

1. Ve a https://appinventor.mit.edu/
2. Inicia sesión con tu cuenta Google
3. Haz click en **Create apps!**
4. Selecciona **Start new project**
5. Nombre del proyecto: `ControlLED`
6. Click en **Create**

## Paso 2: Diseñar la Interfaz (Designer)

### Componentes a agregar:

#### 1. VerticalArrangement (Contenedor)
- **Propiedad AlignHorizontal**: Center
- **Propiedad Width**: Fill parent

#### 2. Label (Título)
- **Nombre**: `lbl_titulo`
- **Text**: "Control de LED"
- **FontSize**: 24
- **FontBold**: ✓ (marcado)

#### 3. Image (Imagen del LED)
- **Nombre**: `img_led`
- **Width**: 200
- **Height**: 200
- Descarga y sube una imagen de LED

#### 4. Label (Estado del LED)
- **Nombre**: `lbl_estado`
- **Text**: "Estado: Apagado"
- **FontSize**: 18

#### 5. Label (Estado del Sensor)
- **Nombre**: `lbl_sensor`
- **Text**: "Movimiento: No detectado"
- **FontSize**: 16
- **TextColor**: Blue

#### 6. Button (Encender)
- **Nombre**: `btn_encender`
- **Text**: "ENCENDER"
- **BackgroundColor**: Yellow (#FFD700)
- **FontSize**: 16
- **Width**: 150
- **Height**: 60

#### 7. Button (Apagar)
- **Nombre**: `btn_apagar`
- **Text**: "APAGAR"
- **BackgroundColor**: Red (#FF6B6B)
- **FontSize**: 16
- **Width**: 150
- **Height**: 60

#### 8. TextBox (IP del ESP32)
- **Nombre**: `txt_ip`
- **Text**: "192.168.4.1"
- **Hint**: "Ingresa IP del ESP32"

#### 9. Web (Componente no visual)
- **Nombre**: `web_esp32`
- Lo encontrarás en **Connectivity**

#### 10. Clock (Componente no visual)
- **Nombre**: `clock1`
- **TimerInterval**: 1000 (actualizar cada 1 segundo)

## Paso 3: Programar la Lógica (Blocks)

1. Haz click en la pestaña **Blocks**

### Bloque 1: Cuando presiona Encender

```
when btn_encender.Click
  do call web_esp32.Get
    with url → join "http://" txt_ip.Text "/encender"
  do set lbl_estado.Text → "Estado: Encendido"
  do set img_led.Picture → (imagen LED encendido)
```

### Bloque 2: Cuando presiona Apagar

```
when btn_apagar.Click
  do call web_esp32.Get
    with url → join "http://" txt_ip.Text "/apagar"
  do set lbl_estado.Text → "Estado: Apagado"
  do set img_led.Picture → (imagen LED apagado)
```

### Bloque 3: Actualizar estado cada segundo

```
when clock1.Timer
  do call web_esp32.Get
    with url → join "http://" txt_ip.Text "/estado"
  do call web_esp32.Get
    with url → join "http://" txt_ip.Text "/sensor"
```

### Bloque 4: Respuesta del estado del LED

```
when web_esp32.GotText
  responseCode, responseText
  if responseCode = 200
    do set lbl_estado.Text → 
      join "Estado: " (get_json_value responseText "estado")
```

### Bloque 5: Respuesta del sensor de movimiento

```
when web_esp32.GotText
  responseCode, responseText
  if (contains responseText "movimiento")
    do set lbl_sensor.Text → 
      if (get_json_value responseText "movimiento")
        then "Movimiento: Detectado"
        else "Movimiento: No detectado"
```

## Paso 4: Descargar e Instalar la App

### Opción A: Usar MIT AI2 Companion (Más rápido)
1. En tu teléfono, descarga la app **MIT AI2 Companion** desde Play Store
2. En MIT App Inventor, click en **Connect** → **AI Companion**
3. Escanea el código QR
4. ¡Tu app estará lista para probar!

### Opción B: Generar APK (Archivo instalable)
1. Click en **Build** → **App (save .apk to my computer)**
2. Espera a que se genere el archivo
3. Descarga el APK a tu PC
4. Transfiere el APK a tu teléfono Android
5. Instala la app

## Paso 5: Probar la App

1. Alimenta el ESP32
2. Conecta tu teléfono a la red WiFi: **ESP32_LED_Control**
   - Contraseña: **12345678**
3. Abre la app
4. Verifica que la IP esté correcta: **192.168.4.1**
5. ¡Prueba los botones Encender y Apagar!
6. Prueba el sensor moviendo la mano frente a él

## Troubleshooting

### Problema: La app no se conecta
- ✓ Verifica que el ESP32 esté encendido
- ✓ Comprueba que la IP es correcta
- ✓ Asegúrate que el teléfono está conectado a la red WiFi del ESP32
- ✓ Reinicia el ESP32 y la app

### Problema: El LED no se enciende
- ✓ Verifica la conexión GPIO 5
- ✓ Comprueba la resistencia (220Ω)
- ✓ Verifica la polaridad del LED
- ✓ Prueba el LED directamente

### Problema: El sensor no funciona
- ✓ Verifica la conexión GPIO 4
- ✓ Asegúrate que el sensor tiene alimentación 5V
- ✓ Espera 30-60 segundos para calibración
- ✓ Prueba a 5-20 cm del sensor

## Imágenes Recomendadas

Puedes usar emojis o descargar imágenes de:
- https://www.flaticon.com/ (LED)
- https://www.pixabay.com/ (LED)
- Emoji: 💡 para LED encendido, 🔲 para apagado

Guarda como PNG y sube en MIT App Inventor.
