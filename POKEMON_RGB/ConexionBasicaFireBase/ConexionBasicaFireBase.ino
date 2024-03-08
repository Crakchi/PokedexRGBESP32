#include <Firebase_ESP_Client.h>
#include <WiFi.h>
#include <addons/TokenHelper.h>
#include <ArduinoJson.h>
#define FIREBASE_USE_PSRAM

int LedR=25,LedV=33;

//Conectar a una red WiFi 
const char* WIFI_SSID = "CECY_ZAMBRANO";//el nombre de la red
const char* WIFI_PASSWORD = "rivera11";//la contraseña de la red
//Recursos de Firebase
const char* API_KEY = "AIzaSyChi5a-rXryy-T_jt__pjxNwZKElnRPcf0";
const char* FIREBASE_PROJECT_ID = "sumativariverasalinas";
//CONFIGURAR UN EMAIL Y CONTRASEÑA EN AUTHENTICATION de Firebase
const char* USER_EMAIL = "salinas@rivera.com";
const char* USER_PASSWORD = "salinas@rivera.com";
//Define Firebase Data object
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

void setup() {
  pinMode(25,OUTPUT);
  pinMode(33,OUTPUT);

  Serial.begin(115200);
  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);//Verificamos la version
  setupWiFi();//Llamamos la funcion de configuración wifi
  setupFirebase();//Llamamos la funcion de configuración Firebase
  digitalWrite(LedR,0);
  digitalWrite(LedV,0);
}

//Funcion para configuara WiFi
void setupWiFi() {
  Serial.print("Connecting to Wi-Fi");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    digitalWrite(LedR,1);
    delay(150);
    digitalWrite(LedR,0);
    delay(150);
  }
  digitalWrite(LedV,1);
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
}
void setupFirebase() {
  config.api_key = API_KEY;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  config.token_status_callback = tokenStatusCallback;  // Ver addons/TokenHelper.h
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}
void loop(){
String path = "Pokedex";//RUTA DE COLECCION
  FirebaseJson json;

  if (Firebase.Firestore.getDocument(&fbdo, FIREBASE_PROJECT_ID, "", path.c_str(), "")) {

    StaticJsonDocument<1024> doc;
    DeserializationError error = deserializeJson(doc, fbdo.payload().c_str());

    if (!error) {
      for (JsonObject document : doc["documents"].as<JsonArray>()) {
        const char* document_name = document["name"];//PARAMETRO NOMBRE == ID Documento
        Serial.print(document);
        const bool state = document["fields"]["fire"]["booleanValue"];//PARAMETRO DE CAMPOS A REVISAR
        Serial.print(" : ");
        if (strstr(document_name, "Tipo") != nullptr) {//COMPARAR NOMBRE CON  RESULTADO ESPERADO LED1
          state ? Serial.println("Fuego 1") : Serial.println("Fire 0");
        }
		  }
		delay(500);
	  } 
  }
}
