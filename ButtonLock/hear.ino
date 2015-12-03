void hear(){
  if(relock - 10 < millis() < relock + 10 && door) lock();
  
  if(millis() - start > longest){
    counting = false; //If 3 seconds pass without a push, we stop counting and start over.
    current = 0;
  }
  
  if(current < push_cnt){
    if(digitalRead(pButton) == 0 && !counting){
      counting = true;
      start = millis();
    }
    
    if(digitalRead(pButton) == 1 && counting){
      delta[current] = start - finish; //This finish is the end of the previous push. Essentially we're finding out how far apart the current and the previous push were.
      finish = millis();
      duration[current] = finish - start; //This finds the Δt or in other words the duration of the current push.
      #ifdef SERIAL
        Serial.println(String("delta ")+String(delta[current]));
        Serial.println(String("dur ")+String(finish-start));
      #endif
      current++;
      counting = false;
    }
  }
  else check();
}
