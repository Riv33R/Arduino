#define speed 0 //скорость мерцания
#define intans 200 //интенсивность
#define diodport_1 12//порт первого светодиода
#define diodport_2 13//порт второго светодиода
int light = 0;

void vibrate() {
  for (int light = 1; light <= intans; light = light + 1) {
    Serial.println(light);
    analogWrite(diodport_1, light);
    analogWrite(diodport_2, light);
    delay(speed);
  }

  for (int light = intans; light >= 1; light = light - 1) {
    Serial.println(light);
    analogWrite(diodport_1, light);
    analogWrite(diodport_2, light);
    delay(speed);
  }

}

void setup()
{
  Serial.begin(9600);
  pinMode(diodport_1, OUTPUT);
  pinMode(diodport_2, OUTPUT);
}


void loop()
{
  vibrate();
}
