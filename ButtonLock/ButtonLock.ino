//Pin Cofiguration
const int pButton = 4; //pattern button
const int rButton = 6; //record button
const int buzzer = 9; //buzzer or speaker
const int led = 13; //led

//General Configuration
const int maxpush = 10;  //Set this to the maximum amount of pushes you should expect.
const int longest = 3000; //Set this to the maximum amount of time you should expect between current and possibly recorded pushes. Have it be longer than your longest push.
int push_cnt = 7;  //Set this to the amount of knocks in your default pattern. //This is used to prevent code from going out of bounds and into useless data on the arrays.
int ref_delta[maxpush]={0, 161, 100, 96, 231, 503, 171}, ref_duration[maxpush]={115, 86, 81, 86, 130, 110, 136};//Set a default pattern here.
int res = 5; //The higher this is, the more inaccurate the measuring of pushes will be.
int tolerance = 200; //How many milliseconds the user can be late.

//Variable Setup
bool counting = false;
bool rcounting = false;
bool recording = false;
bool recorded = false; //True if the user has recorded at least one full push.
int delta[maxpush], duration[maxpush];
int current = 0;
int rcurrent = 0;
unsigned long start, finish;

void setup(){
  Serial.begin(9600);
  pinMode(pButton, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  pinMode(rButton, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  
  delta[0] = 0;
  digitalWrite(led, HIGH);
  delay(500); //The user should hold the record button at "boot up" until the led blinks.
  
  if(digitalRead(rButton) == 0){
    Serial.println("recording!");
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

void unlock(){ //Feel free to write an unlock function that suits your resources and needs. This gets executed only if the correct pattern is input at record time.
  digitalWrite(buzzer, HIGH);
  delay(250);
  digitalWrite(buzzer, LOW);
  Serial.println("OPEN");
}

void check(){ //The function responsible for checking whether or not the pattern input at record time is satisfactory, and for issuing the unlock command.
  Serial.println("checking!");
  delta[0] = 0;
  ref_delta[0] = 0;
  int valid = 0;
  current = 0;
  for(int i = 0; i < push_cnt; i++){
    if(abs(ref_delta[i] - delta[i]) < tolerance) valid++;
    if(abs(ref_duration[i] - duration[i]) < tolerance) valid++;
  }
  
  if(valid == push_cnt*2){
    unlock();
  }
  else{
    //buzz;
  }
}

void loop(){
  if(recording){ //Recording
    if((digitalRead(rButton) == 0 || millis() - start > longest) && recorded){ //If rButton is pressed or the "longest" time limit has been exceeded and the user has recorded at least one full push.
      rcounting = false;
      recording = false; //Stopped recording. Now we're listening and checking.
      rcurrent = maxpush + 1; //We don't want the if below to execute at all.
      Serial.println("Done Recording!");
    }

    if(rcurrent < maxpush){
      if(digitalRead(pButton) == 0 && !rcounting){
        start = millis();
        rcounting = true;
      }
  
      if(digitalRead(pButton) == 1 && rcounting){
        ref_delta[rcurrent] = start - finish; //This finish is the end of the previous push. Essentially we're finding out how far apart the current and the previous push were.
        finish = millis();
        ref_duration[rcurrent] = finish - start; //This finds the Δt or, in other words, the duration of the current push.
        Serial.println(ref_delta[rcurrent]);
        Serial.println(ref_duration[rcurrent]);
        rcurrent++;
        push_cnt = rcurrent;
        rcounting = false;
        recorded = true;
      }
    }
  }
  else{ //Listening
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
        Serial.println(String("delta ")+String(delta[current]));
        Serial.println(String("dur ")+String(finish-start));
        current++;
        counting = false;
      }
    }
    else check();
  }
  
  delay(res); //To reduce strain and power consumption (one of our goals) we can introduce a delay to the code that slows down the frequency at which the Arduino checks and computes things.
}


