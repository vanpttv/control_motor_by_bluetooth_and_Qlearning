#include <SoftwareSerial.h>
//SoftwareSerial HC06(10, 11); // RX,TX //HC06-TX Pin 10, HC06-RX to Arduino Pin 11
SoftwareSerial HC06(4, 13); // RX,TX //HC06-TX Pin 4, HC06-RX to Arduino Pin 13
#include<TimerOne.h>

#define ena 5
#define in1 7
#define in2 8
#define in3 10
#define in4 9
#define enb 6

//char temp[]={'L','U','R','U','U','R','U','L','U'};
//char temp[]={'U'};
char Data_Bluetooth;
int Output_m1=180, Output_m2=180;
void quayphai ();
void quaytrai ();
void lui ();
void dithang ();


void setup(){
  pinMode(ena,OUTPUT); 
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(enb,OUTPUT); 
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  digitalWrite(ena,HIGH);
  digitalWrite(enb,HIGH);
  
  
  Serial.begin(9600);
  HC06.begin(9600); //Baudrate 9600 , Choose your own baudrate 
}


void loop() {

  if(HC06.available() > 0) //When HC06 receive something
  {
    Data_Bluetooth = HC06.read(); //Read from Serial Communication
    Serial.println("CONNECTION IS OK!");
  }

  
  if(Data_Bluetooth == '1') // so 1
  {
    Serial.println("TURN LEFT IS OK!");
    quaytrai();
  }
  else if (Data_Bluetooth == '4')// so 4
  {
    Serial.println("TURN RIGHT IS OK!");
    quayphai();
  }
  else if (Data_Bluetooth == '2') //so 2
  {
    Serial.println("MOVE BACKWARD IS OK!");
    lui();
  }
  if (Data_Bluetooth == '3') //so 3
  {
    Serial.println("MOVE FORWARD IS OK!");
    dithang();
  }
  else if (Data_Bluetooth == '6') // so 6
  {
    Serial.println("STOP IS OK!");
    dunglai();
  }

}


void quayphai ()
{
  analogWrite(ena,Output_m1);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  analogWrite(enb,Output_m2);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
}
void quaytrai ()
{
  analogWrite(ena,Output_m1);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  analogWrite(enb,Output_m2);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
}
void dithang()
{
    analogWrite(ena,Output_m1);
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    analogWrite(enb,Output_m2);
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);
}
void lui  ()
{
    analogWrite(ena,Output_m1);
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
    analogWrite(enb,Output_m2);
    digitalWrite(in3,LOW);
    digitalWrite(in4,HIGH);
    
}
void dunglai()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
