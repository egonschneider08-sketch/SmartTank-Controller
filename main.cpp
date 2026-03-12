#include <Arduino.h>

#include <LiquidCrystal.h>
#include <EEPROM.h>

// LCD (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Sensores de nível
const int sensorNivel[5] = {6,7,8,9,10};

// Altura em cm
const int alturaNivel[5] = {2,4,6,8,9};

// Sensor de vazão (potenciômetro)
const int sensorVazao = A0;

// LED que representa a bomba
const int ledSistema = 13;

int alturaAtual = 0;
unsigned long consumoTotal = 0;

void setup()
{
  lcd.begin(16,2);

  for(int i=0;i<5;i++)
  {
    pinMode(sensorNivel[i], INPUT);
  }

  pinMode(ledSistema, OUTPUT);

  EEPROM.get(0, consumoTotal);

  lcd.print("Sistema Agua");
  delay(2000);
  lcd.clear();
}

void loop()
{
  lerNivel();
  controlarSistema();
  calcularConsumo();
  mostrarLCD();

  delay(500);
}

void lerNivel()
{
  for(int i=4;i>=0;i--)
  {
    if(digitalRead(sensorNivel[i]) == HIGH)
    {
      alturaAtual = alturaNivel[i];
      break;
    }
  }
}

void controlarSistema()
{
  if(alturaAtual <= 4)
  {
    digitalWrite(ledSistema, HIGH); // reservatorio enchendo
  }
  else if(alturaAtual >= 9)
  {
    digitalWrite(ledSistema, LOW); // reservatorio cheio
  }
}

void calcularConsumo()
{
  int leitura = analogRead(sensorVazao);

  int fluxo = map(leitura,0,1023,0,10);

  consumoTotal += fluxo;

  EEPROM.put(0, consumoTotal);
}

void mostrarLCD()
{
  lcd.setCursor(0,0);
  lcd.print("Nivel:");
  lcd.print(alturaAtual);
  lcd.print("cm   ");

  lcd.setCursor(0,1);
  lcd.print("Cons:");
  lcd.print(consumoTotal);
  lcd.print("L    ");
}