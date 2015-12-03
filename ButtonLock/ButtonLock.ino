#include "config.h"
#include "global.h"

void loop(){
  if(recording){ //Recording
    record();
  }
  else{ //Hearing
    while (1){ //We will not record ever again, so running the if at the beginning of loop() is useless.
      hear();
      delay(res);
    }
  }
  delay(res); //To reduce strain and power consumption (one of our goals) we can introduce a delay to the code that slows down the frequency at which the Arduino checks and computes things.
}


