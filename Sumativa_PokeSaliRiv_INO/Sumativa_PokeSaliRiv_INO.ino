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

// Definición de los pines
const int redPin = 13;
const int greenPin = 14;
const int bluePin = 32;
// Definición de los colores en formato RGB
const int colors[18][3] = {
  {96, 162, 185}, //  1- steel - acero - Azul claro
  {0, 0, 255}, //     2- water - agua - Azul
  {151, 166, 29}, //  3- bug - bicho - Verde oliva
  {90, 0, 255}, //    4- dragon - dragón - Azul violeta
  {250, 193, 0}, //   5- electric - eléctrico - Amarillo
  {150, 0, 255}, //   6- ghost - fantasma - Morado oscuro
  {255, 0, 0}, //     7- fire - fuego - Rojo
  {239, 112, 240}, // 8- fairy - hada - Rosa
  {61, 217, 255}, //  9- ice - hielo - Cian
  {255, 129, 0}, //   10 fight - lucha - Naranja
  {160, 162, 160}, // 11 normal - normal - Gris
  {0, 255, 0}, //     12 grass - planta - Verde
  {239, 63, 122}, //  13 psychic - psíquico - Rosa fuerte
  {175, 170, 129}, // 14 rock - roca - Beige
  {61, 0, 124}, //    15 dark - siniestro - morado
  {145, 55, 0}, //    16 ground - tierra - Marrón
  {145, 62, 203}, //  17 poison - veneno - Violeta
  {130, 186, 240} //  18 flying - volador - Azul cielo
};

// Definición de los nombres de los tipos de Pokémon
const char* names[] = {
  "steel", "water", "bug", "dragon", "electric", "ghost",
  "fire", "fairy", "ice", "fight", "normal", "grass",
  "psychic", "rock", "dark", "ground", "poison", "flying"
};

void setup() {
  pinMode(25,OUTPUT);
  pinMode(33,OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

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
       digitalWrite(LedV,1);
      for (JsonObject document : doc["documents"].as<JsonArray>()) {
        const char* document_name = document["name"];//PARAMETRO NOMBRE == ID Documento
        Serial.print(document);
        for (int i = 0; i < 18; i++) {
          const bool state = document["fields"][names[i]]["booleanValue"];
          Serial.print(" : ");
          if (strstr(document_name, "Tipo") != nullptr) {
            state ? Serial.println(String(names[i]) + " 1") : Serial.println(String(names[i]) + " 0");
            if (state) {
              setColor(colors[i][0], colors[i][1], colors[i][2]);
            }
          }
        }
      }
      delay(500);
    } 
  }
}

void setColor(int red, int green, int blue) {
  analogWrite(redPin, 255-red);
  analogWrite(greenPin, 255-green);
  analogWrite(bluePin, 255-blue);
}
