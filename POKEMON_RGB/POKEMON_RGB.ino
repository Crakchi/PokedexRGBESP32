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
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  Serial.begin(9600);
  setColor(0, 0, 0); // Inicialmente el LED está apagado
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();
    if (input == "0") {
      setColor(0, 0, 0); // Apagar el LED
      Serial.println("LED apagado");
    } else {
      for (int i = 0; i < 18; i++) {
        if (input == names[i] || input == String(i + 1)) {
          setColor(colors[i][0], colors[i][1], colors[i][2]);
          Serial.println(names[i]);
          break;
        }
      }
    }
  }
}

void setColor(int red, int green, int blue) {
  analogWrite(redPin, 255-red);
  analogWrite(greenPin, 255-green);
  analogWrite(bluePin, 255-blue);
}