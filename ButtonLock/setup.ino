void setup(){
  #ifdef SERIAL Serial.begin(SERIAL);
  #endif
  //Pin Declarations
  pinMode(pButton, INPUT_PULLUP);
  pinMode(rButton, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  pinMode(motor, OUTPUT);
  pinMode(buzzer, OUTPUT);
  
  delta[0] = 0;
  digitalWrite(led, HIGH);
  delay(500); //The user should hold the record button at "boot up" until the led blinks.
  
  if(digitalRead(rButton) == 0){
    #ifdef SERIAL Serial.println("recording!");
    #endif
    recording = true;
    push_cnt = 0; //We'll count how many pushes we're expecting later.
    digitalWrite(led, LOW); //Blink the led to indicate that we're about to record. (Fors are bad :P)
    delay(100);
    digitalWrite(led, HIGH);
    delay(100);
    digitalWrite(buzzer, HIGH); //Buzz to indicate that we're starting to record.
    digitalWrite(led, LOW);
    delay(100);
    digitalWrite(buzzer, LOW);
    digitalWrite(led, HIGH);
  }
  else digitalWrite(led, LOW);
}
