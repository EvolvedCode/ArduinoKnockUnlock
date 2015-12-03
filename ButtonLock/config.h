#ifndef config_h
#define config_h

//Pin Cofiguration
#define pButton 2 //pattern button
#define rButton 3 //record button
#define buzzer 11 //buzzer or speaker
#define motor 12 //motor that unlocks the door
#define led 13 //led

//General Configuration
#define maxpush 10 //Set this to the maximum amount of pushes you should expect.
#define longest 3000 //Set this to the maximum amount of time you should expect between current and possibly recorded pushes. Have it be longer than your longest push.
int push_cnt = 7;  //Set this to the amount of knocks in your default pattern. //This is used to prevent code from going out of bounds and into useless data on the arrays.
int ref_delta[maxpush]={0, 161, 100, 96, 231, 503, 171}, ref_duration[maxpush]={115, 86, 81, 86, 130, 110, 136};//Set a default pattern here.
int res = 5; //The higher this is, the more inaccurate the measuring of pushes will be.
int tolerance = 200; //How many milliseconds the user can be late.
#define locktime 10000 //Set this to the amount of time after which the door will lock itself again.

//#define SERIAL 9600 //Uncomment this line if you want some information regarding the pushes transmitted over serial port. Set which port you want to use.

#endif
