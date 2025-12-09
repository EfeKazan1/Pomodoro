#ifndef EFE_POMODORO_H
#define EFE_POMODORO_H


#include <Arduino.h>
#include <Preferences.h>
#include <LiquidCrystal_I2C.h>


extern uint8_t durum;

#define MS 1500000

#define BASLAT (1<<0)

#define DURDUR (1<<1)


/*
    25 dakikalik sayaçlar olucak
    her 25 dk bittiğinde tur private bir artıcak
    2 dk lik mola sayacı
    sonra tekrardan 25 dk ve tur 
    kapansa bile kaç tur olduğu bilgisi flash memde olcak
    //v2 tur göster-reset tuşu -- durdur-başlat tuşu-lcd ekranda gösterilmeli
*/
//bitwise tuşlar eksik* 
// save load eksik*
// state machineler eksik**

typedef enum {

    DEVAM,
    
    GOSTER,
    
    SIFIRLA,// dur a basınca sayaç durur

    DUR // sistem açıldığında dur modunda başlat tuşuna basıldığında devam a girer ve sayaç başlar 


}State_Machine;


class Pins{

    private:
        const uint8_t SDA;
        const uint8_t SCL;
        const uint8_t Stop;
        const uint8_t Play;
        const uint8_t ShowCyc;
        const uint8_t ResetCyc;

    public:
        Pins(const uint8_t SDA , const uint8_t SCL, const uint8_t Stop, const uint8_t Play , const uint8_t ShowCyc, const uint8_t ResetCyc):SDA(SDA) , SCL(SCL) , Stop(Stop), Play(Play), ShowCyc(ShowCyc), ResetCyc(ResetCyc){
        } // set ve get edildi
        uint8_t getStop(){ return Stop;}
        uint8_t getPlay(){ return Play;}
        uint8_t getShowCyc(){ return ShowCyc;}
        uint8_t getResetCyc(){ return ResetCyc;}

        void begin();
        
};


//fonks eksşk**
class Time{

    private:

        uint8_t tur;

        unsigned long su_an;

        unsigned long onceki_an;

        unsigned long btn_basis;

        // sayac 0 olucak 25 dk bitince (1000 ms 1 sn 1dk 60000 ms 25 dk 1500000ms) yetmez millis de oynatiılamaz 
        /*
        suan- once >= 1.500.000
            tur ++;
            once=suan 
        */
       unsigned long kalan_sure; //1.5M - su an 

        //unsigned long harcanan_sure; //sayac = 60.000 = 1dk; kalan süre= 1.5M - 60.000= kalan 1.440.000 ms /60.000 ;
        //1440 sn = 24 dk /60 = dk
        //1439 sn = 23 dk 59sn % = sn 

        Preferences mypreference;//save load tur;

    public:

        Time(){

            tur = 0;

            su_an = 0;

            onceki_an = 0;

            kalan_sure = 0;

        };

        uint8_t getTur(){return tur;}//yansıtmak için

        void setTur(uint8_t tur){this->tur=tur;}

        uint8_t loadCycle();
    
        void saveCycle();

        void saveSettings(uint8_t ayar);

        uint8_t loadSettings();

        void setBtnTimes(Pins *p,State_Machine &state, LiquidCrystal_I2C *lcd);
            
        unsigned long calcKalan();

        

       
};

class lcdprint{

    public:

    uint8_t lcdMins(Time *t);

    uint8_t lcdSecs(Time *t);

    void lcdSettings(LiquidCrystal_I2C *lcd,Time *t);

    void lcdShowTur(Time *t,LiquidCrystal_I2C *lcd);

    void lcdbegin(LiquidCrystal_I2C *lcd);

};






#endif