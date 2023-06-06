#include "SPI.h"               // SPI kütüphanesini ekliyoruz
#include "Wire.h"              // Wire kütüphanesini ekliyoruz
#include "Adafruit_SSD1306.h"  // Adafruit'in SSD1306 kütüphanesini ekliyoruz
#include <Adafruit_GFX.h>

int genislik = 128;  // OLED ekran genişliği (piksel olarak)
int yukseklik = 64;  // OLED ekran yüksekliği (piksel olarak)
int adres = 0x3C;    // 128x64 için 0x3C (bazı modüllerde 0x3D)
Adafruit_SSD1306 ekran(genislik, yukseklik, &Wire);



byte potPin = A0;
int potDeger;
int canLed[3] = { 11, 12, 13 };
int silahLed[3] = { 8, 9, 10 };
const uint8_t PROGMEM uzayMekikI[] = {
  //okay
  B00011000,
  B00111100,
  B10111101,
  B11111111,
  B10100101,
  B10100101,
  B00000000,
  B10000001,
};

const uint8_t PROGMEM uzayCopI[] = {
  //okay
  B00000000,
  B00000000,
  B01010100,
  B00111000,
  B01111100,
  B00111000,
  B01010100,
  B00000000,
};

const uint8_t PROGMEM meteorI[] = {
  B00000000,
  B00010000,
  B00010000,
  B01010100,
  B00111000,
  B01111100,
  B00111000,
  B00010000,
};

const uint8_t PROGMEM yedekCanI[] = {
  //okay
  B00000000,
  B01000100,
  B10101010,
  B10010010,
  B01000100,
  B00101000,
  B00010000,
  B00000000,
};

const uint8_t PROGMEM silahI[] = {
  //okay
  B00000000,
  B00000100,
  B01111111,
  B11111100,
  B10010000,
  B10001000,
  B00000000,
  B00000000,
};

const uint8_t PROGMEM dokunulmazlikI[] = {
  B00010000,
  B00010000,
  B00010000,
  B11111110,
  B00010000,
  B00010000,
  B00010000,
  B00000000,
};

#define asagi_pin 4
#define yukari_pin 5
#define tamam_pin 3
#define atis_pin 6
#define buzzer 17
////
#define puan 14
#define puan1 15
#define puan2 16

byte segment[10] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x7, 0x7F, 0x6F };  //0123456789

int birler = 0;
int onlar = 0;
int yuzler = 0;
////
byte asagi, yukari, tamam, atis;
byte menu = 0;
int isik;
void setup() {
  Serial.begin(9600);

  ////
  pinMode(puan, OUTPUT);
  pinMode(puan1, OUTPUT);
  pinMode(puan2, OUTPUT);
  ////
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(buzzer, OUTPUT);
  randomSeed(analogRead(A0));
  pinMode(asagi_pin, INPUT_PULLUP);
  pinMode(yukari_pin, INPUT_PULLUP);
  pinMode(tamam_pin, INPUT_PULLUP);
  pinMode(atis_pin, INPUT_PULLUP);




  ekran.begin(SSD1306_SWITCHCAPVCC, adres);  // Kütüphaneyi başlatıyoruz
  ekran.setRotation(1);
  ekran.clearDisplay();
  ekran.display();

  //intro
  ekran.setTextSize(1);  // yazı boyutu
  ekran.setTextColor(SSD1306_WHITE);
  ekran.setCursor(7, 50);
  ekran.print("Oyunumuza");
  ekran.setCursor(7, 60);
  ekran.print("Hos");
  ekran.setCursor(7, 70);
  ekran.print("Geldiniz");
  ekran.display();
  delay(2000);
  ekran.clearDisplay();
  ekran.display();
}

void loop() {
  delay(300);
  while (true) {

    isik = analogRead(A1);


    if (isik < 900) {
      ekran.invertDisplay(true);
    } else {
      ekran.invertDisplay(false);
    }

    butonOku();
    if (!asagi) {
      menu++;
      if (menu >= 1) {
        menu = 1;
      }
    }
    if (!yukari) {
      menu--;
      if (menu >= 2) {
        menu = 0;
      }
    }
    if (!tamam) {
      if (menu == 0) {  //seviye1 giriş
        ekran.clearDisplay();
        ekran.writeFillRect(17, 120, 8, 8, 1);
        ekran.display();
        Seviye1();
      } else if (menu == 1) {  //seviye2 giriş
        Seviye2();
      }
    }

    ekran.clearDisplay();
    ekran.setCursor(10, 2);
    ekran.print("Menu");
    ekran.drawLine(0, 15, 127, 15, SSD1306_WHITE);

    ekran.setCursor(10, 60);
    ekran.print("Seviye 1");
    ekran.setCursor(10, 70);
    ekran.print("Seviye 2");

    if (menu == 0) {
      ekran.setCursor(0, 60);
      ekran.print(">");
    } else if (menu == 1) {
      ekran.setCursor(0, 70);
      ekran.print(">");
    }
    ekran.display();
  }
}

