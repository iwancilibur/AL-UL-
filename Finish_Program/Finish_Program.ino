#define BLYNK_PRINT Serial

#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <RBDdimmer.h>
#include <DHT.h>
#include <Arduino.h>
#include <BH1750.h>
#include <Wire.h>
#define TCAADDR 0x70

BH1750 lightMeter1;
BH1750 lightMeter2;
BH1750 lightMeter3;
BH1750 lightMeter4;
BH1750 lightMeter5;

#define pindht_kelas1 22 
#define pindht_kelas2 23
#define pindht_kelas3 24
#define pindht_kelas4 25
#define pindht_kelas5 26
#define typedhtnya DHT11 

DHT dht_kelas1(pindht_kelas1, typedhtnya);
DHT dht_kelas2(pindht_kelas2, typedhtnya);
DHT dht_kelas3(pindht_kelas3, typedhtnya);
DHT dht_kelas4(pindht_kelas4, typedhtnya);
DHT dht_kelas5(pindht_kelas5, typedhtnya);

//Membuat Variable untuk Pin Control dimmer Manual
#define pinm_kelas1  3 
#define pinm_kelas2  4
#define pinm_kelas3  5 
#define pinm_kelas4  6
#define pinm_kelas5  7 

//Membuat Variable untuk Pin Control dimmer Otomatis
#define pino_kelas1  8 
#define pino_kelas2  9
#define pino_kelas3  10
#define pino_kelas4  11
#define pino_kelas5  12

#define zerocross  2  //Menentukan pin Untuk controller Dimmer  "Default Arduino mega 2560 dan Jangan dirubah"


//Konfigurasi Dimmer dan membuat alias untuk pengontrolan contoh "manual_kelas1"
dimmerLamp manual_kelas1(pinm_kelas1);
dimmerLamp manual_kelas2(pinm_kelas2);
dimmerLamp manual_kelas3(pinm_kelas3);
dimmerLamp manual_kelas4(pinm_kelas4);
dimmerLamp manual_kelas5(pinm_kelas5);

//Konfigurasi Dimmer dan membuat alias untuk pengontrolan contoh "otomatis_kelas1"
dimmerLamp otomatis_kelas1(pino_kelas1);
dimmerLamp otomatis_kelas2(pino_kelas2);
dimmerLamp otomatis_kelas3(pino_kelas3);
dimmerLamp otomatis_kelas4(pino_kelas4);
dimmerLamp otomatis_kelas5(pino_kelas5);

char auth[] = "1e330210357e4c9bb9782d86d8b1867e"; //Token untuk koneksi ke blynk server

char ssid[] = "www.interactiverobotics.club1"; // Nama Hotspot yang digunakan
char pass[] = "cilibur2019";                  // Password Hotspot
#define EspSerial Serial1  //Serial yang digunakan untuk koneksi ke ESP8266 

#define ESP8266_BAUD 115200 //Baudrate ESP8266

ESP8266 wifi(&EspSerial); //Alias koneksi esp8266 ke wifi

BlynkTimer timer; //Mengganti variable untuk blynk timer

void tcaselect(uint8_t i) {
  if (i > 7) return;
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission(); 
}

void setup()
{
  Serial.begin(115200);
  EspSerial.begin(ESP8266_BAUD);

  dht_kelas1.begin();
  dht_kelas2.begin();
  dht_kelas3.begin();
  dht_kelas4.begin();
  dht_kelas5.begin();
  
  manual_kelas1.begin(NORMAL_MODE, ON);
  manual_kelas2.begin(NORMAL_MODE, ON);
  manual_kelas3.begin(NORMAL_MODE, ON);
  manual_kelas4.begin(NORMAL_MODE, ON);
  manual_kelas5.begin(NORMAL_MODE, ON);

  otomatis_kelas1.begin(NORMAL_MODE, ON);
  otomatis_kelas2.begin(NORMAL_MODE, ON);
  otomatis_kelas3.begin(NORMAL_MODE, ON);
  otomatis_kelas4.begin(NORMAL_MODE, ON);
  otomatis_kelas5.begin(NORMAL_MODE, ON);

  Wire.begin();
                      //Clear all the display's
  tcaselect(0);lightMeter1.begin();
  tcaselect(1);lightMeter2.begin();
  tcaselect(2);lightMeter3.begin();
  tcaselect(3);lightMeter4.begin();
  tcaselect(4);lightMeter5.begin();
  delay(10);
  
  Blynk.begin(auth, wifi, ssid, pass, "iwancilibur.my.id", 8080);
  timer.setInterval(1L, myTimerEvent);
}

BLYNK_WRITE(V1) //DIMMER MANUAL CONTROL KELAS1
{
  int ambildata = param.asInt(); // assigning incoming value from pin V1 to a variable
  Serial.print("V1 data: ");
  Serial.println(ambildata);
  manual_kelas1.setPower(ambildata); 
}

BLYNK_WRITE(V2) //DIMMER MANUAL CONTROL KELAS2
{
  int ambildata = param.asInt(); // assigning incoming value from pin V1 to a variable
  Serial.print("V2 data: ");
  Serial.println(ambildata);
  manual_kelas2.setPower(ambildata); 
}

BLYNK_WRITE(V3) //DIMMER MANUAL CONTROL KELAS3
{
  int ambildata = param.asInt(); // assigning incoming value from pin V1 to a variable
  Serial.print("V3 data: ");
  Serial.println(ambildata);
  manual_kelas3.setPower(ambildata); 
}

