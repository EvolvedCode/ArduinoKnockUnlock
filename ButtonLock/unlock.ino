void unlock(){ //Feel free to write an unlock function that suits your resources and needs. This gets executed only if the correct pattern is input at record time.
  digitalWrite(buzzer, HIGH);
  delay(250);
  digitalWrite(buzzer, LOW);
  Serial.println("OPEN");
}