void Seviye1() {


  byte matris[16][8] = { { 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 } };
  byte bayrak = 0;
  int sayac = 0;
  int potDegerTut;
  int ledsayac = 2;
  int cansayac = 2;
  int engelSayac = 0;
  int butonDurum = 0;
  byte silahDurum = 0;
  byte canDurum = 0;
  byte canDurum1 = 0;
  byte canDurum2 = 0;
  long ilkZaman = 0;
  long sonZaman;

  long canIlkZaman = 0;
  long canSonZaman;
  byte konum1X, konum1Y;
  byte konum2X, konum2Y;
  byte konum3X, konum3Y;

  byte flag1 = 0;
  long dokunulmazlikIlkZaman = 0;
  long dokunulmazlikSonZaman;

  byte ates1 = 0;
  byte ates2 = 0;
  byte ates3 = 0;
  long skor = 0;
  int flag = 0;

  int dokunulmazlikFlag = 0;



  for (int i = 0; i < 3; i++) {
    digitalWrite(canLed[i], HIGH);
  }
  for (int i = 0; i < 3; i++) {
    digitalWrite(silahLed[i], HIGH);
  }
  while (true) {
    isik = analogRead(A1);

    if (isik < 900) {
      ekran.invertDisplay(true);
    } else {
      ekran.invertDisplay(false);
    }

    potDeger = analogRead(potPin);
    potDeger = map(potDeger, 0, 82, 0, 64);

    if (potDeger % 8 == 7) {
      potDeger++;
    }

    if (potDeger % 8 == 1) {
      potDeger--;
    }

    if (potDeger >= 64) {
      int sayi = potDeger / 64;
      potDeger = potDeger - sayi * 64;
    }

    if (potDeger != potDegerTut) {

      ekran.clearDisplay();

      for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 8; j++) {

          if (matris[i][j] == 1 || matris[i][j] == 4) {
            ekran.drawBitmap(j * 8, i * 8, uzayCopI, 8, 8, WHITE);
          } else if (matris[i][j] == 2 || matris[i][j] == 5 || matris[i][j] == 9) {
            ekran.drawBitmap(j * 8, i * 8, meteorI, 8, 8, WHITE);
          } else if (matris[i][j] == 3) {
            ekran.drawBitmap(j * 8, i * 8, dokunulmazlikI, 8, 8, WHITE);
          } else if (matris[i][j] == 6) {
            ekran.drawBitmap(j * 8, i * 8, yedekCanI, 8, 8, WHITE);
          } else if (matris[i][j] == 7) {
            ekran.drawBitmap(j * 8, i * 8, silahI, 8, 8, WHITE);
          }
        }
      }

      ekran.drawBitmap(potDeger, 120, uzayMekikI, 8, 8, WHITE);
      ekran.display();
    }
    potDegerTut = potDeger;

    int konum[4] = { -1, -1, -1, -1 };

    sonZaman = millis();

    if (sonZaman - ilkZaman > 1000) {
      bayrak = 1;

      if (sayac % 3 == 0) {

        if (engelSayac != 14) {
          objeOlustur(konum);
          for (int i = 0; i < 4 && engelSayac != 14; i++) {
            int rnd = random(1, 6);

            if (konum[i] != -1) {
              matris[0][konum[i] - 1] = rnd;
              if (rnd == 1 || rnd == 4 || rnd == 2 || rnd == 5) {
                engelSayac++;
              }
            }
          }
        } else {
          byte rnd = random(0, 8);
          matris[0][rnd] = 6;
          byte rnd2 = random(0, 8);
          while (rnd == rnd2) {
            rnd2 = random(0, 8);
          }
          matris[0][rnd2] = 7;
          engelSayac = 0;
        }
      }
      if (sayac % 3 == 1 || sayac % 3 == 2) {
        matris[0][0] = 0;
        matris[0][1] = 0;
        matris[0][2] = 0;
        matris[0][3] = 0;
        matris[0][4] = 0;
        matris[0][5] = 0;
        matris[0][6] = 0;
        matris[0][7] = 0;
      }
      for (int i = 15; i >= 1; i--) {

        for (int j = 0; j < 8; j++) {
          matris[i][j] = matris[i - 1][j];
        }
      }
      matris[0][0] = 0;
      matris[0][1] = 0;
      matris[0][2] = 0;
      matris[0][3] = 0;
      matris[0][4] = 0;
      matris[0][5] = 0;
      matris[0][6] = 0;
      matris[0][7] = 0;

      if (ates1 == 1) {
        konum1X--;
        if (matris[konum1X][konum1Y] == 1 || matris[konum1X][konum1Y] == 4 || matris[konum1X][konum1Y] == 2 || matris[konum1X][konum1Y] == 5 || matris[konum1X][konum1Y] == 9) {
          if (matris[konum1X][konum1Y] == 1 || matris[konum1X][konum1Y] == 4 || matris[konum1X][konum1Y] == 9) {
            ates1 = 0;
            matris[konum1X][konum1Y] = 0;
          }

          if (matris[konum1X][konum1Y] == 2 || matris[konum1X][konum1Y] == 5) {
            matris[konum1X][konum1Y] = 9;
            ates1 = 0;
          }
        }


        if (matris[konum1X + 1][konum1Y] == 1 || matris[konum1X + 1][konum1Y] == 4 || matris[konum1X + 1][konum1Y] == 2 || matris[konum1X + 1][konum1Y] == 5 || matris[konum1X + 1][konum1Y] == 9) {
          if (matris[konum1X + 1][konum1Y] == 1 || matris[konum1X + 1][konum1Y] == 4 || matris[konum1X + 1][konum1Y] == 9) {
            ates1 = 0;
            matris[konum1X + 1][konum1Y] = 0;
          }

          if (matris[konum1X + 1][konum1Y] == 2 || matris[konum1X + 1][konum1Y] == 5) {
            matris[konum1X + 1][konum1Y] = 9;
            ates1 = 0;
          }
        }
      }

      if (ates2 == 1) {
        konum2X--;
        if (matris[konum2X][konum2Y] == 1 || matris[konum2X][konum2Y] == 4 || matris[konum2X][konum2Y] == 2 || matris[konum2X][konum2Y] == 5 || matris[konum2X][konum2Y] == 9) {
          if (matris[konum2X][konum2Y] == 1 || matris[konum2X][konum2Y] == 4 || matris[konum2X][konum2Y] == 9) {
            ates2 = 0;
            matris[konum2X][konum2Y] = 0;
          }
          if (matris[konum2X][konum2Y] == 2 || matris[konum2X][konum2Y] == 5) {
            ates2 = 0;
            matris[konum2X][konum2Y] = 9;
          }
        }

        if (matris[konum2X + 1][konum2Y] == 1 || matris[konum2X + 1][konum2Y] == 4 || matris[konum2X + 1][konum2Y] == 2 || matris[konum2X + 1][konum2Y] == 5 || matris[konum2X + 1][konum2Y] == 9) {

          if (matris[konum2X + 1][konum2Y] == 1 || matris[konum2X + 1][konum2Y] == 4 || matris[konum2X + 1][konum2Y] == 9) {
            ates2 = 0;
            matris[konum2X + 1][konum2Y] = 0;
          }

          if (matris[konum2X + 1][konum2Y] == 2 || matris[konum2X + 1][konum2Y] == 5) {
            ates2 = 0;
            matris[konum2X + 1][konum2Y] = 9;
          }
        }
      }

      if (ates3 == 1) {
        konum3X--;
        if (matris[konum3X][konum3Y] == 1 || matris[konum3X][konum3Y] == 4 || matris[konum3X][konum3Y] == 2 || matris[konum3X][konum3Y] == 5 || matris[konum3X][konum3Y] == 9) {
          if (matris[konum3X][konum3Y] == 1 || matris[konum3X][konum3Y] == 4 || matris[konum3X][konum3Y] == 9) {
            ates3 = 0;
            matris[konum3X][konum3Y] = 0;
          }
          if (matris[konum3X][konum3Y] == 2 || matris[konum3X][konum3Y] == 5) {
            ates3 = 0;
            matris[konum3X][konum3Y] = 9;
          }
        }

        if (matris[konum3X + 1][konum3Y] == 1 || matris[konum3X + 1][konum3Y] == 4 || matris[konum3X + 1][konum3Y] == 2 || matris[konum3X + 1][konum3Y] == 5 || matris[konum3X + 1][konum3Y] == 9) {
          if (matris[konum3X + 1][konum3Y] == 1 || matris[konum3X + 1][konum3Y] == 4 || matris[konum3X + 1][konum3Y] == 9) {
            ates3 = 0;
            matris[konum3X + 1][konum3Y] = 0;
          }

          if (matris[konum3X + 1][konum3Y] == 2 || matris[konum3X + 1][konum3Y] == 5) {
            ates3 = 0;
            matris[konum3X + 1][konum3Y] = 9;
          }
        }
      }

      ilkZaman = sonZaman;

      sayac++;




      digitalWrite(puan2, LOW);
      shiftOut(puan, puan1, MSBFIRST, ~segment[birler]);
      shiftOut(puan, puan1, MSBFIRST, ~segment[onlar]);
      shiftOut(puan, puan1, MSBFIRST, ~segment[yuzler]);
      digitalWrite(puan2, HIGH);

      birler++;
      if (birler > 9) {
        birler = 0;
        onlar++;

        if (onlar > 9) {
          onlar = 0;
          yuzler++;

          if (yuzler > 9) {
            yuzler = 0;
          }
        }
      }

      if (dokunulmazlikFlag != 0) {
        dokunulmazlikFlag++;
      }

      if (flag != 0) {
        flag++;
      }
    }

    if (bayrak == 1) {

      ekran.clearDisplay();

      for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 8; j++) {

          if (matris[i][j] == 1 || matris[i][j] == 4) {
            ekran.drawBitmap(j * 8, i * 8, uzayCopI, 8, 8, WHITE);
          } else if (matris[i][j] == 2 || matris[i][j] == 5 || matris[i][j] == 9) {
            ekran.drawBitmap(j * 8, i * 8, meteorI, 8, 8, WHITE);
          } else if (matris[i][j] == 3) {
            ekran.drawBitmap(j * 8, i * 8, dokunulmazlikI, 8, 8, WHITE);
          } else if (matris[i][j] == 6) {
            ekran.drawBitmap(j * 8, i * 8, yedekCanI, 8, 8, WHITE);
          } else if (matris[i][j] == 7) {
            ekran.drawBitmap(j * 8, i * 8, silahI, 8, 8, WHITE);
          }
        }
      }

      if (ates1 == 1) {
        // ekran.writeFillRect(konum1Y*8,konum1X*8,8,8,1);
        ekran.drawCircle(konum1Y * 8 + 3.5, konum1X * 8 + 3.5, 1, WHITE);
      }

      if (ates2 == 1) {
        // ekran.writeFillRect(konum2Y*8,konum2X*8,8,8,1);
        ekran.drawCircle(konum2Y * 8 + 3.5, konum2X * 8 + 3.5, 1, WHITE);
      }

      if (ates3 == 1) {
        //  ekran.writeFillRect(konum3Y*8,konum3X*8,8,8,1);
        ekran.drawCircle(konum3Y * 8 + 3.5, konum3X * 8 + 3.5, 1, WHITE);
      }


      ekran.drawBitmap(potDeger, 120, uzayMekikI, 8, 8, WHITE);
      ekran.display();
    }


    if (matris[15][potDeger / 8] == 7 && silahDurum == 0) {

      if (ledsayac <= 1 && ledsayac >= -1) {
        ledsayac++;
      }
      digitalWrite(silahLed[ledsayac], HIGH);
      silahDurum = 1;
    }
    if (matris[15][potDeger / 8] != 7 && silahDurum == 1) {
      silahDurum = 0;
    }


    atis = digitalRead(atis_pin);
    if (!atis && butonDurum == 0) {
      digitalWrite(silahLed[ledsayac], LOW);

      if (ledsayac <= 2 && ledsayac >= 0) {
        if (ates1 == 1) {
          konum3X = 14;  //////
          konum3Y = potDeger / 8;
          ates3 = 1;
        }

        else {
          konum1X = 14;  //////
          konum1Y = potDeger / 8;
          ates1 = 1;  //////
        }


        ledsayac--;
      }
      butonDurum = 1;
    }
    if (butonDurum == 1 && atis) {
      butonDurum = 2;
    }
    if (butonDurum == 2 && !atis) {
      digitalWrite(silahLed[ledsayac], LOW);

      if (ledsayac <= 2 && ledsayac >= 0) {

        konum2X = 14;  //////
        konum2Y = potDeger / 8;
        ates2 = 1;  //////
        ledsayac--;
      }
      butonDurum = 3;
    }
    if (butonDurum == 3 && atis) {
      butonDurum = 0;
    }






    if (matris[15][potDeger / 8] == 6 && canDurum == 0) {
      if (cansayac <= 1 && cansayac >= 0) {
        cansayac++;
      }
      digitalWrite(canLed[cansayac], HIGH);
      canDurum = 1;
    }
    if (matris[15][potDeger / 8] != 6 && canDurum == 1) {
      canDurum = 0;
    }




    if (matris[15][potDeger / 8] == 3 && dokunulmazlikFlag == 0) {
      dokunulmazlikFlag = 1;
    }


    if (flag == 0 && dokunulmazlikFlag == 0) {


      if (matris[15][potDeger / 8] == 1 || matris[15][potDeger / 8] == 4 || matris[15][potDeger / 8] == 2 || matris[15][potDeger / 8] == 5 || matris[15][potDeger / 8] == 9) {
        tone(buzzer, 100, 150);


        flag = 1;
      }


      //uzayçöpü
      if ((matris[15][potDeger / 8] == 1 || matris[15][potDeger / 8] == 4) && canDurum1 == 0) {
        digitalWrite(canLed[cansayac], LOW);

        if (cansayac <= 2 && cansayac >= 0) {
          cansayac--;
        }
        canDurum1 = 1;
      }
      if (matris[15][potDeger / 8] != 1 && matris[15][potDeger / 8] != 4 && canDurum1 == 1) {
        canDurum1 = 0;
      }

      //meteor
      if ((matris[15][potDeger / 8] == 2 || matris[15][potDeger / 8] == 5 || matris[15][potDeger / 8] == 9) && canDurum2 == 0) {

        digitalWrite(canLed[cansayac], LOW);
        if (cansayac <= 2 && cansayac >= 0) {
          cansayac--;
        }
        canDurum2 = 1;
      }
      if (matris[15][potDeger / 8] != 2 && matris[15][potDeger / 8] != 5 && matris[15][potDeger / 8] != 9 && canDurum2 == 1) {
        canDurum2 = 0;
      }
    }


    if (flag >= 5) {
      flag = 0;
    }

    if (dokunulmazlikFlag >= 5) {
      dokunulmazlikFlag = 0;
    }





    if (cansayac == -1) {


      gameOver();

      break;
    }
  }
}


