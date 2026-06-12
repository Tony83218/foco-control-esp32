/*
 * Control de LED con Sensor de Movimiento (PIR) - ESP32-WROOM-32 y MIT App Inventor
 * Autor: Tony83218
 * Descripción: Este código permite controlar un LED mediante:
 *              1. Detección automática de movimiento (sensor PIR)
 *              2. Comandos manuales desde app móvil
 *              3. Interfaz web integrada en el ESP32
 */

#include <WiFi.h>
#include <WebServer.h>

// Configuración WiFi
const char* ssid = "ESP32_LED_Control";        // SSID de la red WiFi
const char* password = "12345678";              // Contraseña de la red WiFi

// Configuración del puerto web
WebServer server(80);

// GPIO del LED y sensor PIR
const int LED_PIN = 5;                          // GPIO5 para el LED
const int MOTION_SENSOR_PIN = 4;                // GPIO4 para el sensor PIR
const int MOTION_TIMEOUT = 30;                  // Segundos antes de apagar por inactividad

// Variables de estado
bool ledEncendido = false;
bool motionDetected = false;
unsigned long lastMotionTime = 0;
unsigned long lastManualControlTime = 0;
bool manualMode = false;

void setup() {
  // Inicializar puerto serial
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("\n\nIniciando ESP32 - Control de LED con Sensor de Movimiento...");
  
  // Configurar GPIO
  pinMode(LED_PIN, OUTPUT);
  pinMode(MOTION_SENSOR_PIN, INPUT);
  digitalWrite(LED_PIN, LOW);  // Apagar LED por defecto
  
  // Iniciar WiFi en modo AP (Access Point)
  WiFi.softAP(ssid, password);
  
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  
  // Configurar rutas del servidor web
  server.on("/", handleRoot);
  server.on("/encender", handleEncender);
  server.on("/apagar", handleApagar);
  server.on("/estado", handleEstado);
  server.on("/sensor", handleSensor);
  server.onNotFound(handleNotFound);
  
  // Iniciar servidor
  server.begin();
  Serial.println("Servidor iniciado");
  Serial.println("Conecta a:");
  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("Password: ");
  Serial.println(password);
  Serial.print("IP: http://");
  Serial.println(IP);
}

void loop() {
  server.handleClient();
  
  // Leer estado del sensor de movimiento
  int sensorValue = digitalRead(MOTION_SENSOR_PIN);
  
  if (sensorValue == HIGH) {
    motionDetected = true;
    lastMotionTime = millis();
    
    if (!ledEncendido) {
      digitalWrite(LED_PIN, HIGH);
      ledEncendido = true;
      Serial.println("LED ENCENDIDO por detección de movimiento");
    }
  }
  
  // Apagar LED después de timeout sin movimiento (solo en modo automático)
  if (!manualMode && motionDetected && (millis() - lastMotionTime > MOTION_TIMEOUT * 1000)) {
    motionDetected = false;
    if (ledEncendido && (millis() - lastManualControlTime > 2000)) {
      digitalWrite(LED_PIN, LOW);
      ledEncendido = false;
      Serial.println("LED APAGADO por timeout de inactividad");
    }
  }
  
  delay(100);
}

// Función para la página raíz
void handleRoot() {
  String html = R"(
    <!DOCTYPE html>
    <html>
    <head>
      <title>Control de LED</title>
      <style>
        body { 
          font-family: Arial; 
          text-align: center; 
          margin: 50px; 
          background-color: #f0f0f0;
        }
        .container {
          background-color: white;
          padding: 30px;
          border-radius: 10px;
          box-shadow: 0 0 10px rgba(0,0,0,0.1);
          max-width: 500px;
          margin: 0 auto;
        }
        h1 { color: #333; }
        button { 
          padding: 15px 30px; 
          font-size: 16px; 
          margin: 10px;
          border: none;
          border-radius: 5px;
          cursor: pointer;
          transition: 0.3s;
        }
        .encender { 
          background-color: #FFD700; 
          color: black;
        }
        .encender:hover { background-color: #FFC700; }
        .apagar { 
          background-color: #FF6B6B; 
          color: white;
        }
        .apagar:hover { background-color: #FF5555; }
        .estado { 
          font-size: 20px; 
          margin: 20px; 
          padding: 15px;
          background-color: #f9f9f9;
          border-radius: 5px;
        }
        .sensor-info {
          margin-top: 20px;
          padding: 15px;
          background-color: #e3f2fd;
          border-radius: 5px;
          font-size: 14px;
        }
      </style>
    </head>
    <body>
      <div class="container">
        <h1>💡 Control de LED</h1>
        <div class="estado" id="estado">Estado: Apagado</div>
        <div class="estado" id="sensor">Movimiento: No detectado</div>
        <button class="encender" onclick="encender()">ENCENDER</button>
        <button class="apagar" onclick="apagar()">APAGAR</button>
        <div class="sensor-info">
          <strong>Sensor PIR:</strong> Detecta movimiento automáticamente
          <br>El LED se apaga 30 segundos después de que se deja de detectar movimiento
        </div>
      </div>
      <script>
        function encender() {
          fetch('/encender');
          document.getElementById('estado').innerText = 'Estado: Encendido';
        }
        function apagar() {
          fetch('/apagar');
          document.getElementById('estado').innerText = 'Estado: Apagado';
        }
        setInterval(function() {
          fetch('/estado')
            .then(response => response.json())
            .then(data => {
              document.getElementById('estado').innerText = 'Estado: ' + (data.estado === 'encendido' ? 'Encendido' : 'Apagado');
            });
          fetch('/sensor')
            .then(response => response.json())
            .then(data => {
              document.getElementById('sensor').innerText = 'Movimiento: ' + (data.movimiento ? 'Detectado' : 'No detectado');
            });
        }, 1000);
      </script>
    </body>
    </html>
  )";
  server.send(200, "text/html", html);
}

// Función para encender el LED (modo manual)
void handleEncender() {
  digitalWrite(LED_PIN, HIGH);
  ledEncendido = true;
  manualMode = true;
  lastManualControlTime = millis();
  Serial.println("LED ENCENDIDO (Control manual)");
  server.send(200, "application/json", "{\"estado\":\"encendido\"}");
}

// Función para apagar el LED (modo manual)
void handleApagar() {
  digitalWrite(LED_PIN, LOW);
  ledEncendido = false;
  manualMode = false;
  lastManualControlTime = millis();
  motionDetected = false;
  Serial.println("LED APAGADO (Control manual)");
  server.send(200, "application/json", "{\"estado\":\"apagado\"}");
}

// Función para obtener el estado del LED
void handleEstado() {
  String estado = ledEncendido ? "encendido" : "apagado";
  String json = "{\"estado\":\"" + estado + "\"}";
  server.send(200, "application/json", json);
}

// Función para obtener el estado del sensor
void handleSensor() {
  int sensorValue = digitalRead(MOTION_SENSOR_PIN);
  String json = "{\"movimiento\":" + String(sensorValue ? "true" : "false") + "}";
  server.send(200, "application/json", json);
}

// Función para rutas no encontradas
void handleNotFound() {
  server.send(404, "text/plain", "Ruta no encontrada");
}
