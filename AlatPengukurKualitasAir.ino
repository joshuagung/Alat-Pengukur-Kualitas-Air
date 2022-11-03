#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
#define konduktivitas  A0
#define pH A1

long int NilaiKonduktivitas[10], NilaipH[10];
float sumK, avgK, avgpH, OutputKesadahan, OutputSalinitas;

void setup(){
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

  for(int i=0;i<10;i++){
    NilaipH[i]=analogRead(pH);
    avgpH += NilaipH[i];
    delay(10);
  }

  for(int i=0;i<10;i++){
    NilaiKonduktivitas[i] = analogRead(konduktivitas);
    Serial.println(NilaiKonduktivitas[i]);

    lcd.setCursor(0, 0);
    lcd.print("Silakan tunggu:");
    lcd.setCursor(16, 0);
    lcd.print(i+1);

    sumK += NilaiKonduktivitas[i];
    avgK = sumK/10;
    delay(1000);
  }
  
  Serial.print("nilai avg: ");
  Serial.println(avgK);

  OutputKesadahan = (0.341*avgK)+281;
  OutputSalinitas = ((1.622*avgK)-688)/1000;
  float pHVol=(float)avgpH*5.0/1024/10;
  float phValue = (-5.70*pHVol)+21.34;
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ADC: ");
  lcd.setCursor(5, 0);
  lcd.print(avgK);

  lcd.setCursor(0, 1);
  lcd.print("Kesadahan: ");
  lcd.setCursor(11, 1);
  lcd.print(OutputKesadahan);

  lcd.setCursor(0, 2);
  lcd.print("Salinitas: ");
  lcd.setCursor(11, 2);
  lcd.print(OutputSalinitas);

  lcd.setCursor(0, 3);
  lcd.print("pH: ");
  lcd.setCursor(4, 3);
  lcd.print(phValue);
}

void loop() {

}
