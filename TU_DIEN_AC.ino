int AC_LOAD = 11;    // Output to Opto Triac pin
int dimming = 128;  // Dimming level (0-128)  0 = ON, 128 = OFF
int i=0;
bool t = false;
#define nguon 4
#define dkden2 5
#define dkden1 6
#define dkquat 7
#define dkden2 5
#define den1 8
#define den2 9
#define loc 3
#define hongngoai1 A0
#define hongngoai2 A1
#define coi 13
int tg =0, conlai=0,tgg=0;
int gio,phut,giay;
long time;
bool n = false;
int q=0,d=0;
int thoigianchay = 3600; //đơn vị tính bằng giây
long thoigian = 0,thoigianchay1 = 0;
long chay =0, chay1 = 900, chay2 = 1800, chay3= 2700, chay4 = 3600; //Thười gian chạy các mức của đèn 1 tính theo s
String ttd1, ttd2, ttq;
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
#define ledloc 12
#define ledquat 10
void setup()
{
  Serial.begin(115200);
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  pinMode(AC_LOAD, OUTPUT);// Set AC Load pin as output
  attachInterrupt(0, zero_crosss_int, RISING);  
  pinMode(nguon, INPUT_PULLUP);
  pinMode(dkden2, INPUT_PULLUP);
  pinMode(dkden1, INPUT_PULLUP);
  pinMode(dkquat, INPUT_PULLUP);
  pinMode(hongngoai1, INPUT_PULLUP);
  pinMode(hongngoai2, INPUT_PULLUP);
  pinMode(loc, INPUT_PULLUP);
  pinMode(den1, OUTPUT);
  pinMode(den2, OUTPUT);
  pinMode(coi, OUTPUT);
  pinMode(ledloc, OUTPUT);
  pinMode(ledquat, OUTPUT);
  thoigian = millis();
}
// the interrupt function must take no parameters and return nothing
void zero_crosss_int()  
// function to be fired at the zero crossing to dim the light
{
  // Firing angle calculation : 1 full 50Hz wave =1/50=20ms  
  // Every zerocrossing thus: (50Hz)-> 10ms (1/2 Cycle) For 60Hz => 8.33ms
  // 10ms=10000us
  // (10000us - 10us) / 128 = 75 (Approx) For 60Hz =>65
  int dimtime = (75*dimming);    // For 60Hz =>65   
  //Serial.println(dimtime);   
  delayMicroseconds(dimtime);    // Off cycle
  digitalWrite(AC_LOAD, HIGH);   // triac firing
  delayMicroseconds(10);         // triac On propogation delay
                                 //(for 60Hz use 8.33)
  digitalWrite(AC_LOAD, LOW);    // triac Off
}
void loop()  {
 thoigian = millis()/1000;  //Chạy thời gian theo giây
  digitalWrite(denloc, LOW);
  if(digitalRead(nguon) == 0){
    n = !n;
    delay(500);
  }
  
  if(n){//dimming = 128 max 
     
    //////////////////điều khiển quạt ///////////
  if(digitalRead(dkquat) == 0){
    q = q+1;
    q = q%4;
    thoigianchay1 = thoigian;
    digitalWrite(denquat, LOW);
    delay(300);
  }
  if(q == 0){
    dimming = 128;
    thoigianchay1 = thoigian;
    ttq = "TAT";
  }
  if(q == 1){
    if(thoigian - thoigianchay1 <  thoigianchay){
    dimming = 84;
    Serial.println("TOC DO 1");
    ttq = "BAT";
    digitalWrite(denquat, HIGH);
    time = (thoigianchay*2) -  (thoigian-thoigianchay1);
    int gio = (time/3600)-1;
    int phut = (time /60)-1;
    int giay = time;
    if(digitalRead(loc)== 0){
    lcd.setCursor(0, 0);
  lcd.print("   DEM NGUOC    ");
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(3, 1);
  lcd.print(String(gio%24) + " : " + String(phut%60)+ " : " + String(giay%60));
  digitalWrite(denloc, HIGH); 
  delay(2000);
  }
  }
  else {dimming = 0;ttq = "TAT";}
  }
  if(q == 2){
    if(thoigian - thoigianchay1 <  thoigianchay){
    dimming = 42;
    Serial.println("TOC DO 2");
    ttq = "BAT";
    digitalWrite(denquat, HIGH);
    time = (thoigianchay*2) -  (thoigian-thoigianchay1);
    giay = time;
    int gio = (time/3600)-1;
    int phut = (time /60)-1;
    int giay = time;
    if(digitalRead(loc)== 0){
    lcd.setCursor(0, 0);
  lcd.print("   DEM NGUOC    ");
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(3, 1);
  lcd.print(String(gio%24) + " : " + String(phut%60)+ " : " + String(giay%60)); 
  digitalWrite(denloc, HIGH);
  delay(2000);
  }
  }
   else {dimming = 0;ttq = "TAT";}
  }
  if(q == 3){
    if(thoigian - thoigianchay1 <  thoigianchay){
    dimming = 0;
    Serial.println("TOC DO 3");
    ttq = "BAT";
    digitalWrite(denquat, HIGH);
    time = (thoigianchay*2) -  (thoigian-thoigianchay1);
    giay = time;
    int gio = (time/3600)-1;
    int phut = (time /60)-1;
    int giay = time;
    if(digitalRead(loc)== 0){
    lcd.setCursor(0, 0);
  lcd.print("   DEM NGUOC    ");
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(3, 1);
  lcd.print(String(gio%24) + " : " + String(phut%60)+ " : " + String(giay%60)); 
  digitalWrite(denloc, HIGH);
  delay(2000);
  
  }
  }
  else {dimming = 0;ttq = "TAT";}
  }
///////ĐIỀU KHIỂN ĐÈN 1//////////////// HẸN GIỜ
if(digitalRead(hongngoai1) == 1){
 t = true;
}
else t = false;
if(t){
if(digitalRead(dkden1) == 0){
    d = d+1;
    d = d%5;
    chay = thoigian;
    tg = millis();
    conlai = 0;
    delay(300);
  }
  if(d == 0){
    digitalWrite(den1, LOW);
    chay = thoigian;
    tg = millis();
    conlai = 0;
  }
  if(d == 1){
    if(thoigian - chay <  chay1){
    digitalWrite(den1, HIGH);
    digitalWrite(den2, LOW);
    Serial.println("CHAY KHOANG THOI GIAN 1");
    ttd1 = "BAT";
    if(millis() - tg >= 1000){
     conlai = (chay1 - 1);
     tgg = conlai;
     conlai = conlai/60;
     tg = millis();
    }
  }
  else digitalWrite(den1, LOW);
  }
  if(d == 2){
    if(thoigian - chay <  chay2){
    digitalWrite(den1, HIGH);
    digitalWrite(den2, LOW);
    Serial.println("CHAY KHOANG THOI GIAN 1");
    ttd1 = "BAT";
    if(millis() - tg >= 1000){
     conlai = (chay2 - 1);
     conlai = conlai/60;
     tg = millis();
    }
  }
  else digitalWrite(den1, LOW);
  }
  if(d == 3){
    if(thoigian - chay <  chay3){
    digitalWrite(den1, HIGH);
    digitalWrite(den2, LOW);
    Serial.println("CHAY KHOANG THOI GIAN 1");
    ttd1 = "BAT";
    if(millis() - tg >= 1000){
     conlai = (chay3 - 1);
     conlai = conlai/60;
     tg = millis();
    }
  }
  else digitalWrite(den1, LOW);
  }

  if(d == 4){
    if(thoigian - chay <  chay4){
    digitalWrite(den1, HIGH);
    digitalWrite(den2, LOW);
    Serial.println("CHAY KHOANG THOI GIAN 1");
    ttd1 = "BAT";
    if(millis() - tg >= 1000){
     conlai = (chay4 - 1);
     conlai = conlai/60;
     tg = millis();
    }
  }
  else digitalWrite(den1, LOW);
  }
}
else {
  digitalWrite(den1, LOW);
  d = 0;
  ttd1 = "TAT";
  conlai = 0;
}
  /////////ĐIỀU KHIỂN ĐÈN 2////////////
  if(digitalRead(dkden2) == 0){
    digitalWrite(den2, !digitalRead(den2));
    digitalWrite(den1, LOW);
    delay(300);
    }
    
     
    if(digitalRead(den1) == 0){ ttd1 = "TAT";}
    if(digitalRead(den2) == 1){
      ttd2 = "BAT";
      d = 0;
    }
    else ttd2 = "TAT";
  lcd.setCursor(0, 0);
  lcd.print("Q:      D2:     ");
  lcd.setCursor(3, 0);
  lcd.print(ttq); 
  lcd.setCursor(11, 0);
  lcd.print(ttd2); 
  lcd.setCursor(0, 1);
  lcd.print("DEN1:           ");
  lcd.setCursor(6, 1);
  lcd.print(String(ttd1) + "   " + String(conlai) + " : " + String(tgg%60));
  }
  else {
  lcd.setCursor(0, 0);
  lcd.print("    TAT NGUON    ");
  lcd.setCursor(0, 1);
  lcd.print("                 "); 
  digitalWrite(den1, LOW);
  digitalWrite(den2, LOW);
  dimming = 0; 
  }
digitalWrite(coi, !digitalRead(hongngoai2));
 }
