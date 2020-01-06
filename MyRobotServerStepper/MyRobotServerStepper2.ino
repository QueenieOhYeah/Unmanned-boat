//舵机占用IO口3，5，6，9，10，11 步进电机占用4dir，7step
//robot server
#include <Braccio.h>
#include <Servo.h>
#include <EEPROM.h>
#define DIR 4
#define STEP 7


#define resetM1  60
#define resetM2  90-(-10)-38
#define resetM3  90+90
#define resetM4  90-90
#define resetM5  90
#define resetM6  90
#define resetPos  0

#define stepDelay  10  //allowed 10-30ms
#define closeAngle 65

union data{
  int a;
  byte b[4];
};

Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;
Servo cam;
byte command[10];
bool pack = false;
byte n = 0;

//电机校正值
int ErrorRectifyM1 = 0;
int ErrorRectifyM2 = -10;
int ErrorRectifyM3 = 6;
int ErrorRectifyM4 = 10;
int ErrorRectifyM5 = 0;
int ErrorRectifyM6 = 0;

//电机实际初始值
int Mangle[6]={resetM1,resetM2,resetM3,resetM4,resetM5,resetM6};
//坐标系的值
int ControlValue[7]={0,38+24,-90,-90,0,1,20};
int coutNum=7;
int address=0;
data posCurrentU;
int posCurrent;
int posDesired=0;

void StepperMove(int *pos, int *pos_current){
  int x;
  int dpos;
//*pos = pos1
//*pos_current = pos_current1
  dpos = *pos - *pos_current;
  if(dpos>0){
    digitalWrite(DIR,HIGH);
    Serial.println("running for");
    for(x=0; x<int(100*dpos/6); x++){
      digitalWrite(STEP,HIGH);
      delayMicroseconds(500);
      digitalWrite(STEP,LOW);
      delayMicroseconds(500);
    }
  }
  else{
    digitalWrite(DIR,LOW);
    Serial.println("running back");
    for(x=0; x<int(-100*dpos/6); x++){
      digitalWrite(STEP,HIGH);
      delayMicroseconds(500);
      digitalWrite(STEP,LOW);
      delayMicroseconds(500);
    }
  }
  }
  
  void StepperWrite(int *pos, int *pos_current){
    for(int i=0; i<4; i++){
    posCurrentU.b[i] = EEPROM.read(i);
    }
//*pos = pos1
//*pos_current = pos_curent1
//    *pos_current = posCurrentU.a;
    *pos_current = posCurrentU.a;
    
//    Serial.println(posCurrent);
    if (*pos>=150){
      posCurrentU.a=150;
      for(int i=0; i<4; i++){
          EEPROM.write(i,posCurrentU.b[i]);
       }
      }
      else{
        posCurrentU.a=*pos;
       for(int i=0; i<4; i++){
          EEPROM.write(i,posCurrentU.b[i]);
       }

      }
    }


void unpack(){
  //Serial.println("hello");
  //byte information1 = 0x7e;
  byte information2 = 0x7d;
  if (command[9]==information2){
    //Serial.println("coming"); 
    switch(command[1]){
      case 0x23:
        Serial.println("moveding...");
        for(int i=0;i<5;i++)  //数据类型转换
        {                                      
          ControlValue[i]=command[i+2];  
          // Serial.println(Mangle[i]);
        }
        ControlValue[5]=command[7];
        ControlValue[6]=command[8];
        
 
        ControlValueToMangle();
        StepperMove(&posDesired, &posCurrent);
        StepperWrite(&posDesired, &posCurrent);    
        Braccio.ServoMovement(stepDelay, Mangle[0],Mangle[1],Mangle[2],Mangle[3],Mangle[4],Mangle[5]); 
        Serial.print("moved at:");
        MangleToControlValue();  
        Serial.print(ControlValue[0]); Serial.print(",");
        Serial.print(ControlValue[1]); Serial.print(",");
        Serial.print(ControlValue[2]); Serial.print(",");
        Serial.print(ControlValue[3]); Serial.print(",");
        Serial.print(ControlValue[4]); Serial.print(",");
        Serial.print(ControlValue[5]); Serial.print(",");
        Serial.print(ControlValue[6]); Serial.print("\n");
        break;
      case 0x24: //read
        MangleToControlValue();
        for(int i=0;i<7;i++)
        {
        Serial.print(ControlValue[i]);
        if(i!=6)
        {  Serial.print(","); } 
        else
        {Serial.print("\n");}
                               
        }
        break;
      case 0x25: //reset
        Serial.println("reseting...");                          
        Mangle[0]=resetM1;
        Serial.print("M1:");
        Serial.println(Mangle[0]);
        Mangle[1]=resetM2;
        Mangle[2]=resetM3;
        Mangle[3]=resetM4;
        Mangle[4]=resetM5;
        Mangle[5]=resetM6;
        posDesired=resetPos;
        StepperMove(&posDesired, &posCurrent);
        StepperWrite(&posDesired, &posCurrent);  
        Braccio.ServoMovement(stepDelay, Mangle[0],Mangle[1],Mangle[2],Mangle[3],Mangle[4],Mangle[5]); 
        MangleToControlValue();
        Serial.print("reset finished at:");
        Serial.print(ControlValue[0]); Serial.print(",");
        Serial.print(ControlValue[1]); Serial.print(",");
        Serial.print(ControlValue[2]); Serial.print(",");
        Serial.print(ControlValue[3]); Serial.print(",");
        Serial.print(ControlValue[4]); Serial.print(",");
        Serial.print(ControlValue[5]); Serial.print(",");
        Serial.print(ControlValue[6]); Serial.print("\n");
        break;
      case 0x26: //stop
        Serial.println("MangleToControlValue()...");
            MangleToControlValue();
            for(int i=0;i<7;i++){
              Serial.println(ControlValue[i]);
            } 
                        
            
            Serial.println("ControlValueToMangle()...");
            ControlValueToMangle();
            for(int i=0;i<6;i++){
              Serial.println(Mangle[i]);
              Serial.println(posDesired);
            }
        break;
      case 0x27:
        cam.write(command[2]);
        break;
      default:
        break;
    }
  command[0]=0xdd;
  command[9]=0xdd;
  }

}

