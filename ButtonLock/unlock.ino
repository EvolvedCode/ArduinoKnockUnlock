void unlock(){ //Feel free to write an unlock function that suits your resources and needs. This gets executed only if the correct pattern is input at record time.
  digitalWrite(buzzer, HIGH);
  digitalWrite(motor, HIGH); //Don't forget to alter the pinMode declarations in the setup method if you desire to make changes.
  delay(250);
  digitalWrite(buzzer, LOW);
  delay(500);
  digitalWrite(motor, LOW);

  relock = millis() + locktime;
  door = true;
  #ifdef SERIAL Serial.println("OPEN");
  #endif
}

void lock(){ //Do the reverse process.
  door = false;
  digitalWrite(motor, HIGH);
  digitalWrite(buzzer, HIGH);
  delay(750);
  digitalWrite(motor, LOW);
  digitalWrite(buzzer, LOW);
}

