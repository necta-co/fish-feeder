#include "RTClib.h"
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Servo.h>

Servo s;
int pos;
const int pinoServo = 6;
const int PINO_ONEWIRE = 12;
char daysOfTheWeek[7][12] = {"Domingo", "Segunda", "Terça", "Quarta", "Quinta", "Sexta", "Sábado"};
int hora1 = 13;
int minuto = 00;
 
RTC_DS1307 rtc;
LiquidCrystal_I2C lcd(0x27, 16, 2);

OneWire oneWire(PINO_ONEWIRE);
DallasTemperature sensor(&oneWire);
DeviceAddress endereco_temp;

void setup () {
  s.attach(pinoServo);
  s.write(0);
  lcd.init();      
  lcd.backlight();
  if (! rtc.begin()) { 
    Serial.println("DS1307 não encontrado"); 
    while(1);
  }
  if (! rtc.isrunning()) {
    //REMOVA O COMENTÁRIO DE UMA DAS LINHAS ABAIXO PARA INSERIR AS INFORMAÇÕES ATUALIZADAS EM SEU RTC
    //rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //CAPTURA A DATA E HORA EM QUE O SKETCH É COMPILADO
    //rtc.adjust(DateTime(2023, 7, 23, 01, 21, 00)); //(ANO), (MÊS), (DIA), (HORA), (MINUTOS), (SEGUNDOS)
  }
  delay(100); 
}

void GetTemperatura ()
{
  sensor.requestTemperatures();
  float temperatura = sensor.getTempCByIndex(0);

  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(temperatura, 1);
  lcd.print("C     ");
  delay(1000); //INTERVALO DE 1 SEGUNDO
  lcd.setCursor(0,1);
  lcd.print("Menor Viado !!! ");
}

void GetTime() {
  DateTime now = rtc.now();
  
  char formattedTime[6]; // Cria um array de caracteres para armazenar a hora formatada

  // Formata a hora e os minutos com dois dígitos e armazena na variável formattedTime
  sprintf(formattedTime, "%02d:%02d", now.hour(), now.minute());

  lcd.setCursor(0, 0);
  lcd.print(now.day(), DEC);
  lcd.print('/');
  lcd.print(now.month(), DEC);
  lcd.print('/');
  lcd.print(now.year(), DEC);
  lcd.print(' ');
  lcd.print(formattedTime); // Imprime a hora formatada
  delay(1000);
}

void Alimentar()
{
  for(pos = 0; pos < 180; pos++){
    s.write(pos);
    delay(5);
  }
  for(pos = 180; pos >= 0; pos--){
    s.write(pos);
    delay(5);
  }
  
  for(pos = 0; pos < 180; pos++){
    s.write(pos);
    delay(5);
  }
  for(pos = 180; pos >= 0; pos--){
    s.write(pos);
    delay(5);
  }
  
  for(pos = 0; pos < 180; pos++){
    s.write(pos);
    delay(5);
  }
  for(pos = 180; pos >= 0; pos--){
    s.write(pos);
    delay(5);
  }
  
}
 
void loop () {
  DateTime now = rtc.now();
  if (now.hour() == hora1 && now.minute() == minuto) {
    Alimentar();
    delay(60000); // Espera 1 minuto (60.000 milissegundos)
  }

  GetTime();
  GetTemperatura();
}
