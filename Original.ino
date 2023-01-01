/*
モーターを回す
*/

#include <DynamixelWorkbench.h>

#if defined(__OPENCM904__)
  #define DEVICE_NAME "/dev/cu.usbmodem21401" //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP
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

bool result;

void setup() 
{
  pinMode(analogInputPin, INPUT_ANALOG);
  pinMode(BOARD_BUTTON_PIN, INPUT_PULLDOWN);
  pinMode(BOARD_LED_PIN, OUTPUT);
  Serial.begin(115200);

  const char *log;
  result = false;

  uint16_t model_number = 0;


  //セットアップが完了しているかを3工程で確認する
  result = dxl_wb.init(DEVICE_NAME, BAUDRATE, &log);

  if (result == false)
  {
    Serial.println(log);
    Serial.println("Failed to init");
  }
  else
  {
    Serial.print("Succeeded to init : ");
    Serial.println(BAUDRATE);  
  }

  result = dxl_wb.ping(DXL_ID_1, &model_number, &log);
  if (result == false)
  {
    Serial.println(log);
    Serial.println("Failed to ping");
  }
  else
  {
    Serial.println("Succeeded to ping");
    Serial.print("id : ");
    Serial.print(dxl_id);
    Serial.print(" model_number : ");
    Serial.println(model_number);
  }

  result = dxl_wb.ping(DXL_ID_2, &model_number, &log);
  if (result == false)
  {
    Serial.println(log);
    Serial.println("Failed to ping");
  }
  else
  {
    Serial.println("Succeeded to ping");
    Serial.print("id : ");
    Serial.print(dxl_id);
    Serial.print(" model_number : ");
    Serial.println(model_number);
  }

  result = dxl_wb.jointMode(DXL_ID_1, 0, 0, &log);
  result = dxl_wb.jointMode(DXL_ID_2, 0, 0, &log);

  pinMode(G, OUTPUT);    // digitPinを出力モードに設定する
  pinMode(F, OUTPUT);    // digitPinを出力モードに設定する
  pinMode(E, OUTPUT);    // digitPinを出力モードに設定する
  pinMode(D, OUTPUT);    // digitPinを出力モードに設定する
  pinMode(A, OUTPUT);    // digitPinを出力モードに設定する
  pinMode(B, OUTPUT);    // digitPinを出力モードに設定する
  pinMode(C, OUTPUT);    // digitPinを出力モードに設定する

}


void loop() {
  int analogValue = analogRead(analogInputPin);
  int buttonState = digitalRead(BOARD_BUTTON_PIN);


  //セグメントを表示する

  
  //ボタンによるタイマーセット
  if(buttonState == HIGH){
    digitalWrite(BOARD_LED_PIN,LOW);
  }else{
    //ボタンが押されたとき
    digitalWrite(BOARD_LED_PIN,HIGH);
  }

  dxl_wb.goalVelocity(dxl_id,speed);
  dxl_wb.goalPosition(dxl_id, (int32_t)512);


  
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


