#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>

const char *ssid = "ototronic";
const char *password = "mentaltempe112_";

WebServer server(80);

#define DHTPIN 14         // Pin yang terhubung ke DHT11
#define DHTTYPE DHT11     // Jenis sensor DHT11
DHT dht(DHTPIN, DHTTYPE); // Inisialisasi objek DHT

bool ledStatus = false;
float temperature = 0;
float humidity = 0;

void handleRoot()
{
    String html = "<html><body><h1>Wemos D1 R32</h1>";

    html += "<p>Temperature: ";
    html += temperature;
    html += " &#8451;</p>";

    html += "<p>Humidity: ";
    html += humidity;
    html += " %</p>";

    if (ledStatus)
    {
        html += "<p><a href=\"/ledoff\"><button style=\"font-size:24px;\">Matikan LED</button></a></p></body></html>";
    }
    else
    {
        html += "<p><a href=\"/ledon\"><button style=\"font-size:24px;\">Nyalakan LED</button></a></p></body></html>";
    }

    server.send(200, "text/html", html);
}

void handleLedOn()
{
    ledStatus = true;
    digitalWrite(2, LOW);
    server.sendHeader("Location", "/");
    server.send(302, "text/plain", "");
}

void handleLedOff()
{
    ledStatus = false;
    digitalWrite(2, HIGH);
    server.sendHeader("Location", "/");
    server.send(302, "text/plain", "");
}

void setup()
{
    pinMode(2, OUTPUT);
    digitalWrite(2, HIGH);

    Serial.begin(115200);
    delay(1000);

    WiFi.begin(ssid, password);
    Serial.println("");

    // Menunggu koneksi WiFi
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.print(".");
    }

    Serial.println("");
    Serial.print("WiFi connected, IP address: ");
    Serial.println(WiFi.localIP());

    dht.begin(); // Memulai sensor DHT

    server.on("/", handleRoot);
    server.on("/ledon", handleLedOn);
    server.on("/ledoff", handleLedOff);

    server.begin();
    Serial.println("Web server started");
}

void loop()
{
    server.handleClient();

    // Membaca data dari sensor DHT
    humidity = dht.readHumidity();
    temperature = dht.readTemperature();

    // Jika gagal membaca data dari sensor DHT
    if (isnan(humidity) || isnan(temperature))
    {
        Serial.println("Gagal membaca data dari sensor DHT!");
        return;
    }
}
