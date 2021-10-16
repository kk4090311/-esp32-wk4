#include <Servo.h>  //匯入函式庫
Servo myservo;  // 建立伺服馬達控制
bool win=0;
const int servoPin = 13;  //用常態變數設定pin腳位，與之前define方式差不多
int pos = 90; //角度初始在中間，設定為90度
const int led_pin = 27;
int win_staus = 1;

const int Button1_Pin = 12, Button2_Pin = 14; //紀錄兩按鈕腳位
bool btn1_Pressed = false, btn2_Pressed = false;  //紀錄兩按鈕按壓狀態

void setup() {
  Serial.begin(115200);//序列阜連線速率(鮑率)
  
  myservo.attach(servoPin);  // 將伺服馬達連接的GPIO pin連接伺服物件
  myservo.write(pos);  //角度初始在中間，設定為90度
   pinMode(led_pin,OUTPUT);
   pinMode(Button1_Pin, INPUT);
   pinMode(Button2_Pin, INPUT);
   digitalWrite(led_pin,LOW);
}

void loop() 
{
int btn1_val=digitalRead(Button1_Pin);
int btn2_val=digitalRead(Button2_Pin);
    if (win==0)//no win
    {
   
      /*
      if (btn1_val==1)
      {
      Serial.print(",btn1=");
      Serial.println(btn1_val);
      }
      if (btn2_val==1)
      {
       Serial.print(",btn2=");
      Serial.println(btn2_val);
      }
      delay(20);
      */
       //Player 1
      if(btn1_val == HIGH && btn1_Pressed == false)
      {
        btn1_Pressed = true;
        pos += 5; //角度加五度
      }
      else if(btn1_val == LOW && btn1_Pressed == true)
      {
        btn1_Pressed = false;
      }
      
      //Player 2
      if(btn2_val == HIGH && btn2_Pressed == false)
      {
        btn2_Pressed = true;
        pos -= 5; //角度減五度
      }
      else if(btn2_val == LOW && btn2_Pressed == true)
      {
        btn2_Pressed = false;
      }
    
      Serial.println(pos);
      myservo.write(pos); //設定角度
      if (pos==0||pos==180)
      {
        win=1;
        
      }
    }
    else 
    {
      if( btn1_val == HIGH && btn2_val == HIGH)
      {
        win=0;
        pos=90;
        win_staus=0;
      }
      DoWin();
    }
}

void DoWin()
{
      digitalWrite(led_pin,win_staus); 
      if(win_staus== 1)
      win_staus=0;
      else win_staus=1; 
      delay(500-300*win_staus);
}
 