void Seviye2() {
  byte matris[16][8] = { { 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 } };
  byte flag = 0;
  long sonZaman;
  long ilkZaman = 0;

  long ilkZaman2 = 0;
  long sonZaman2;
  long canSonZaman;
  long canIlkZaman = 0;
  float ekranHiz = 1000;
  byte bayrak = 0;
  int sayac = 0;
  int potDegerTut;
  int ledsayac = 2;
  int cansayac = 2;
  int engelSayac = 0;
  int butonDurum = 0;
  byte silahDurum = 0;
  byte canDurum = 0;
  byte canDurum1 = 0;
  byte canDurum2 = 0;
  byte konum1X, konum1Y;
  byte konum2X, konum2Y;
  byte konum3X, konum3Y;
  long skor = 0;

  byte ates1 = 0;
  byte ates2 = 0;
  byte ates3 = 0;
  int dokunulmazlikFlag = 0;
  for (int i = 0; i < 3; i++) {
    digitalWrite(canLed[i], HIGH);
  }
  for (int i = 0; i < 3; i++) {
    digitalWrite(silahLed[i], HIGH);
  }
  while (true) {
    isik = analogRead(A1);

    if (isik < 900) {
      ekran.invertDisplay(true);
    } else {
      ekran.invertDisplay(false);
    }

    sonZaman2 = millis();

    if (sonZaman2 - ilkZaman2 >= 10000) {
      ekranHiz = ekranHiz - ekranHiz * 0.2;
      ilkZaman2 = sonZaman2;
    }

    potDeger = analogRead(potPin);
    potDeger = map(potDeger, 0, 82, 0, 64);

    if (potDeger % 8 == 7) {
      potDeger++;
    }

    if (potDeger % 8 == 1) {
      potDeger--;
    }

    if (potDeger >= 64) {
      int sayi = potDeger / 64;
      potDeger = potDeger - sayi * 64;
    }

    if (potDeger != potDegerTut) {

      ekran.clearDisplay();

      for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 8; j++) {

          if (matris[i][j] == 1 || matris[i][j] == 4) {
            ekran.drawBitmap(j * 8, i * 8, uzayCopI, 8, 8, WHITE);
          } else if (matris[i][j] == 2 || matris[i][j] == 5 || matris[i][j] == 9) {
            ekran.drawBitmap(j * 8, i * 8, meteorI, 8, 8, WHITE);
          } else if (matris[i][j] == 3) {
            ekran.drawBitmap(j * 8, i * 8, dokunulmazlikI, 8, 8, WHITE);
          } else if (matris[i][j] == 6) {
            ekran.drawBitmap(j * 8, i * 8, yedekCanI, 8, 8, WHITE);
          } else if (matris[i][j] == 7) {
            ekran.drawBitmap(j * 8, i * 8, silahI, 8, 8, WHITE);
          }
        }
      }

      ekran.drawBitmap(potDeger, 120, uzayMekikI, 8, 8, WHITE);
      ekran.display();
    }
    potDegerTut = potDeger;

    int konum[4] = { -1, -1, -1, -1 };

    sonZaman = millis();

    if (sonZaman - ilkZaman > ekranHiz) {
      bayrak = 1;

      if (sayac % 3 == 0) {

        if (engelSayac != 14) {
          objeOlustur(konum);
          for (int i = 0; i < 4 && engelSayac != 14; i++) {
            int rnd = random(1, 6);

            if (konum[i] != -1) {
              matris[0][konum[i] - 1] = rnd;
              if (rnd == 1 || rnd == 4 || rnd == 2 || rnd == 5) {
                engelSayac++;
              }
            }
          }
        } else {
          byte rnd = random(0, 8);
          matris[0][rnd] = 6;
          byte rnd2 = random(0, 8);
          while (rnd == rnd2) {
            rnd2 = random(0, 8);
          }
          matris[0][rnd2] = 7;
          engelSayac = 0;
        }
      }
      if (sayac % 3 == 1 || sayac % 3 == 2) {
        matris[0][0] = 0;
        matris[0][1] = 0;
        matris[0][2] = 0;
        matris[0][3] = 0;
        matris[0][4] = 0;
        matris[0][5] = 0;
        matris[0][6] = 0;
        matris[0][7] = 0;
      }
      for (int i = 15; i >= 1; i--) {

        for (int j = 0; j < 8; j++) {
          matris[i][j] = matris[i - 1][j];
        }
      }
      matris[0][0] = 0;
      matris[0][1] = 0;
      matris[0][2] = 0;
      matris[0][3] = 0;
      matris[0][4] = 0;
      matris[0][5] = 0;
      matris[0][6] = 0;
      matris[0][7] = 0;



      if (ates1 == 1) {
        konum1X--;
        if (matris[konum1X][konum1Y] == 1 || matris[konum1X][konum1Y] == 4 || matris[konum1X][konum1Y] == 2 || matris[konum1X][konum1Y] == 5 || matris[konum1X][konum1Y] == 9) {
          if (matris[konum1X][konum1Y] == 1 || matris[konum1X][konum1Y] == 4 || matris[konum1X][konum1Y] == 9) {
            ates1 = 0;
            matris[konum1X][konum1Y] = 0;
          }

          if (matris[konum1X][konum1Y] == 2 || matris[konum1X][konum1Y] == 5) {
            matris[konum1X][konum1Y] = 9;
            ates1 = 0;
          }
        }


        if (matris[konum1X + 1][konum1Y] == 1 || matris[konum1X + 1][konum1Y] == 4 || matris[konum1X + 1][konum1Y] == 2 || matris[konum1X + 1][konum1Y] == 5 || matris[konum1X + 1][konum1Y] == 9) {
          if (matris[konum1X + 1][konum1Y] == 1 || matris[konum1X + 1][konum1Y] == 4 || matris[konum1X + 1][konum1Y] == 9) {
            ates1 = 0;
            matris[konum1X + 1][konum1Y] = 0;
          }

          if (matris[konum1X + 1][konum1Y] == 2 || matris[konum1X + 1][konum1Y] == 5) {
            matris[konum1X + 1][konum1Y] = 9;
            ates1 = 0;
          }
        }
      }

      if (ates2 == 1) {
        konum2X--;
        if (matris[konum2X][konum2Y] == 1 || matris[konum2X][konum2Y] == 4 || matris[konum2X][konum2Y] == 2 || matris[konum2X][konum2Y] == 5 || matris[konum2X][konum2Y] == 9) {
          if (matris[konum2X][konum2Y] == 1 || matris[konum2X][konum2Y] == 4 || matris[konum2X][konum2Y] == 9) {
            ates2 = 0;
            matris[konum2X][konum2Y] = 0;
          }
          if (matris[konum2X][konum2Y] == 2 || matris[konum2X][konum2Y] == 5) {
            ates2 = 0;
            matris[konum2X][konum2Y] = 9;
          }
        }

        if (matris[konum2X + 1][konum2Y] == 1 || matris[konum2X + 1][konum2Y] == 4 || matris[konum2X + 1][konum2Y] == 2 || matris[konum2X + 1][konum2Y] == 5 || matris[konum2X + 1][konum2Y] == 9) {

          if (matris[konum2X + 1][konum2Y] == 1 || matris[konum2X + 1][konum2Y] == 4 || matris[konum2X + 1][konum2Y] == 9) {
            ates2 = 0;
            matris[konum2X + 1][konum2Y] = 0;
          }

          if (matris[konum2X + 1][konum2Y] == 2 || matris[konum2X + 1][konum2Y] == 5) {
            ates2 = 0;
            matris[konum2X + 1][konum2Y] = 9;
          }
        }
      }

      if (ates3 == 1) {
        konum3X--;
        if (matris[konum3X][konum3Y] == 1 || matris[konum3X][konum3Y] == 4 || matris[konum3X][konum3Y] == 2 || matris[konum3X][konum3Y] == 5 || matris[konum3X][konum3Y] == 9) {
          if (matris[konum3X][konum3Y] == 1 || matris[konum3X][konum3Y] == 4 || matris[konum3X][konum3Y] == 9) {
            ates3 = 0;
            matris[konum3X][konum3Y] = 0;
          }
          if (matris[konum3X][konum3Y] == 2 || matris[konum3X][konum3Y] == 5) {
            ates3 = 0;
            matris[konum3X][konum3Y] = 9;
          }
        }

        if (matris[konum3X + 1][konum3Y] == 1 || matris[konum3X + 1][konum3Y] == 4 || matris[konum3X + 1][konum3Y] == 2 || matris[konum3X + 1][konum3Y] == 5 || matris[konum3X + 1][konum3Y] == 9) {
          if (matris[konum3X + 1][konum3Y] == 1 || matris[konum3X + 1][konum3Y] == 4 || matris[konum3X + 1][konum3Y] == 9) {
            ates3 = 0;
            matris[konum3X + 1][konum3Y] = 0;
          }

          if (matris[konum3X + 1][konum3Y] == 2 || matris[konum3X + 1][konum3Y] == 5) {
            ates3 = 0;
            matris[konum3X + 1][konum3Y] = 9;
          }
        }
      }




      ilkZaman = sonZaman;

      sayac++;



      digitalWrite(puan2, LOW);
      shiftOut(puan, puan1, MSBFIRST, ~segment[birler]);
      shiftOut(puan, puan1, MSBFIRST, ~segment[onlar]);
      shiftOut(puan, puan1, MSBFIRST, ~segment[yuzler]);
      digitalWrite(puan2, HIGH);

      birler++;
      if (birler > 9) {
        birler = 0;
        onlar++;

        if (onlar > 9) {
          onlar = 0;
          yuzler++;

          if (yuzler > 9) {
            yuzler = 0;
          }
        }
      }

      if (dokunulmazlikFlag != 0) {
        dokunulmazlikFlag++;
      }

      if (flag != 0) {
        flag++;
      }
    }

    if (bayrak == 1) {

      ekran.clearDisplay();

      for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 8; j++) {

          if (matris[i][j] == 1 || matris[i][j] == 4) {
            ekran.drawBitmap(j * 8, i * 8, uzayCopI, 8, 8, WHITE);
          } else if (matris[i][j] == 2 || matris[i][j] == 5 || matris[i][j] == 9) {
            ekran.drawBitmap(j * 8, i * 8, meteorI, 8, 8, WHITE);
          } else if (matris[i][j] == 3) {
            ekran.drawBitmap(j * 8, i * 8, dokunulmazlikI, 8, 8, WHITE);
          } else if (matris[i][j] == 6) {
            ekran.drawBitmap(j * 8, i * 8, yedekCanI, 8, 8, WHITE);
          } else if (matris[i][j] == 7) {
            ekran.drawBitmap(j * 8, i * 8, silahI, 8, 8, WHITE);
          }
        }
      }


      if (ates1 == 1) {
        //ekran.writeFillRect(konum1Y*8,konum1X*8,8,8,1);
        ekran.drawCircle(konum1Y * 8 + 3.5, konum1X * 8 + 3.5, 1, WHITE);
      }

      if (ates2 == 1) {
        // ekran.writeFillRect(konum2Y*8,konum2X*8,8,8,1);
        ekran.drawCircle(konum2Y * 8 + 3.5, konum2X * 8 + 3.5, 1, WHITE);
      }

      if (ates3 == 1) {
        //ekran.writeFillRect(konum3Y*8,konum3X*8,8,8,1);
        ekran.drawCircle(konum3Y * 8 + 3.5, konum3X * 8 + 3.5, 1, WHITE);
      }

      ekran.drawBitmap(potDeger, 120, uzayMekikI, 8, 8, WHITE);


      ekran.display();
    }

    atis = digitalRead(atis_pin);
    if (matris[15][potDeger / 8] == 7 && silahDurum == 0) {

      if (ledsayac <= 1 && ledsayac >= -1) {
        ledsayac++;
      }
      digitalWrite(silahLed[ledsayac], HIGH);
      silahDurum = 1;
    }
    if (matris[15][potDeger / 8] != 7 && silahDurum == 1) {
      silahDurum = 0;
    }

    if (!atis && butonDurum == 0) {
      digitalWrite(silahLed[ledsayac], LOW);

      if (ledsayac <= 2 && ledsayac >= 0) {

        if (ates1 == 1) {
          konum3X = 14;  //////
          konum3Y = potDeger / 8;
          ates3 = 1;
        }

        else {
          konum1X = 14;  //////
          konum1Y = potDeger / 8;
          ates1 = 1;  //////
        }

        ledsayac--;
      }
      butonDurum = 1;
    }
    if (butonDurum == 1 && atis) {
      butonDurum = 2;
    }
    if (butonDurum == 2 && !atis) {
      digitalWrite(silahLed[ledsayac], LOW);

      if (ledsayac <= 2 && ledsayac >= 0) {
        konum2X = 14;  //////
        konum2Y = potDeger / 8;
        ates2 = 1;  //////

        ledsayac--;
      }
      butonDurum = 3;
    }
    if (butonDurum == 3 && atis) {
      butonDurum = 0;
    }



    if (matris[15][potDeger / 8] == 6 && canDurum == 0) {
      if (cansayac <= 1 && cansayac >= 0) {
        cansayac++;
      }
      digitalWrite(canLed[cansayac], HIGH);
      canDurum = 1;
    }
    if (matris[15][potDeger / 8] != 6 && canDurum == 1) {
      canDurum = 0;
    }



    if (matris[15][potDeger / 8] == 3 && dokunulmazlikFlag == 0) {
      dokunulmazlikFlag = 1;
    }


    if (flag == 0 && dokunulmazlikFlag == 0) {


      //uzayçöpü


      if (matris[15][potDeger / 8] == 1 || matris[15][potDeger / 8] == 4 || matris[15][potDeger / 8] == 2 || matris[15][potDeger / 8] == 5 || matris[15][potDeger / 8] == 9) {
        flag = 1;
        tone(buzzer, 100, 150);
      }

      if ((matris[15][potDeger / 8] == 1 || matris[15][potDeger / 8] == 4) && canDurum1 == 0) {

        digitalWrite(canLed[cansayac], LOW);
        if (cansayac <= 2 && cansayac >= 0) {
          cansayac--;
        }
        canDurum1 = 1;
      }
      if (matris[15][potDeger / 8] != 1 && matris[15][potDeger / 8] != 4 && canDurum1 == 1) {
        canDurum1 = 0;
      }

      //meteor
      if ((matris[15][potDeger / 8] == 2 || matris[15][potDeger / 8] == 5 || matris[15][potDeger / 8] == 9) && canDurum2 == 0) {

        digitalWrite(canLed[cansayac], LOW);
        if (cansayac <= 2 && cansayac >= 0) {
          cansayac--;
        }
        canDurum2 = 1;
      }
      if (matris[15][potDeger / 8] != 2 && matris[15][potDeger / 8] != 5 && matris[15][potDeger / 8] != 9 && canDurum2 == 1) {
        canDurum2 = 0;
      }
    }


    if (flag >= 5) {
      flag = 0;
    }

    if (dokunulmazlikFlag >= 5) {
      dokunulmazlikFlag = 0;
    }


    if (cansayac == -1) {
      gameOver();
      break;
    }
  }
}

