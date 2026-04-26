#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>

#define RELAY1 0
#define RELAY2 2

ESP8266WebServer server(80);
DNSServer dns;

const byte DNS_PORT = 53;

// AP credentials
const char* ssid = "ESP-Control"; // SSID
const char* password = "12345678"; // Passowrd

bool state1 = false;
bool state2 = false;

// ===== HTML =====
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>ESP Control</title>
<style>
*{box-sizing:border-box;}
body{margin:0;font-family:system-ui;background:linear-gradient(135deg,#0f172a,#1e293b);color:white;display:flex;justify-content:center;}
.container{width:100%;max-width:400px;padding:20px;}
h2{text-align:center;margin-bottom:30px;}
.card{background:rgba(255,255,255,0.05);backdrop-filter:blur(10px);padding:20px;margin-bottom:20px;border-radius:16px;}
.pb{width:100%;padding:22px;font-size:20px;border:none;border-radius:16px;color:white;background:#334155;transition:0.2s;}
.pb.on{background:#22c55e;box-shadow:0 0 18px rgba(34,197,94,0.6);}
.pb.off{background:#334155;}
.pb:active{transform:scale(0.96);}
</style>
</head>
<body>
<div class="container">
<h2>Stemba Tech</h2>

<div class="card">
<button id="btn1" class="pb off" onclick="toggle(1)">Relay 1</button>
</div>

<div class="card">
<button id="btn2" class="pb off" onclick="toggle(2)">Relay 2</button>
</div>

</div>

<script>
function toggle(r){
 fetch("/toggle?r="+r).then(()=>loadState());
}
function loadState(){
 fetch("/status")
  .then(res=>res.json())
  .then(data=>{
    setBtn("btn1",data.r1);
    setBtn("btn2",data.r2);
  });
}
function setBtn(id,state){
 let btn=document.getElementById(id);
 if(state){
  btn.classList.add("on");
  btn.classList.remove("off");
 }else{
  btn.classList.add("off");
  btn.classList.remove("on");
 }
}
loadState();
</script>

</body>
</html>
)rawliteral";

// ===== Handlers =====
void handleRoot() {
  server.send_P(200, "text/html", index_html);
}

void handleToggle() {
  int r = server.arg("r").toInt();

  if (r == 1) {
    state1 = !state1;
    digitalWrite(RELAY1, state1 ? LOW : HIGH);
  }
  if (r == 2) {
    state2 = !state2;
    digitalWrite(RELAY2, state2 ? LOW : HIGH);
  }

  server.send(200, "text/plain", "OK");
}

void handleStatus() {
  String json = "{";
  json += "\"r1\":" + String(state1 ? 1 : 0) + ",";
  json += "\"r2\":" + String(state2 ? 1 : 0);
  json += "}";

  server.send(200, "application/json", json);
}

// ===== Setup =====
void setup() {
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);

  digitalWrite(RELAY1, HIGH); // OFF (active LOW)
  digitalWrite(RELAY2, HIGH);

  // Stable AP config
  IPAddress apIP(192, 168, 4, 1);
  IPAddress netMsk(255, 255, 255, 0);
  WiFi.softAPConfig(apIP, apIP, netMsk);

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);

  dns.start(DNS_PORT, "*", WiFi.softAPIP());

  // ===== Normal routes =====
  server.on("/", handleRoot);
  server.on("/toggle", handleToggle);
  server.on("/status", handleStatus);

  // ===== Captive portal detection =====

  // Android
  server.on("/generate_204", []() {
    server.sendHeader("Location", "/", true);
    server.send(302, "text/plain", "");
  });

  // iOS
  server.on("/hotspot-detect.html", []() {
    server.send_P(200, "text/html", index_html);
  });

  // Windows
  server.on("/connecttest.txt", []() {
    server.send(200, "text/plain", "OK");
  });

  // Generic redirect (VERY IMPORTANT)
  server.onNotFound([]() {
    server.sendHeader("Location", "/", true);
    server.send(302, "text/plain", "");
  });

  server.begin();
}

// ===== Loop =====
void loop() {
  dns.processNextRequest();
  server.handleClient();
}
