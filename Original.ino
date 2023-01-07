//タイマー
#include <DynamixelWorkbench.h>

#if defined(__OPENCM904__)
  #define DEVICE_NAME "/dev/cu.usbmodem11401" //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP
#elif defined(__OPENCR__)
  #define DEVICE_NAME ""
#endif   

#define BAUDRATE  1000000
#define DXL_ID_1    1
#define DXL_ID_2    2

// LEDをオン・オフする際の出力
#define DIGIT_ON LOW
#define DIGIT_OFF HIGH
#define SEGMENT_ON HIGH
#define SEGMENT_OFF LOW
const int G = 8;// F
const int F = 9;// F
const int E = 10;// F
const int D = 11;// F
const int A = 12;// F
const int B = 13;// F
const int C = 14;

//Dynamixel周辺
uint8_t dxl_id;
DynamixelWorkbench dxl_wb;
int32_t speed = 0.1;

//アナログピンの設定
const int analogInputPin = 1;

int minuteNumber = 0;
int minutePosition[5];

//ブロックごとの真偽値処理
bool result;
bool isTimerSet;
bool startRotation;
bool timerFinish;

void setup() 
{
  pinMode(analogInputPin, INPUT_ANALOG);
  pinMode(BOARD_BUTTON_PIN, INPUT_PULLDOWN);
  pinMode(BOARD_LED_PIN, OUTPUT);
  Serial.begin(115200);

  const char *log;
  result = false;
  isTimerSet = false;
  startRotation = false;
  timerFinish = false;

  uint16_t model_number = 0;

  //セットアップが完了しているかを3工程で確認する
  result = dxl_wb.init(DEVICE_NAME, BAUDRATE, &log);

  result = dxl_wb.ping(DXL_ID_1, &model_number, &log);
  result = dxl_wb.ping(DXL_ID_2, &model_number, &log);

  result = dxl_wb.jointMode(DXL_ID_1, 0, 0, &log);
  result = dxl_wb.jointMode(DXL_ID_2, 0, 0, &log);

  //変更前
  // Serial.print(dxl_wb.readControlTableItem(PRESENT_POSITION, 1));
  // Serial.print(dxl_wb.readControlTableItem(PRESENT_POSITION, 2));
  //初期設定
  SetUp();
  //変更後
  // Serial.print(dxl_wb. (PRESENT_POSITION, 1));
  // Serial.print(dxl_wb.readControlTableItem(PRESENT_POSITION, 2));


  pinMode(G, OUTPUT);    // digitPinを出力モードに設定する
  pinMode(F, OUTPUT);    // digitPinを出力モードに設定する
  pinMode(E, OUTPUT);    // digitPinを出力モードに設定する
  pinMode(D, OUTPUT);    // digitPinを出力モードに設定する
  pinMode(A, OUTPUT);    // digitPinを出力モードに設定する
  pinMode(B, OUTPUT);    // digitPinを出力モードに設定する
  pinMode(C, OUTPUT);    // digitPinを出力モードに設定する


  minutePosition[0] = 512;
  minutePosition[1] = 409;
  minutePosition[2] = 307;
  minutePosition[3] = 205;
  minutePosition[4] = 102;
  minutePosition[5] = 0;  //５分
}