void objeOlustur(int konum[4]) {

  int randomDeger;
  int randNumber;
  int randNumber2;

  randNumber = random(1, 5);
  randNumber2 = random(1, 9);

  konum[0] = randNumber2;
  int j = 1, k = 1;

  for (int i = 1; i < randNumber; i++) {
    int sayi1 = konum[0] + j * 2;
    int sayi2 = konum[0] - k * 2;
    if (sayi1 < 9) {
      konum[i] = sayi1;
      j++;
    }

    else {
      konum[i] = sayi2;
      k++;
    }
  }
}

void butonOku() {
  asagi = digitalRead(asagi_pin);
  yukari = digitalRead(yukari_pin);
  tamam = digitalRead(tamam_pin);
}

void gameOver() {


  ekran.clearDisplay();
  ekran.setCursor(20, 60);
  ekran.print("GAME");
  ekran.setCursor(20, 70);
  ekran.print("OVER");
  ekran.display();
  for (int i = 0; i < 3; i++) {
    digitalWrite(canLed[i], HIGH);
  }
  for (int i = 0; i < 3; i++) {
    digitalWrite(silahLed[i], HIGH);
  }
  delay(100);
  for (int i = 0; i < 3; i++) {
    digitalWrite(canLed[i], LOW);
  }
  for (int i = 0; i < 3; i++) {
    digitalWrite(silahLed[i], LOW);
  }
  delay(100);
  for (int i = 0; i < 3; i++) {
    digitalWrite(canLed[i], HIGH);
  }
  for (int i = 0; i < 3; i++) {
    digitalWrite(silahLed[i], HIGH);
  }
  delay(100);
  for (int i = 0; i < 3; i++) {
    digitalWrite(canLed[i], LOW);
  }
  for (int i = 0; i < 3; i++) {
    digitalWrite(silahLed[i], LOW);
  }
  delay(100);
  for (int i = 0; i < 3; i++) {
    digitalWrite(canLed[i], HIGH);
  }
  for (int i = 0; i < 3; i++) {
    digitalWrite(silahLed[i], HIGH);
  }
  delay(100);
  for (int i = 0; i < 3; i++) {
    digitalWrite(canLed[i], LOW);
  }
  for (int i = 0; i < 3; i++) {
    digitalWrite(silahLed[i], LOW);
  }
  delay(100);
  for (int i = 0; i < 3; i++) {
    digitalWrite(canLed[i], HIGH);
  }
  for (int i = 0; i < 3; i++) {
    digitalWrite(silahLed[i], HIGH);
  }
  delay(100);
  for (int i = 0; i < 3; i++) {
    digitalWrite(canLed[i], LOW);
  }
  for (int i = 0; i < 3; i++) {
    digitalWrite(silahLed[i], LOW);
  }
  delay(100);
  for (int i = 0; i < 3; i++) {
    digitalWrite(canLed[i], HIGH);
  }
  for (int i = 0; i < 3; i++) {
    digitalWrite(silahLed[i], HIGH);
  }
  delay(100);
  for (int i = 0; i < 3; i++) {
    digitalWrite(canLed[i], LOW);
  }
  for (int i = 0; i < 3; i++) {
    digitalWrite(silahLed[i], LOW);
  }

  birler = 0;
  onlar = 0;
  yuzler = 0;
  digitalWrite(puan2, LOW);
  shiftOut(puan, puan1, MSBFIRST, ~segment[birler]);
  shiftOut(puan, puan1, MSBFIRST, ~segment[onlar]);
  shiftOut(puan, puan1, MSBFIRST, ~segment[yuzler]);
  digitalWrite(puan2, HIGH);
}