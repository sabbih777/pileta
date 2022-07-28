#include <virtuabotixRTC.h>
// Creation of the Real Time Clock Object
virtuabotixRTC myRTC(6, 7, 8);


int BOMB1 = 11;

int MODE = 12;

int ON_LED = 2;
int AUTO_LED = 3;
int MANUAL_LED= 4;


#define SCHEDULE_1_FROM 745 // 7h45 = 7 x100 + 45
#define SCHEDULE_1_TO 930 // 9h30  = 9 x 100 +30

#define SCHEDULE_2_FROM 1200 
#define SCHEDULE_2_TO 1400

#define SCHEDULE_3_FROM 1715 
#define SCHEDULE_3_TO 1900

int current_time = 0;


short state=0;

bool switchState= false;




void setup()  {
  Serial.begin(9600);
  // Set the current date, and time in the following format:
  // seconds, minutes, hours, day of the week, day of the month, month, year
  // myRTC.setDS1302Time(50, 57, 9, 4, 27, 7, 2022);

  pinMode(MODE, INPUT);
  
  
  pinMode(BOMB1,OUTPUT);
  digitalWrite(BOMB1,HIGH); 
  
  pinMode(ON_LED,OUTPUT);
  digitalWrite(ON_LED,HIGH); 
  
  pinMode(AUTO_LED,OUTPUT);
  digitalWrite(AUTO_LED,LOW); 
  
  pinMode(MANUAL_LED,OUTPUT);
  digitalWrite(MANUAL_LED,LOW); 

}
void loop()  {
  // This allows for the update of variables for time or accessing the individual elements.
  myRTC.updateTime();

  
  
      Serial.println(digitalRead(MODE));

  //Debouncing
  do{


    if ( digitalRead(MODE) == HIGH)
    {
      switchState = true;  
    }
    
            
 }while (digitalRead(MODE) == HIGH );


  if (switchState)
  {
      switch (state) {
        case 0:  
           state=1;
           switchState = false;
           
           
           break;
         case 1:
            state=2;  
            switchState = false;
           
          break;
          
          case 2:  
           state=0;
           switchState = false;
           break;
            
       }
  }
       
    Serial.print("To State: \n");
    Serial.print(state);
    Serial.print(" \n");

  
  //If Automatic Mode
  if(state== 1) { 

     digitalWrite(ON_LED,LOW);
     digitalWrite(AUTO_LED,HIGH);
     digitalWrite(MANUAL_LED,LOW);

    
    
    
    //Check for Schedule
    
    current_time = myRTC.hours * 100 + myRTC.minutes; //change RTC Hour and minutes format in order to compare with defined schedules
    
    if (  (current_time >= SCHEDULE_1_FROM && current_time <= SCHEDULE_1_TO)  || //Morning
          (current_time >= SCHEDULE_2_FROM && current_time <= SCHEDULE_2_TO) || //Afternoon
          (current_time >= SCHEDULE_3_FROM && current_time <= SCHEDULE_3_TO)  //Night
       )
    {
        Serial.print("Sí: \n");
        digitalWrite(BOMB1,LOW);
       
    }
    else {
        digitalWrite(BOMB1,HIGH);
               
      }
    
  }

  else if (state ==2) {
    digitalWrite(BOMB1,LOW);
    digitalWrite(ON_LED,LOW);
    digitalWrite(AUTO_LED,LOW);
    digitalWrite(MANUAL_LED,HIGH);
    
  }
  else if (state ==0) {
    digitalWrite(BOMB1,HIGH);
    digitalWrite(ON_LED,HIGH);
    digitalWrite(AUTO_LED,LOW);
    digitalWrite(MANUAL_LED,LOW);
    
  }
  
  
  
  
 
  // Start printing elements as individuals
  Serial.print("Current Date / Time: ");
  Serial.print(myRTC.dayofmonth);
  Serial.print("/");
  Serial.print(myRTC.month);
  Serial.print("/");
  Serial.print(myRTC.year);
  Serial.print("  ");
  Serial.print(myRTC.hours);
  Serial.print(":");
  Serial.print(myRTC.minutes);
  Serial.print(":");
  Serial.println(myRTC.seconds);

  
  // Delay so the program doesn't print non-stop
  //delay(500);
}
