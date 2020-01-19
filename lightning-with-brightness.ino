#define POTENTIOMETER_PIN A2

#define WHITE_LED_MOSFET_PIN 9
#define WHITE_SWITCH_PIN 8

#define UV_LED_MOSFET_PIN 11
#define UV_SWITCH_PIN 12

#define MAX_POTENTIOMETER_VALUE 1015
#define MIN_POTENTIOMETER_VALUE 100

#define MAX_BRIGHTNESS_VALUE 255
#define MIN_BRIGHTNESS_VALUE 0

int _brightness = 0;

void setup() {
  Serial.begin(9600);

  pinMode(POTENTIOMETER_PIN, INPUT);
  pinMode(WHITE_LED_MOSFET_PIN, OUTPUT);
  pinMode(WHITE_SWITCH_PIN, INPUT_PULLUP);
  pinMode(UV_LED_MOSFET_PIN, OUTPUT);
  pinMode(UV_SWITCH_PIN, INPUT_PULLUP);
}

void loop() {
  bool whiteSwitch = digitalRead(WHITE_SWITCH_PIN);
  bool uvSwitch = digitalRead(UV_SWITCH_PIN);

  Serial.print("W_SW: ");
  Serial.print(whiteSwitch);
  Serial.print(" UV_WS: ");
  Serial.print(uvSwitch);

  if (whiteSwitch == false || uvSwitch == false)
    ReadBrightness();
  else
  {
    analogWrite(WHITE_LED_MOSFET_PIN, MIN_BRIGHTNESS_VALUE);
    analogWrite(UV_LED_MOSFET_PIN, MIN_BRIGHTNESS_VALUE);
  }

  if (whiteSwitch == false)
  {
    analogWrite(WHITE_LED_MOSFET_PIN, _brightness);

    Serial.print(" White: ");
    Serial.print(_brightness);
  }

  if (uvSwitch == false)
  {
    analogWrite(UV_LED_MOSFET_PIN, _brightness);

    Serial.print(" UV: ");
    Serial.print(_brightness);
  }
  Serial.println();
}

void ReadBrightness() {
    int potentiometerValue = analogRead(POTENTIOMETER_PIN);
    _brightness = map(potentiometerValue, MIN_POTENTIOMETER_VALUE, MAX_POTENTIOMETER_VALUE, MIN_BRIGHTNESS_VALUE, MAX_BRIGHTNESS_VALUE);

    if (_brightness < MIN_BRIGHTNESS_VALUE)
      _brightness = MIN_BRIGHTNESS_VALUE;
    else if (_brightness > MAX_BRIGHTNESS_VALUE)
      _brightness = MAX_BRIGHTNESS_VALUE;
}