void loop() {
  int analogValue = analogRead(analogInputPin);
  int buttonState = digitalRead(BOARD_BUTTON_PIN);

  //ボタンによるタイマーセット
  if(buttonState == HIGH && !isTimerSet){
    //ボタンが押された
    //短針を動かす
    isTimerSet = true;
    startRotation = true;
  }else if(buttonState == LOW && !isTimerSet){
    if(analogValue < 100){
      minuteNumber = 1;
      Number_1_ON();
      dxl_wb.goalVelocity(DXL_ID_2,speed);
      dxl_wb.goalPosition(DXL_ID_2, (int32_t)409);
    }else if(100 <= analogValue && analogValue < 200){
      minuteNumber = 2;
      Number_2_ON();
      dxl_wb.goalVelocity(DXL_ID_2,speed);
      dxl_wb.goalPosition(DXL_ID_2, (int32_t)307);
    }else if(200 <= analogValue && analogValue < 300){
      minuteNumber = 3;
      Number_3_ON();
      dxl_wb.goalVelocity(DXL_ID_2,speed);
      dxl_wb.goalPosition(DXL_ID_2, (int32_t)205);
    }else if(300 <= analogValue && analogValue < 400){
      minuteNumber = 4;
      Number_4_ON();
      dxl_wb.goalVelocity(DXL_ID_2,speed);
      dxl_wb.goalPosition(DXL_ID_2, (int32_t)102);
    }else if(400 <= analogValue && analogValue < 500){
      minuteNumber = 5;
      Number_5_ON();
      dxl_wb.goalVelocity(DXL_ID_2,speed);
      dxl_wb.goalPosition(DXL_ID_2, (int32_t)0);
    }
  }

  //秒針＋短針をまわす
  if(startRotation){
      //７セグメントの明かりを削除
      NumberOff();
      //長針が1分で一周する
      //短針がX分で元に戻る
      dxl_wb.wheelMode(DXL_ID_1);
      dxl_wb.goalSpeed(DXL_ID_1, 55|0x400);

    for (int count = minuteNumber - 1; count >= 0; count--)
    {
      delay(10000);
      dxl_wb.goalVelocity(DXL_ID_2,speed);
      dxl_wb.goalPosition(DXL_ID_2, minutePosition[count]);
    }
    timerFinish = true;
    dxl_wb.goalSpeed(DXL_ID_1,0);
  }

  if(timerFinish){
    startRotation = false;
    ShowTextF();
    delay(5000);
    NumberOff();
    SetUp();
    isTimerSet = false;
    timerFinish = false;
  }

}


