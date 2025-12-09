#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <efe_pomodoro.h>

LiquidCrystal_I2C lcd(0x3F,16,2);

uint8_t durum = 0;

Pins pinler(21,22,23,14,25,26);

Time zaman;

lcdprint lcdyazdir;

State_Machine makine = DUR;

State_Machine eski= DUR;

void setup() {

  Serial.begin(9600);

  zaman.loadCycle();

  zaman.loadSettings();
  
  pinler.begin();

  lcdyazdir.lcdbegin(&lcd);

  lcd.clear();

}

void loop() {
  
  zaman.setBtnTimes(&pinler,makine,&lcd);

  if(makine!=eski){
    lcd.clear();

    if (makine == DUR) {
          lcd.setCursor(0,0);
          lcd.print("Durduruldu");
          lcd.setCursor(0,1);
          lcd.print("Basla -> Devam");
      }
    eski=makine;
  }

  
  switch (makine)
  {
  case DUR:
    
    break;
  case DEVAM:
    
    if(zaman.calcKalan()==0){
      
      zaman.setTur(zaman.getTur() + 1);

      zaman.saveCycle();

      durum |= DURDUR;

      durum &= ~BASLAT;

      makine = DUR;

      lcd.clear();
      
      lcd.print("SURE BITTI!");
        
      lcd.setCursor(0,1);
        
      lcd.print("Tur Tamamlandi");
        
      delay(3000); 
        
      lcd.clear();
    }
    else{

      lcdyazdir.lcdSettings(&lcd,&zaman);
      
    }
    

    break;
  
  case SIFIRLA:
    
    lcd.setCursor(0,0);

    lcd.print("Tur sifirlandi");

    lcd.setCursor(0,1);

    lcd.print("Tur Sayisi:");

    lcd.print(zaman.getTur());

    break;

  case GOSTER:
    
    lcd.clear();
    
    lcd.setCursor(0,0);

    lcd.print("Tur Sayisi:");

    lcd.print(zaman.getTur());

    break;

  
  default:
    break;
  }



}


