/*
 * Control de Foco con ESP32-WROOM-32 y MIT App Inventor
 * Autor: Tony83218
 * Descripción: Este código permite controlar un foco mediante comandos
 *              recibidos a través de un servidor web en el ESP32
 */

#include <WiFi.h>
#include <WebServer.h>

// Configuración WiFi
const char* ssid = "ESP32_Foco_Control";      // SSID de la red WiFi
const char* password = "12345678";             // Contraseña de la red WiFi

// Configuración del puerto web
WebServer server(80);

// GPIO del relé
const int RELE_PIN = 5;  // GPIO5 para el relé

// Variable de estado
bool focoEncendido = false;

void setup() {
  // Inicializar puerto serial
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("\n\nIniciando ESP32...");
  
  // Configurar GPIO
  pinMode(RELE_PIN, OUTPUT);
  digitalWrite(RELE_PIN, LOW);  // Apagar por defecto
  
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
  delay(10);
}

// Función para la página raíz
void handleRoot() {
  String html = R"(
    <!DOCTYPE html>
    <html>
    <head>
      <title>Control de Foco</title>
      <style>
        body { font-family: Arial; text-align: center; margin: 50px; }
        button { padding: 20px 40px; font-size: 18px; margin: 10px; }
        .encender { background-color: #FFD700; }
        .apagar { background-color: #FF6B6B; }
        .estado { font-size: 24px; margin: 20px; }
      </style>
    </head>
    <body>
      <h1>Control de Foco</h1>
      <div class="estado" id="estado">Estado: Apagado</div>
      <button class="encender" onclick="fetch('/encender')">ENCENDER</button>
      <button class="apagar" onclick="fetch('/apagar')">APAGAR</button>
    </body>
    </html>
  )";
  server.send(200, "text/html", html);
}

// Función para encender el foco
void handleEncender() {
  digitalWrite(RELE_PIN, HIGH);
  focoEncendido = true;
  Serial.println("Foco ENCENDIDO");
  server.send(200, "application/json", "{\"estado\":\"encendido\"}");
}

// Función para apagar el foco
void handleApagar() {
  digitalWrite(RELE_PIN, LOW);
  focoEncendido = false;
  Serial.println("Foco APAGADO");
  server.send(200, "application/json", "{\"estado\":\"apagado\"}");
}

// Función para obtener el estado
void handleEstado() {
  String estado = focoEncendido ? "encendido" : "apagado";
  String json = "{\"estado\":\"" + estado + "\"}";
  server.send(200, "application/json", json);
}

// Función para rutas no encontradas
void handleNotFound() {
  server.send(404, "text/plain", "Ruta no encontrada");
}
