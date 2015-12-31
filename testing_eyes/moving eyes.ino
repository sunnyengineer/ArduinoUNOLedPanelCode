
#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library

// Similar to F(), but for PROGMEM string pointers rather than literals
#define F2(progmem_ptr) (const __FlashStringHelper *)progmem_ptr

#define CLK 8  // MUST be on PORTB! (Use pin 11 on Mega)
#define LAT A3
#define OE  9
#define A   A0
#define B   A1
#define C   A2
// Last parameter = 'true' enables double-buffering, for flicker-free,
// buttery smooth animation.  Note that NOTHING WILL SHOW ON THE DISPLAY
// until the first call to swapBuffers().  This is normal.
RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, true);
// Double-buffered mode consumes nearly all the RAM available on the
// Arduino Uno -- only a handful of free bytes remain.  Even the
// following string needs to go in PROGMEM:

int eye_origin_x = 24;
int eye_origin_y = 7;

int pupil_origin_x = eye_origin_x;
int pupil_origin_y = eye_origin_y;

int eye_offset = 17;

int eye_radius = 6;
double pupil_radius = 1.5;

void setup() {
  matrix.begin();
}
void set_Eye(){
  matrix.fillCircle(eye_origin_x, eye_origin_y, eye_radius, matrix.Color333(255, 255, 255));
  matrix.fillCircle(eye_origin_x - eye_offset, eye_origin_y, eye_radius, matrix.Color333(255, 255, 255));
}
void loop() {
  
  // Clear background
  matrix.fillScreen(0);
  set_Eye();
  // Pupils
  
  matrix.fillRect(pupil_origin_x - 1, pupil_origin_y - 1, 3, 3, matrix.Color333(0, 0, 255));
  matrix.fillRect(pupil_origin_x - eye_offset - 1, pupil_origin_y - 1, 3, 3, matrix.Color333(0, 0, 255));

 

  // Eyebrow
  matrix.drawLine(31, 11, 27, 15, matrix.Color333(7, 0, 0)); //Topleft angle
  matrix.drawLine(27, 15, 21, 15, matrix.Color333(7, 0, 0));
  matrix.drawLine(21, 15, 17, 11, matrix.Color333(7, 0, 0));
  matrix.drawLine(17, 11, 14, 11, matrix.Color333(7, 0, 0));
  matrix.drawLine(14, 11, 10, 15, matrix.Color333(7, 0, 0));
  matrix.drawLine(10, 15, 04, 15, matrix.Color333(7, 0, 0));
  matrix.drawLine(04, 15, 00, 11, matrix.Color333(7, 0, 0));
  
  // Update display
  matrix.swapBuffers(true);

  delay(1500);

  while(pupil_origin_x > 20){
    pupil_origin_x--;
    set_Eye();
    matrix.fillRect(pupil_origin_x - 1, pupil_origin_y - 1, 3, 3, matrix.Color333(0, 0, 255));
    matrix.fillRect(pupil_origin_x - eye_offset - 1, pupil_origin_y - 1, 3, 3, matrix.Color333(0, 0, 255));   
    matrix.swapBuffers(true);
    delay(250);
     }
  delay(1000);
    while(pupil_origin_x < 28){
      pupil_origin_x++;
      set_Eye();
      matrix.fillRect(pupil_origin_x - 1, pupil_origin_y - 1, 3, 3, matrix.Color333(0, 0, 255));
      matrix.fillRect(pupil_origin_x - eye_offset - 1, pupil_origin_y - 1, 3, 3, matrix.Color333(0, 0, 255));  
      matrix.swapBuffers(true); 
      delay(250);
    }
    delay(1000);
    while(pupil_origin_x > 24){
      pupil_origin_x--;
      set_Eye();
      matrix.fillRect(pupil_origin_x - 1, pupil_origin_y - 1, 3, 3, matrix.Color333(0, 0, 255));
      matrix.fillRect(pupil_origin_x - eye_offset - 1, pupil_origin_y - 1, 3, 3, matrix.Color333(0, 0, 255));  
      matrix.swapBuffers(true); 
      delay(250);
    }
    
  //////////////BLINK///////////////
  delay(2000);
  // Eye
  matrix.fillCircle(eye_origin_x, eye_origin_y, eye_radius, matrix.Color333(0, 0, 0));
  matrix.fillCircle(eye_origin_x - eye_offset, eye_origin_y, eye_radius, matrix.Color333(0, 0, 0));
  
  
  //Closed eye
  matrix.drawLine(30, 7, 18, 7, matrix.Color333(255, 255, 255));
  matrix.drawLine(13, 7, 1, 7, matrix.Color333(255, 255, 255));

  matrix.drawLine(25, 7, 23, 7, matrix.Color333(0, 0, 255));
  matrix.drawLine(8, 7, 6, 7, matrix.Color333(0, 0, 255));
  
    
  matrix.swapBuffers(true);

  delay(750);
  pupil_origin_x = 24;
}

