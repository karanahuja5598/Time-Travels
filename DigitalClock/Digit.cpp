#include "Digit.h"

const byte sA = 0;
const byte sB = 1;
const byte sC = 2;
const byte sD = 3;
const byte sE = 4;
const byte sF = 5;
const byte sG = 6;
const int segHeight = 6;
const int segWidth = segHeight;
const uint16_t height = 31;
const uint16_t width = 63;

byte digitBits[] = {
  B11111100, 
  B01100000, 
  B11011010, 
  B11110010, 
  B01100110, 
  B10110110, 
  B10111110, 
  B11100000, 
  B11111110, 
  B11110110, 
};

uint16_t black;

Digit::Digit(PxMATRIX* d, byte value, uint16_t xo, uint16_t yo, uint16_t color) {
  _display = d;
  _value = value;
  xOffset = xo;
  yOffset = yo;
  _color = color;
}

byte Digit::Value() {
  return _value;
}
void Digit::drawPixel(uint16_t x, uint16_t y, uint16_t c)
{
  _display->drawPixel(xOffset + x, height - (y + yOffset), c);
}

void Digit::drawLine(uint16_t x, uint16_t y, uint16_t x2, uint16_t y2, uint16_t c)
{
  _display->drawLine(xOffset + x, height - (y + yOffset), xOffset + x2, height - (y2 + yOffset), c);
}

void Digit::drawFillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t c)
{
  _display->fillRect(xOffset + x, height - (y + yOffset), w,h, c);
}

void Digit::DrawColon(uint16_t c)
{

  drawFillRect(-3, segHeight-1, 2,2, c);
  drawFillRect(-3, segHeight+1+3, 2,2, c);
}

void Digit::drawSeg(byte seg)
{
  switch (seg) {
    case sA: drawLine(1, segHeight * 2 + 2, segWidth, segHeight * 2 + 2, _color); break;
    case sB: drawLine(segWidth + 1, segHeight * 2 + 1, segWidth + 1, segHeight + 2, _color); break;
    case sC: drawLine(segWidth + 1, 1, segWidth + 1, segHeight, _color); break;
    case sD: drawLine(1, 0, segWidth, 0, _color); break;
    case sE: drawLine(0, 1, 0, segHeight, _color); break;
    case sF: drawLine(0, segHeight * 2 + 1, 0, segHeight + 2, _color); break;
    case sG: drawLine(1, segHeight + 1, segWidth, segHeight + 1, _color); break;
  }
}

void Digit::Draw(byte value) {
  byte pattern = digitBits[value];
  if (bitRead(pattern, 7)) drawSeg(sA);
  if (bitRead(pattern, 6)) drawSeg(sB);
  if (bitRead(pattern, 5)) drawSeg(sC);
  if (bitRead(pattern, 4)) drawSeg(sD);
  if (bitRead(pattern, 3)) drawSeg(sE);
  if (bitRead(pattern, 2)) drawSeg(sF);
  if (bitRead(pattern, 1)) drawSeg(sG);
  _value = value;
}

void Digit::Morph2() {
 
  for (int i = 0; i <= segWidth; i++)
  {
    if (i < segWidth) {
      drawPixel(segWidth - i, segHeight * 2 + 2, _color);
      drawPixel(segWidth - i, segHeight + 1, _color);
      drawPixel(segWidth - i, 0, _color);
    }

    drawLine(segWidth + 1 - i, 1, segWidth + 1 - i, segHeight, black);
    drawLine(segWidth - i, 1, segWidth - i, segHeight, _color);
    delay(animSpeed);
  }
}

void Digit::Morph3() {
 
  for (int i = 0; i <= segWidth; i++)
  {
    drawLine(0 + i, 1, 0 + i, segHeight, black);
    drawLine(1 + i, 1, 1 + i, segHeight, _color);
    delay(animSpeed);
  }
}

void Digit::Morph4() {
  
  for (int i = 0; i < segWidth; i++)
  {
    drawPixel(segWidth - i, segHeight * 2 + 2, black); // Erase A
    drawPixel(0, segHeight * 2 + 1 - i, _color); // Draw as F
    drawPixel(1 + i, 0, black); // Erase D
    delay(animSpeed);
  }
}

void Digit::Morph5() {
  
  for (int i = 0; i < segWidth; i++)
  {
    drawPixel(segWidth + 1, segHeight + 2 + i, black); // Erase B
    drawPixel(segWidth - i, segHeight * 2 + 2, _color); // Draw as A
    drawPixel(segWidth - i, 0, _color); // Draw D
    delay(animSpeed);
  }
}

void Digit::Morph6() {
  
  for (int i = 0; i <= segWidth; i++)
  {
    // Move C right to left
    drawLine(segWidth - i, 1, segWidth - i, segHeight, _color);
    if (i > 0) drawLine(segWidth - i + 1, 1, segWidth - i + 1, segHeight, black);
    delay(animSpeed);
  }
}

