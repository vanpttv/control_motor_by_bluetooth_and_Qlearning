#include<TimerOne.h>

#define ena 5
#define in1 7
#define in2 8
#define in3 10
#define in4 9
#define enb 6
//#define Kp 0.3
//#define Kd 0.001
//#define Ki 0.05
//#define Kp 0.1
//#define Kd 0.0002
//#define Ki 0.04

//char temp[]={'L','U','R','U','U','R','U','L','U'};
char temp[]={'L'};
int i=0;
int dem_xung_1=0, dem_xung_2=0;

double tam;
float T,xung_m1, xung_m2;
float tocdo_m1, tocdo_m2, tocdodat;
double E_m1,E1_m1,E2_m1, E_m2,E1_m2,E2_m2;
double alpha_m1, beta_m1, gamma_m1, alpha_m2, beta_m2, gamma_m2;
double Output_m1, LastOutput_m1, Output_m2, LastOutput_m2;
double Kp_m1,Kd_m1,Ki_m1, Kp_m2,Kd_m2,Ki_m2;

void setup(){
  pinMode(2,INPUT);
  pinMode(4,INPUT);
  pinMode(3,INPUT);
  pinMode(13,INPUT);
  pinMode(ena,OUTPUT); 
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(enb,OUTPUT); 
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  digitalWrite(ena,HIGH);
  digitalWrite(enb,HIGH);

  tocdodat=50; tocdo_m1=0; tocdo_m2=0;
  E_m1=0; E1_m1=0; E2_m1=0;
  Output_m1 = 0; LastOutput_m1 = 0;
  T=0.01;
//  Kp_m1=7;Ki_m1=0.03;Kd_m1=0.005;
  Kp_m1=5.6;Ki_m1=0.03;Kd_m1=0;
  
  E_m2=0; E1_m2=0; E2_m2=0;
  Output_m2 = 0; LastOutput_m2 = 0;
  Kp_m2=7.1;Ki_m2=0.02;Kd_m2=0.0;
  
  Serial.begin(9600);
  attachInterrupt(0,Demxung_m1,RISING);
  attachInterrupt(1,Demxung_m2,RISING);
  Timer1.initialize(10000);  //don vi us - 10ms
  Timer1.attachInterrupt(pid);
}

void loop(){
//  Serial.println(tocdo_m1); 
//  Serial.print("    "); Serial.println(tocdo_m2);
//  Serial.print(Output_m1); Serial.print("    "); Serial.println(Output_m2);


//  if (Serial.available() > 0) 
//  {
//    //đọc dữ liệu gửi về
//    bluetoothByte = Serial.read();
//    Serial.println("CONNECTION IS OK!");
//  }
//  if(bluetoothByte == 49) // so 1
//  {
//    Serial.println("TURN LEFT IS OK!");
//    //dunglai();
//    quaytrai();
//  }
//  else if (bluetoothByte == 52)// so 4
//  {
//    Serial.println("TURN RIGHT IS OK!");
//    //dunglai();
//    quayphai();
//  }
//  else if (bluetoothByte == 50) //so 2
//  {
//    Serial.println("MOVE BACKWARD IS OK!");
//    //dunglai();
//    lui();
//  }
//  if (bluetoothByte == 51) //so 3
//  {
//    Serial.println("MOVE FORWARD IS OK!");
//    //dunglai();
//    dithang();
//  }
//  else if (bluetoothByte == 54) // so 6
//  {
//    Serial.println("STOP IS OK!");
//    dunglai();
//  }

  if (temp[i]=='D')
  {
    Serial.println(temp[i]);
    Serial.println(xung_m2);
    lui  ();
    if ((dem_xung_1 >= 1250)||(dem_xung_2 >= 1250))//up,down 3400, left,right 1950
    {
      i++;
//      delay(2000);
      if(i>=strlen(temp))
      {
  //      Serial.println(strlen(temp));
        Serial.println("STOP");
        dunglai();
        i=10;
      }
      dem_xung_1 = 0;
      dem_xung_2 = 0;
    }
  }
  else if (temp[i]=='U')
  {
    Serial.println(temp[i]);
    dithang();
    if ((dem_xung_1 >= 1200)||(dem_xung_2 >= 1200))//up,down 3500, left,right 2000
    {
      i++;
      if(i>=strlen(temp))
      {
  //      Serial.println(strlen(temp));
        Serial.println("STOP");
        dunglai();
        i=10;
      }
      dem_xung_1 = 0;
      dem_xung_2 = 0;
    }
  }
  else if (temp[i]=='R')
  {
    Serial.println(temp[i]);
    quayphai();
    Serial.println(dem_xung_2);
    if ((dem_xung_2 >= 685))// up,down 3500, left,right 2000
    {
      i++;
      if(i>=strlen(temp))
      {
  //      Serial.println(strlen(temp));
        Serial.println("STOP");
        dunglai();
        i=10;
      }
      dem_xung_1 = 0;
      dem_xung_2 = 0;
    }
  }
  else if (temp[i]=='L')
  {
    Serial.println(temp[i]);
    quaytrai();
//    Serial.println(dem_xung_1); 
    Serial.println(dem_xung_2);
    if ((dem_xung_1 >= 630))//up,down 3500, left,right 2000
    {
      i++;
//      delay(100);
      if(i>=strlen(temp))
      {
  //      Serial.println(strlen(temp));
        Serial.println("STOP");
        dunglai();
        i=10;
      }
      dem_xung_1 = 0;
      dem_xung_2 = 0;
    }
  }
}
void Demxung_m1()
{
  dem_xung_1++;
//  if(digitalRead(4) == LOW)
  xung_m1++;
//  else
//  xung_m1--;
}
void Demxung_m2()
{
  dem_xung_2++;
//  if(digitalRead(13) == LOW)
//if(digitalRead(13) == HIGH)
  xung_m2++;
//  else
//  xung_m2++;
}
void pid()
{ 
  tocdo_m1=((xung_m1/616)*(1/T)*60);
  xung_m1=0;
  E_m1 = tocdodat - tocdo_m1;
  alpha_m1 = 2*T*Kp_m1 + Ki_m1*T*T + 2*Kd_m1;
  beta_m1 = T*T*Ki_m1 - 4*Kd_m1 - 2*T*Kp_m1;
  gamma_m1 = 2*Kd_m1;
  Output_m1 = (alpha_m1*E_m1 + beta_m1*E1_m1 + gamma_m1*E2_m1 + 2*T*LastOutput_m1)/(2*T);
  LastOutput_m1 = Output_m1;

  E2_m1=E1_m1;
  E1_m1=E_m1;
  if(Output_m1>255)  Output_m1=255;
  if(Output_m1<0)  Output_m1=0;

  tocdo_m2=((xung_m2/616)*(1/T)*60);
  xung_m2=0;
  E_m2= tocdodat - tocdo_m2;
  alpha_m2 = 2*T*Kp_m2 + Ki_m2*T*T + 2*Kd_m2;
  beta_m2 = T*T*Ki_m2 - 4*Kd_m2 - 2*T*Kp_m2;
  gamma_m2 = 2*Kd_m2;
  Output_m2 = (alpha_m2*E_m2 + beta_m2*E1_m2 + gamma_m2*E2_m2 + 2*T*LastOutput_m2)/(2*T);
  LastOutput_m2 = Output_m2;

  E2_m2=E1_m2;
  E1_m2=E_m2;
  if(Output_m2>255)  Output_m2=255;
  if(Output_m2<0)  Output_m2=0;
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
