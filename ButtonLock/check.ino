void check(){ //The function responsible for checking whether or not the pattern input at record time is satisfactory, and for issuing the unlock command.
  #ifdef SERIAL Serial.println("checking!");
  #endif
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
