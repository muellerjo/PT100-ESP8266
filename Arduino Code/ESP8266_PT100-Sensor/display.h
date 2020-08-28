
#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif


U8G2_SSD1306_128X32_UNIVISION_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // Adafruit Feather ESP8266/32u4 Boards + FeatherWing OLED


void setup_display() {
  // put your setup code here, to run once:

  u8g2.begin();
  //u8g2.setFlipMode(0);
  u8g2.enableUTF8Print();
}

void display_logo() {
  // put your main code here, to run repeatedly:
  u8g2.clearBuffer();          // clear the internal memory
  u8g2.setFont(u8g2_font_crox4hb_tf);
  u8g2.drawStr(0, 15, "MUELLER");
  u8g2.setFont(u8g2_font_etl14thai_t);
  u8g2.drawStr(0,30,"Engineering");
  u8g2.sendBuffer();          // transfer internal memory to the display
  delay(100);
  u8g2.clearBuffer();          // clear the internal memory
  u8g2.setFont(u8g2_font_crox4hb_tf);
  u8g2.drawStr(0, 15, "MUELLER");
  u8g2.setFont(u8g2_font_etl14thai_t);
  u8g2.drawStr(0,30,"Engineering.");
  u8g2.sendBuffer();          // transfer inter
  delay(100);
  u8g2.clearBuffer();          // clear the internal memory
  u8g2.setFont(u8g2_font_crox4hb_tf);
  u8g2.drawStr(0, 15, "MUELLER");
  u8g2.setFont(u8g2_font_etl14thai_t);
  u8g2.drawStr(0,30,"Engineering..");
  u8g2.sendBuffer();          // transfer inter
  delay(100);
  u8g2.clearBuffer();          // clear the internal memory
  u8g2.setFont(u8g2_font_crox4hb_tf);
  u8g2.drawStr(0, 15, "MUELLER");
  u8g2.setFont(u8g2_font_etl14thai_t);
  u8g2.drawStr(0,30,"Engineering...");
  u8g2.sendBuffer();          // transfer inter
  delay(1000);
}




void display_project() {
  // put your main code here, to run repeatedly:
  u8g2.clearBuffer();          // clear the internal memory
  u8g2.setFont(u8g2_font_crox4hb_tf);
  u8g2.drawStr(0, 15, "PT100");
  u8g2.setFont(u8g2_font_etl14thai_t);
  u8g2.drawStr(0,30,"Temperatur-Sensor");
  u8g2.sendBuffer();          // transfer internal memory to the display
  delay(1000);
}



void display_temperature() {
  // put your main code here, to run repeatedly:
  u8g2.clearBuffer();          // clear the internal memory
  u8g2.setFont(u8g2_font_etl14thai_t);
  u8g2.drawStr(0, 10, "PT100 Temperatur:");
  u8g2.setFont(u8g2_font_crox4hb_tf);
  u8g2.drawStr(0,30, temp_char);
  //u8g2.drawUTF8(63, 35, DEGREE_SYMBOL);
  //u8g2.print("\xb0");
  u8g2.sendBuffer();          // transfer internal memory to the display
  //delay(1000);
}
