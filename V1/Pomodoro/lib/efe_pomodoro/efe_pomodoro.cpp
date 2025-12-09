#include "efe_pomodoro.h"
#include <LiquidCrystal_I2C.h>

void Pins::begin(){
    pinMode(Stop,INPUT_PULLUP);
    pinMode(Play,INPUT_PULLUP);
    pinMode(ShowCyc,INPUT_PULLUP);
    pinMode(ResetCyc,INPUT_PULLUP);
}

void lcdprint::lcdbegin(LiquidCrystal_I2C *lcd){

  lcd->init();

  lcd->backlight();

  lcd->setCursor(0,0);

  lcd->print("Pomodoro");

  lcd->setCursor(0,1);

  lcd->print("Designed by Efe");

  delay(2000);
    
}


uint8_t lcdprint::lcdMins(Time *t){

    uint8_t mins=t->calcKalan()/60000;

    return mins;
}

uint8_t lcdprint::lcdSecs(Time *t){

    uint8_t secs=(t->calcKalan() % 60000) / 1000;

    return secs;
}
void lcdprint::lcdShowTur(Time *t,LiquidCrystal_I2C *lcd){

    lcd->clear();

    lcd->setCursor(0,0);

    lcd->print("Tur sayisi:");

    lcd->print(t->getTur());

}
void lcdprint::lcdSettings(LiquidCrystal_I2C *lcd,Time *t){
    lcd->setCursor(0,0);

    uint8_t dk = lcdMins(t);
    if(dk < 10) lcd->print("0"); 
    lcd->print(dk);
    
    lcd->print(":");
    
    // Saniye
    uint8_t sn = lcdSecs(t);
    if(sn < 10) lcd->print("0"); 
    lcd->print(sn);

    
}
uint8_t Time::loadCycle(){

    mypreference.begin("pomodoro",true); // kasa var mı varsa salt oku yoksa oluştur ve oku 

    tur=mypreference.getUChar("tur",0);

    mypreference.end();

    return tur;


}

void Time::setBtnTimes(Pins *p,State_Machine &state , LiquidCrystal_I2C *lcd){
            
    if(digitalRead(p->getPlay())==LOW){
        if(!(durum & BASLAT)){
                btn_basis=millis();
            }
            durum|=BASLAT;durum&=~DURDUR;state=DEVAM;delay(250);while(digitalRead(p->getPlay()) == LOW);
    }

    if(digitalRead(p->getStop())==LOW){
        durum|=DURDUR;durum&=~BASLAT;state=DUR;delay(250);while(digitalRead(p->getStop())==LOW);
        
    }

    if(digitalRead(p->getShowCyc())==LOW){
        durum|=DURDUR;durum &= ~BASLAT;state=GOSTER;delay(250);while(digitalRead(p->getShowCyc())==LOW);
        //durum durma tuşuna basılmış gibi olur state goster modunda olur
    }

    if(digitalRead(p->getResetCyc())==LOW){
        durum|=DURDUR;durum &= ~BASLAT;state=SIFIRLA;setTur(0);saveCycle();delay(250);while(digitalRead(p->getResetCyc())==LOW);
    }
            
    }
    
unsigned long Time::calcKalan(){
    su_an=millis();
    unsigned long gecen_sure= (su_an - btn_basis);
    if(gecen_sure>=MS){
        kalan_sure=0;
    }
    else{
        kalan_sure=MS-gecen_sure;
    }

            
    return kalan_sure;

}
void Time::saveCycle(){

    mypreference.begin("pomodoro",false);

    mypreference.putUChar("tur",tur);

    mypreference.end();
}

void Time::saveSettings(uint8_t ayar){

    mypreference.begin("pomodoro",false);

    mypreference.putUChar("ayar",ayar);

    mypreference.end();
}

uint8_t Time::loadSettings(){

    mypreference.begin("pomodoro",true);

    uint8_t gelen= mypreference.getUChar("ayar",3); 
    
    mypreference.end();

    return gelen;
}