void Digit::Morph7() {

  for (int i = 0; i <= (segWidth + 1); i++)
  {
    
    drawLine(0 + i - 1, 1, 0 + i - 1, segHeight, black);
    drawLine(0 + i, 1, 0 + i, segHeight, _color);

   
    drawLine(0 + i - 1, segHeight * 2 + 1, 0 + i - 1, segHeight + 2, black);
    drawLine(0 + i, segHeight * 2 + 1, 0 + i, segHeight + 2, _color);


    drawPixel(1 + i, 0, black); 
    drawPixel(1 + i, segHeight + 1, black); 
    delay(animSpeed);
  }
}

void Digit::Morph8() {

  for (int i = 0; i <= segWidth; i++)
  {

    drawLine(segWidth - i, segHeight * 2 + 1, segWidth - i, segHeight + 2, _color);
    if (i > 0) drawLine(segWidth - i + 1, segHeight * 2 + 1, segWidth - i + 1, segHeight + 2, black);


    drawLine(segWidth - i, 1, segWidth - i, segHeight, _color);
    if (i > 0) drawLine(segWidth - i + 1, 1, segWidth - i + 1, segHeight, black);

    
    if (i < segWidth) {
      drawPixel(segWidth - i, 0, _color); // D
      drawPixel(segWidth - i, segHeight + 1, _color); // G
    }
    delay(animSpeed);
  }
}

void Digit::Morph9() {

  for (int i = 0; i <= (segWidth + 1); i++)
  {
    drawLine(0 + i - 1, 1, 0 + i - 1, segHeight, black);
    drawLine(0 + i, 1, 0 + i, segHeight, _color);
    delay(animSpeed);
  }
}

void Digit::Morph0() {
 
  for (int i = 0; i <= segWidth; i++)
  {
    if (_value==1) { 
       
      drawLine(segWidth - i, segHeight * 2+1 , segWidth - i, segHeight + 2, _color);
      if (i > 0) drawLine(segWidth - i + 1, segHeight * 2+1, segWidth - i + 1, segHeight + 2, black);

      
      drawLine(segWidth - i, 1, segWidth - i, segHeight, _color);
      if (i > 0) drawLine(segWidth - i + 1, 1, segWidth - i + 1, segHeight, black);

      if (i<segWidth) drawPixel(segWidth - i, segHeight * 2 + 2 , _color); 
      if (i<segWidth) drawPixel(segWidth - i, 0, _color); 
    }
    
    if (_value==2) { 
      
      drawLine(segWidth - i, segHeight * 2+1 , segWidth - i, segHeight + 2, _color);
      if (i > 0) drawLine(segWidth - i + 1, segHeight * 2+1, segWidth - i + 1, segHeight + 2, black);
    
      drawPixel(1+i, segHeight + 1, black); 
      if (i<segWidth) drawPixel(segWidth + 1, segHeight + 1- i, _color);
    }

    if (_value==3) { 
  
      drawLine(segWidth - i, segHeight * 2+1 , segWidth - i, segHeight + 2, _color);
      if (i > 0) drawLine(segWidth - i + 1, segHeight * 2+1, segWidth - i + 1, segHeight + 2, black);
      
   
      drawLine(segWidth - i, 1, segWidth - i, segHeight, _color);
      if (i > 0) drawLine(segWidth - i + 1, 1, segWidth - i + 1, segHeight, black);

      
      drawPixel(segWidth - i, segHeight + 1, black); 
    }
    
    if (_value==5) { 
      if (i<segWidth) {
        if (i>0) drawLine(1 + i, segHeight * 2 + 1, 1 + i, segHeight + 2, black);
        drawLine(2 + i, segHeight * 2 + 1, 2 + i, segHeight + 2, _color);
      }
    }
    
    if (_value==5 || _value==9) { 
      if (i<segWidth) drawPixel(segWidth - i, segHeight + 1, black);
      if (i<segWidth) drawPixel(0, segHeight - i, _color);
    }
    delay(animSpeed);
  }
}

void Digit::Morph1() {
 
  for (int i = 0; i <= (segWidth + 1); i++)
  {
   
    drawLine(0 + i - 1, 1, 0 + i - 1, segHeight, black);
    drawLine(0 + i, 1, 0 + i, segHeight, _color);

 
    drawLine(0 + i - 1, segHeight * 2 + 1, 0 + i - 1, segHeight + 2, black);
    drawLine(0 + i, segHeight * 2 + 1, 0 + i, segHeight + 2, _color);

 
    drawPixel(1 + i, segHeight * 2 + 2, black); 
    drawPixel(1 + i, 0, black); 
    drawPixel(1 + i, segHeight + 1, black); 

    delay(animSpeed);
  }
}

void Digit::Morph(byte newValue) {
  switch (newValue) {
    case 2: Morph2(); break;
    case 3: Morph3(); break;
    case 4: Morph4(); break;
    case 5: Morph5(); break;
    case 6: Morph6(); break;
    case 7: Morph7(); break;
    case 8: Morph8(); break;
    case 9: Morph9(); break;
    case 0: Morph0(); break;
    case 1: Morph1(); break;
  }
  _value = newValue;
}