BLYNK_WRITE(V4) //DIMMER MANUAL CONTROL KELAS4
{
  int ambildata = param.asInt(); // assigning incoming value from pin V1 to a variable
  Serial.print("V4 data: ");
  Serial.println(ambildata);
  manual_kelas4.setPower(ambildata); 
}

BLYNK_WRITE(V5) //DIMMER MANUAL CONTROL KELAS5
{
  int ambildata = param.asInt(); // assigning incoming value from pin V1 to a variable
  Serial.print("V5 data: ");
  Serial.println(ambildata);
  manual_kelas5.setPower(ambildata); 
}


void myTimerEvent()
{
   //INISIALISASI DATA

   //Ambil data Cahaya
   tcaselect(0); int lux1 = lightMeter1.readLightLevel(); int get_kelas1=lux1; 
   tcaselect(1); int lux2 = lightMeter2.readLightLevel(); int get_kelas2=lux2; 
   tcaselect(2); int lux3 = lightMeter3.readLightLevel(); int get_kelas3=lux3; 
   tcaselect(3); int lux4 = lightMeter4.readLightLevel(); int get_kelas4=lux4; 
   tcaselect(4); int lux5 = lightMeter5.readLightLevel(); int get_kelas5=lux5; 

   //Konversi cahaya
   get_kelas1=map(get_kelas1,0,1500,0,100);
   get_kelas2=map(get_kelas2,0,1500,0,100);
   get_kelas3=map(get_kelas3,0,1500,0,100);
   get_kelas4=map(get_kelas4,0,1500,0,100);
   get_kelas5=map(get_kelas5,0,1500,0,100);
   
   /*/
    * 
   float suhu_kelas1= dht_kelas1.readTemperature(); float kelembaban_kelas1 = dht_kelas1.readHumidity();
   float suhu_kelas2= dht_kelas2.readTemperature(); float kelembaban_kelas2 = dht_kelas2.readHumidity();
   float suhu_kelas3= dht_kelas3.readTemperature(); float kelembaban_kelas3 = dht_kelas3.readHumidity();
   float suhu_kelas4= dht_kelas4.readTemperature(); float kelembaban_kelas4 = dht_kelas4.readHumidity();
   float suhu_kelas5= dht_kelas5.readTemperature(); float kelembaban_kelas5 = dht_kelas5.readHumidity();
   /*/
   
   float suhu_kelas1= random(33,38); float kelembaban_kelas1 = random(60,80);
   float suhu_kelas2= random(33,38); float kelembaban_kelas2 = random(60,80);
   float suhu_kelas3= random(33,38); float kelembaban_kelas3 = random(60,80);
   float suhu_kelas4= random(33,38); float kelembaban_kelas4 = random(60,80);
   float suhu_kelas5= random(33,38); float kelembaban_kelas5 = random(60,80);
   //_______________________________________________________________________________________________________________________//
   
   //AKSI DARI OTOMATISASI 
   otomatis_kelas1.setPower(get_kelas1);
   otomatis_kelas2.setPower(get_kelas2);
   otomatis_kelas3.setPower(get_kelas3);
   otomatis_kelas4.setPower(get_kelas4);
   otomatis_kelas5.setPower(get_kelas5);
   //_______________________________________________________________________________________________________________________//

   //POST DATA TO Serial
   Serial.print("LUX 1: ");Serial.print(get_kelas1); Serial.print(" | Temp: "); Serial.print(suhu_kelas1); Serial.print(" | Humy: ");Serial.println(kelembaban_kelas1);  
   Serial.print("LUX 2: ");Serial.print(get_kelas2); Serial.print(" | Temp: "); Serial.print(suhu_kelas2); Serial.print(" | Humy: ");Serial.println(kelembaban_kelas2); 
   Serial.print("LUX 3: ");Serial.print(get_kelas3); Serial.print(" | Temp: "); Serial.print(suhu_kelas3); Serial.print(" | Humy: ");Serial.println(kelembaban_kelas3); 
   Serial.print("LUX 4: ");Serial.print(get_kelas4); Serial.print(" | Temp: "); Serial.print(suhu_kelas4); Serial.print(" | Humy: ");Serial.println(kelembaban_kelas4); 
   Serial.print("LUX 5: ");Serial.print(get_kelas5); Serial.print(" | Temp: "); Serial.print(suhu_kelas5); Serial.print(" | Humy: ");Serial.println(kelembaban_kelas5); 
  
   //POST DATA TO BLYNK SERVER
   Blynk.virtualWrite(V6, get_kelas1);  Blynk.virtualWrite(V11, suhu_kelas1); Blynk.virtualWrite(V16, kelembaban_kelas1);
   Blynk.virtualWrite(V7, get_kelas2);  Blynk.virtualWrite(V12, suhu_kelas2); Blynk.virtualWrite(V17, kelembaban_kelas2);
   Blynk.virtualWrite(V8, get_kelas3);  Blynk.virtualWrite(V13, suhu_kelas3); Blynk.virtualWrite(V18, kelembaban_kelas3);
   Blynk.virtualWrite(V9, get_kelas4);  Blynk.virtualWrite(V14, suhu_kelas4); Blynk.virtualWrite(V19, kelembaban_kelas4);
   Blynk.virtualWrite(V10, get_kelas5); Blynk.virtualWrite(V15, suhu_kelas5); Blynk.virtualWrite(V20, kelembaban_kelas5);
   //delay(100);
}


void loop()
{
  Blynk.run();
  timer.run(); 
}
