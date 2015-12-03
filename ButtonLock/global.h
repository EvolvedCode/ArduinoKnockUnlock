#ifndef global_h
#define global_h

//Variable Setup
bool counting = false;
bool rcounting = false;
bool recording = false;
bool door = false;
bool recorded = false; //True if the user has recorded at least one full push.
int delta[maxpush], duration[maxpush];
int current = 0;
int rcurrent = 0;
unsigned long start, finish, relock = 1;

#endif
