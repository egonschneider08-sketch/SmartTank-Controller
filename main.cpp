#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// Instâncias
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo valvula;

// Definição de Pinos (Usando nomes mais claros)
const int POT_PIN = A0;
const int MOTOR_PIN = 9;
const int SERVO_PIN = 10;

// LEDs de indicação
const int LED_10 = 2;
const int LED_30 = 3;
const int LED_50 = 4;
const int LED_70 = 5;
const int LED_90 = 6;

// Variáveis de controle
int nivel = 0;
int nivelAnterior = 0;
float consumo = 0; // em litros
bool bombaLigada = false;

void setup() {
    // Inicialização do LCD
    lcd.init();
    lcd.backlight();

    // Inicialização do Servo e Pinos
    valvula.attach(SERVO_PIN);
    pinMode(MOTOR_PIN, OUTPUT);
    pinMode(LED_10, OUTPUT);
    pinMode(LED_30, OUTPUT);
    pinMode(LED_50, OUTPUT);
    pinMode(LED_70, OUTPUT);
    pinMode(LED_90, OUTPUT);

    Serial.begin(9600);

    // Layout fixo do LCD para evitar flickering
    lcd.setCursor(0, 0);
    lcd.print("Nivel:     %");
    lcd.setCursor(0, 1);
    lcd.print("Cons:      L");
}

void loop() {
    // Leitura e mapeamento
    int leitura = analogRead(POT_PIN);
    nivel = map(leitura, 0, 1023, 0, 100);

    // Cálculo de consumo (Baseado no aumento de nível)
    if (nivel > nivelAnterior) {
        int diferenca = nivel - nivelAnterior;
        consumo += (float)diferenca * 100.0; // 1% = 100 litros
    }
    nivelAnterior = nivel;

    // Lógica de Histerese da Bomba
    if (nivel <= 10) bombaLigada = true;
    else if (nivel >= 90) bombaLigada = false;

    // Atuação de Hardware
    if (bombaLigada) {
        digitalWrite(MOTOR_PIN, HIGH);
        valvula.write(90); // Abre válvula
    } else {
        digitalWrite(MOTOR_PIN, LOW);
        valvula.write(0);  // Fecha válvula
    }

    // Atualização dos LEDs de Nível
    digitalWrite(LED_10, nivel >= 10);
    digitalWrite(LED_30, nivel >= 30);
    digitalWrite(LED_50, nivel >= 50);
    digitalWrite(LED_70, nivel >= 70);
    digitalWrite(LED_90, nivel >= 90);

    // Atualização do LCD (Apenas os valores numéricos)
    lcd.setCursor(7, 0);
    lcd.print("   "); // Limpa o valor anterior
    lcd.setCursor(7, 0);
    lcd.print(nivel);

    lcd.setCursor(6, 1);
    lcd.print("      "); // Limpa o valor anterior
    lcd.setCursor(6, 1);
    lcd.print((int)consumo);

    // Saída via Serial para Debug
    Serial.print("Nivel: ");
    Serial.print(nivel);
    Serial.print("% | Consumo: ");
    Serial.print(consumo);
    Serial.print(" L | Bomba: ");
    Serial.println(bombaLigada ? "LIGADA" : "DESLIGADA");

    delay(500);
}