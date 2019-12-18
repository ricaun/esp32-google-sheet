/*
  esp32-google-sheet
  This project read analog input and sends to the google sheet
  created 16 12 2019
  by Luiz H. Cassettari - ricaun@gmail.com
*/

#include <WiFi.h>
#include <WebServer.h>

/* PINOS */

#define ANALOG_PIN A0 // pino 35
#define ANALOG_TIME 1

/* GOOGLE URL */

#define GOOGLE_URL "https://script.google.com/macros/s/#######################################################/exec"
#define GOOGLE_TIME 30

/* TaskHandle_t */

TaskHandle_t Task0;

/* WIFI */

const char *ssid = "";
const char *password = "";

// ----------------- server ------------------- //

WebServer server(80);

const char *script = "<script>function loop() {var resp = GET_NOW('values'); document.getElementById('values').innerHTML = resp; setTimeout('loop()', 1000);} function GET_NOW(get) { var xmlhttp; if (window.XMLHttpRequest) xmlhttp = new XMLHttpRequest(); else xmlhttp = new ActiveXObject('Microsoft.XMLHTTP'); xmlhttp.open('GET', get, false); xmlhttp.send(); return xmlhttp.responseText; }</script>";

void handleRoot()
{
  String str = "";
  str += "<html>";
  str += "<head>";
  str += "<title>ESP32</title>";
  str += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  str += script;
  str += "</head>";
  str += "<body onload='loop()'>";
  str += "<center>";
  str += "<div id='values'></div>";
  str += "</center>";
  str += "</body>";
  str += "</html>";
  server.send(200, "text/html", str);
}

void handleGetValues()
{
  String str = "";

  str += readAnalogPin();

  server.send(200, "text/plain", str);
}

// ----------------- setup ------------------- //

void setup(void)
{
  Serial.begin(115200);

  pinMode(ANALOG_PIN, INPUT);
  
  WiFi.mode(WIFI_STA);
  if (ssid != "")
    WiFi.begin(ssid, password);
  WiFi.begin();
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/values", handleGetValues);
  server.begin();
  Serial.println("HTTP server started");
  get_body();

  //create a task that will be executed in the Task1code() function, with priority 1 and executed on core 0
  xTaskCreatePinnedToCore(
    TaskCode0,   /* Task function. */
    "IDLE0",     /* name of task. */
    10000,       /* Stack size of task */
    NULL,        /* parameter of the task */
    1,           /* priority of the task */
    &Task0,      /* Task handle to keep track of created task */
    0);          /* pin task to core 0 */
}

void TaskCode0( void * pvParameters ) {
  while (1)
  {
    google_loop();
    vTaskDelay(10);
  }
}

void loop(void)
{
  if (analog_runEvery(ANALOG_TIME * 1000))
  {
    add_body();
  }
  server.handleClient();
}

// ----------------- analog ------------------- //

float readAnalogPin()
{
  float f = analogRead(ANALOG_PIN);
  f *= 3.3 / 4095.0;
  Serial.print("ANALOG: ");
  Serial.println(f);
  return f;
}

boolean analog_runEvery(unsigned long interval)
{
  static unsigned long previousMillis = 0;
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    return true;
  }
  return false;
}

// ----------------- body ------------------- //

static String _body = "";

String add_body()
{
  _body += ";";
  _body += readAnalogPin();
}

String get_body()
{
  String payload = _body;
  String mac = WiFi.macAddress();
  _body = mac;
  return payload;
}

// ----------------- google ------------------- //

void google_loop()
{
  if (google_runEvery(GOOGLE_TIME * 1000))
  {
    String post = post_google(GOOGLE_URL, get_body());
    Serial.println(post);
  }
}

boolean google_runEvery(unsigned long interval)
{
  static unsigned long previousMillis = 0;
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    return true;
  }
  return false;
}