void ControlValueToMangle(){
  Mangle[0] = (ControlValue[0]+ErrorRectifyM1)+60;
  Mangle[1] = 90 - (ControlValue[1]+ErrorRectifyM2);
  Mangle[2] = 90 - (ControlValue[2]+ErrorRectifyM3);
  Mangle[3] = 90 + (ControlValue[3]+ErrorRectifyM4);
  Mangle[4] = 90 - (ControlValue[4]+ErrorRectifyM5);
  if(ControlValue[5]==0){
  Mangle[5] = 25;
  }
  else {
  Mangle[5] = closeAngle;
  }
  posDesired=ControlValue[6];
  
}

void MangleToControlValue(){

   //-90,90
   // ControlValue[0] = (90-Mangle[0]) - ErrorRectifyM1;  
    ControlValue[0] = (Mangle[0]-60) - ErrorRectifyM1;  //第一关节改 
    if(ControlValue[0]>90) 
      {ControlValue[0]=90;}
      else if(ControlValue[0]< -60)
      {ControlValue[0]=-60;}
      
    //-90,90
    ControlValue[1] = (90-Mangle[1]) - ErrorRectifyM2 ;
    if(ControlValue[1]>90) 
      {ControlValue[1]=90;}
      else if(ControlValue[1]< -90)
      {ControlValue[1]=-90;}

    //-120,60// updated = -90,90
    ControlValue[2] = (90-Mangle[2]) -  ErrorRectifyM3;  
    if(ControlValue[2]>90) 
      {ControlValue[2]=90;}
      else if(ControlValue[2]< -90)
      {ControlValue[2]=-90;}

    //-90,90
    ControlValue[3] = -1*(90-Mangle[3]) - ErrorRectifyM4;  
    if(ControlValue[3]>90) 
      {ControlValue[3]=90;}
      else if(ControlValue[3]< -90)
      {ControlValue[3]=-90;}

    //-90,90
    ControlValue[4] = -1*(90-Mangle[4])-  ErrorRectifyM5;  
    if(ControlValue[4]>90) 
      {ControlValue[4]=90;}
      else if(ControlValue[4]< -90)
      {ControlValue[4]=-90;}

      
    if(Mangle[5] == closeAngle){
       ControlValue[5] = 1;
    }
    else{
       ControlValue[5] =0;
      }    
     ControlValue[6] =posDesired;
  }


void setup() {
  // initialize serial:
  Serial.begin(115200);
  // reserve 200 bytes for the inputString:
  Serial.println("hello");
  Braccio.begin();
  
  ControlValue[5] =1;
  ControlValueToMangle();
  StepperMove(&posDesired, &posCurrent);
  StepperWrite(&posDesired, &posCurrent);
  Braccio.ServoMovement(stepDelay, Mangle[0],Mangle[1],Mangle[2],Mangle[3],Mangle[4],Mangle[5]); 
//  cam.attach(12);
//  cam.write(0);
  Serial.println("initialization finished");  

  
}
void loop() {
 
}


/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    byte information = Serial.read();
   
    if (!pack && information==0x7e){
      pack=true;
      n = 0;
    }
    
    if (pack && (n < 10)){
    if ((n>1)&& (n<10))
    {
      command[n]=information-100;
    }
    else
    {
      command[n]=information;
    } 
      Serial.println(information);
      n++;
    }
    if (n==1&&information==0x25){
        unpack();
        pack=false;
        n=0;
      }
    else if (n >= 10){
      //Serial.println("unpack");
      unpack();
      pack = false;
      n=0;
    }
            
  }
}

