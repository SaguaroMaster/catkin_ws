#include <Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define thr_in_pin 8
#define str_in_pin 9
#define mode_pin A2
#define bat_voltage_pin A1

Adafruit_SSD1306 display(128, 64, &Wire, -1);

char c;
char str2[] = "    ";

volatile float rev=0;
float value=0;
float spd_kmh;
float spd_mps;
float bat_voltage;      //values for determining battery voltage
float bat_raw;

int rpm;
int oldtime=0;
int tim;
int i;
int j;   
int thr_in;             //values read from RC remote
int str_in;
int thr_out1 = 0;       //outgoing values to RC car
int str_out1 = 0;
int spd_req = 0;       //requested speed, steering and throttle values from Jetson Nano
int thr_req = 0;
int str_req = 0;
int thr_def = 1455;    //default/limit throttle and steering values
int str_def = 1455;
int thr_max = thr_def+200;
int thr_min = thr_def-150;
int str_max = str_def+300;
int str_min = str_def-300;
int mode;
int chars_to_read;
int tps;
int loops = 0;

long lastMillis = 0;
long currentMillis;

volatile long RPMN1count=0;
volatile long RPMN1=0;
volatile boolean flag=0;
long RPMN1period;

Servo str_out;
Servo thr_out;


void N1()
{
  RPMN1period=micros()-RPMN1count;
  RPMN1count=micros();
  flag=1;
}

void setup()
{
  str_out.attach(6);     //ESC and servo control are handled as if both were servos
  thr_out.attach(7);
  
  pinMode (thr_in_pin, INPUT);   //8 -> thr_in; 9 -> str_in
  pinMode (str_in_pin, INPUT);
  pinMode (mode_pin, INPUT);  //for determining wether the Jetson Nano or RC remtoe controls the car
  pinMode (bat_voltage_pin, INPUT);  //for battery voltage reading

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)){ // Address 0x3D for 128x64  
    Serial.println(F("SSD1306 allocation failed"));
  }

  attachInterrupt(0, N1, FALLING);

  Serial.begin(115200);  
}

void loop(){

  currentMillis = millis();
  loops++;
  
  if(currentMillis - lastMillis > 1000){
    lastMillis = currentMillis;
    tps = loops;
    loops = 0;
  }

  if(flag)
  {
    noInterrupts();
    rpm=(30000000UL/RPMN1period)/4;   //Two signals per rotation.
    interrupts();
    flag=0;
  }
  spd_mps = (rpm/60)*1.5*0.355;   //wheel circumference 35,5cm
  spd_kmh = spd_mps*3.6;
  
  bat_raw = analogRead(bat_voltage_pin);
  bat_voltage = bat_raw * 10/1023;

  if(digitalRead(mode_pin)==LOW){           //LOW means RC remote is in control
    thr_in = pulseIn(thr_in_pin, HIGH);
    str_in = pulseIn(str_in_pin, HIGH);
    mode = 0;
  }
  else if(digitalRead(mode_pin)==HIGH){     //HIGH means external device is in control
    thr_in = thr_req;
    str_in = str_req;
    mode = 1;
  }


                                               //do the serial stuff
  Serial.print("!");                          //outgoing data to Jetson Nano on serial
  j=sprintf(str2,"%04d", int(spd_mps*100));  //1000x the value of the speed, this way there is no need for decimal point
  Serial.print(str2);
  j=sprintf(str2,"%04d", thr_out1);
  Serial.print(str2);
  j=sprintf(str2,"%04d", str_out1);
  Serial.print(str2);
  j=sprintf(str2,"%04d", mode);
  Serial.print(str2);
  Serial.println("#");
        
  while(Serial.available() > 0 && mode == 1){                                        
      if(c = Serial.read() == '!'){                                                  //outgoing format(without spaces): ! 0000 0000 0000 0000 #
          spd_req  = 0;                                                             //incoming format(without spaces): ! 0000 0000 0000
          thr_req  = 0;
          str_req  = 0;
          c = Serial.read();                 //requested speed (m/s)
          spd_req  += (c-48)*1000;
          c = Serial.read();
          spd_req  += (c-48)*100;
          c = Serial.read();
          spd_req  += (c-48)*10;
          c = Serial.read();
          spd_req  += (c-48);
  
          c = Serial.read();                  //requested throttle position (us) - max 1650us, min 1350us, mid 1455us 
          thr_req  += (c-48)*1000;
          c = Serial.read();
          thr_req  += (c-48)*100;
          c = Serial.read(); 
          thr_req  += (c-48)*10;
          c = Serial.read();
          thr_req  += (c-48);
  
          c = Serial.read();                  //requested steering angle (us) max 1755us, min 1155us, mid 1455
          str_req  += (c-48)*1000;
          c = Serial.read();
          str_req  += (c-48)*100;
          c = Serial.read(); 
          str_req  += (c-48)*10;
          c = Serial.read();
          str_req  += (c-48);                
      }
    }

    
    if(str_in<=500){                                  //steering limits
      str_out1 = str_def;
      str_out.writeMicroseconds(str_def);
    }
    else if(str_in>str_max){
      str_out1 = str_max;
      str_out.writeMicroseconds(str_max); 
    }
    else if(str_in<str_min){
      str_out1 = str_min;
      str_out.writeMicroseconds(str_min);
    }
    else{
      str_out1 = str_in;
      str_out.writeMicroseconds(str_in);  
    }


    if(thr_in<=500){                                  //throttle limits
      thr_out1 = thr_def;
      thr_out.writeMicroseconds(thr_def); 
    }
    else if(thr_in>thr_max){
      thr_out1 = thr_max;
      thr_out.writeMicroseconds(thr_max); 
    }
    else if(thr_in<thr_min){
      thr_out1 = thr_min;
      thr_out.writeMicroseconds(thr_min);
    }
    else{
      thr_out1 = thr_in;
      thr_out.writeMicroseconds(thr_in);
    }
 
    display.clearDisplay();                           //draw to OLED (this slows down the processing by a factor of cca 2 :( )
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.print(rpm);
    display.println(" RPM");
    display.print(spd_kmh);
    display.print(" km/h; ");
    display.print(spd_mps);
    display.println(" m/s");
    display.print(tps);
    display.println(" TPS");
    
    display.print("thr_in: ");
    display.println(thr_in);
    display.print("str_in: ");
    display.println(str_in);
    display.print("thr_out: ");
    display.println(thr_out1);
    display.print("str_out: ");
    display.println(str_out1);
    display.print("Battery: ");
    display.print(bat_voltage);
    display.println(" V");
    display.display();
    
}