/*
インターフェース
*/
void Number_0_ON(){
  digitalWrite(G, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(F, DIGIT_ON);      // digitPinをオンにする
  digitalWrite(E, DIGIT_ON);      // digitPinをオンにする
  digitalWrite(D, DIGIT_ON);      // digitPinをオンにする
  digitalWrite(A, DIGIT_ON);      // digitPinをオンにする
  digitalWrite(B, DIGIT_ON);      // digitPinをオンにする
  digitalWrite(C, DIGIT_ON);      // digitPinをオンにする

}


void Number_0_OFF(){
  digitalWrite(G, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(F, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(E, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(D, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(A, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(B, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(C, DIGIT_OFF);      // digitPinをオンにする

}

void Number_1_ON(){
  digitalWrite(G, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(F, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(E, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(D, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(A, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(B, DIGIT_ON);      // digitPinをオンにする
  digitalWrite(C, DIGIT_ON);      // digitPinをオンにする

}


void Number_1_OFF(){
  digitalWrite(G, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(F, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(E, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(D, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(A, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(B, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(C, DIGIT_OFF);      // digitPinをオンにする

}

void Number_2_ON(){
  digitalWrite(G, DIGIT_ON);      // digitPinをオンにする
  digitalWrite(F, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(E, DIGIT_ON);      // digitPinをオンにする
  digitalWrite(D, DIGIT_ON);      // digitPinをオンにする
  digitalWrite(A, DIGIT_ON);      // digitPinをオンにする
  digitalWrite(B, DIGIT_ON);      // digitPinをオンにする
  digitalWrite(C, DIGIT_OFF);      // digitPinをオンにする

}


void Number_2_OFF(){
  digitalWrite(G, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(F, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(E, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(D, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(A, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(B, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(C, DIGIT_OFF);      // digitPinをオンにする

}

void Number_3_ON(){
  digitalWrite(G, DIGIT_ON);      // digitPinをオンにする
  digitalWrite(F, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(E, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(D, DIGIT_ON);      // digitPinをオンにする
  digitalWrite(A, DIGIT_ON);      // digitPinをオンにする
  digitalWrite(B, DIGIT_ON);      // digitPinをオンにする
  digitalWrite(C, DIGIT_ON);      // digitPinをオンにする

}


void Number_3_OFF(){
  digitalWrite(G, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(F, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(E, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(D, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(A, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(B, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(C, DIGIT_OFF);      // digitPinをオンにする

}

void Number_4_ON(){
  digitalWrite(G, DIGIT_ON);      // digitPinをオンにする
  digitalWrite(F, DIGIT_ON);      // digitPinをオンにする
  digitalWrite(E, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(D, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(A, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(B, DIGIT_ON);      // digitPinをオンにする
  digitalWrite(C, DIGIT_ON);      // digitPinをオンにする

}


void Number_4_OFF(){
  digitalWrite(G, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(F, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(E, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(D, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(A, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(B, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(C, DIGIT_OFF);      // digitPinをオンにする

}

void Number_5_ON(){
  digitalWrite(G, DIGIT_ON);      // digitPinをオンにする
  digitalWrite(F, DIGIT_ON);      // digitPinをオンにする
  digitalWrite(E, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(D, DIGIT_ON);      // digitPinをオンにする
  digitalWrite(A, DIGIT_ON);      // digitPinをオンにする
  digitalWrite(B, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(C, DIGIT_ON);      // digitPinをオンにする

}


void Number_5_OFF(){
  digitalWrite(G, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(F, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(E, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(D, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(A, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(B, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(C, DIGIT_OFF);      // digitPinをオンにする

}

void Number_6_ON(){
  digitalWrite(G, DIGIT_ON);      // digitPinをオンにする
  digitalWrite(F, DIGIT_ON);      // digitPinをオンにする
  digitalWrite(E, DIGIT_ON);      // digitPinをオンにする
  digitalWrite(D, DIGIT_ON);      // digitPinをオンにする
  digitalWrite(A, DIGIT_ON);      // digitPinをオンにする
  digitalWrite(B, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(C, DIGIT_ON);      // digitPinをオンにする

}


void Number_6_OFF(){
  digitalWrite(G, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(F, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(E, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(D, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(A, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(B, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(C, DIGIT_OFF);      // digitPinをオンにする

}

void Number_7_ON(){
  digitalWrite(G, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(F, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(E, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(D, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(A, DIGIT_ON);      // digitPinをオンにする
  digitalWrite(B, DIGIT_ON);      // digitPinをオンにする
  digitalWrite(C, DIGIT_ON);      // digitPinをオンにする

}


void Number_7_OFF(){
  digitalWrite(G, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(F, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(E, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(D, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(A, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(B, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(C, DIGIT_OFF);      // digitPinをオンにする

}

void Number_8_ON(){
  digitalWrite(G, DIGIT_ON);      // digitPinをオンにする
  digitalWrite(F, DIGIT_ON);      // digitPinをオンにする
  digitalWrite(E, DIGIT_ON);      // digitPinをオンにする
  digitalWrite(D, DIGIT_ON);      // digitPinをオンにする
  digitalWrite(A, DIGIT_ON);      // digitPinをオンにする
  digitalWrite(B, DIGIT_ON);      // digitPinをオンにする
  digitalWrite(C, DIGIT_ON);      // digitPinをオンにする

}


void Number_8_OFF(){
  digitalWrite(G, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(F, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(E, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(D, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(A, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(B, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(C, DIGIT_OFF);      // digitPinをオンにする

}

void Number_9_ON(){
  digitalWrite(G, DIGIT_ON);      // digitPinをオンにする
  digitalWrite(F, DIGIT_ON);      // digitPinをオンにする
  digitalWrite(E, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(D, DIGIT_ON);      // digitPinをオンにする
  digitalWrite(A, DIGIT_ON);      // digitPinをオンにする
  digitalWrite(B, DIGIT_ON);      // digitPinをオンにする
  digitalWrite(C, DIGIT_ON);      // digitPinをオンにする

}


void Number_9_OFF(){
  digitalWrite(G, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(F, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(E, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(D, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(A, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(B, DIGIT_OFF);      // digitPinをオンにする
  digitalWrite(C, DIGIT_OFF);      // digitPinをオンにする

}

void NumberOff(){
  digitalWrite(G, DIGIT_OFF);    
  digitalWrite(F, DIGIT_OFF);    
  digitalWrite(E, DIGIT_OFF); 
  digitalWrite(D, DIGIT_OFF);   
  digitalWrite(A, DIGIT_OFF);   
  digitalWrite(B, DIGIT_OFF);  
  digitalWrite(C, DIGIT_OFF);   

}

void ShowTextF(){
  digitalWrite(G, DIGIT_ON);    
  digitalWrite(F, DIGIT_ON);    
  digitalWrite(E, DIGIT_ON); 
  digitalWrite(D, DIGIT_OFF);   
  digitalWrite(A, DIGIT_ON);   
  digitalWrite(B, DIGIT_OFF);  
  digitalWrite(C, DIGIT_OFF);   
}

void SetUp(){
  //初期設定
  dxl_wb.goalVelocity(DXL_ID_1,speed);
  dxl_wb.goalPosition(DXL_ID_1, (int32_t)512);
  dxl_wb.goalVelocity(DXL_ID_2,speed);
  dxl_wb.goalPosition(DXL_ID_2, (int32_t)512);
}


