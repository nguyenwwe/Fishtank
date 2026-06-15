#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
#include <WiFi.h>
#include <Firebase_ESP_Client.h>

#define WIFI_SSID "HIPTECH_FPT"
#define WIFI_PASSWORD "fpthiptech@2025"

#define API_KEY "AIzaSyBMU5LO0LZcCs1fNP3tpBXXGQZelAKwb-E"
#define DATABASE_URL "https://fishtank-978f1-default-rtdb.firebaseio.com/"

#define RELAY_LIGHT_1 4
#define RELAY_LIGHT_2 19

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

void setup() {
  Serial.begin(115200);

  pinMode(RELAY_LIGHT_1, OUTPUT);
  digitalWrite(RELAY_LIGHT_1, LOW);

  
  pinMode(RELAY_LIGHT_2, OUTPUT);
  digitalWrite(RELAY_LIGHT_2, LOW);

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

  if (Firebase.RTDB.getInt(&fbdo, "Home/Light/Light_1")) {

    int state_light_1 = fbdo.intData();

    if (state_light_1 == 1) {
      digitalWrite(RELAY_LIGHT_1, HIGH);
      Serial.println("Led_1 ON");
    } else {
      digitalWrite(RELAY_LIGHT_1, LOW);
      Serial.println("Led_1 OFF");
    }

  } else {
    Serial.println(fbdo.errorReason());
  }

  if (Firebase.RTDB.getInt(&fbdo, "Home/Light/Light_2")) {

    int state_light_2 = fbdo.intData();

    if (state_light_2 == 1) {
      digitalWrite(RELAY_LIGHT_2, HIGH);
      Serial.println("Led_2 ON");
    } else {
      digitalWrite(RELAY_LIGHT_2, LOW);
      Serial.println("Led_2 OFF");
    }

  } else {
    Serial.println(fbdo.errorReason());
  }

  delay(1000);
}