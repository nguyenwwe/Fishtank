#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
#include <WiFi.h>
#include <Firebase_ESP_Client.h>

#define WIFI_SSID "HIPTECH_FPT"
#define WIFI_PASSWORD "fpthiptech@2025"

#define API_KEY "AIzaSyBMU5LO0LZcCs1fNP3tpBXXGQZelAKwb-E"
#define DATABASE_URL "https://fishtank-978f1-default-rtdb.firebaseio.com/"

#define RELAY_PIN 4

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

void setup() {
  Serial.begin(115200);

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");

config.api_key = API_KEY;
config.database_url = DATABASE_URL;

Firebase.signUp(&config, &auth, "", "");

config.token_status_callback = tokenStatusCallback;

Firebase.begin(&config, &auth);
Firebase.reconnectWiFi(true);
}

void loop() {

  if (Firebase.RTDB.getInt(&fbdo, "/Light")) {

    int state = fbdo.intData();

    if (state == 1) {
      digitalWrite(RELAY_PIN, HIGH);
      Serial.println("Relay ON");
    } else {
      digitalWrite(RELAY_PIN, LOW);
      Serial.println("Relay OFF");
    }

  } else {
    Serial.println(fbdo.errorReason());
  }

  delay(1000);
}