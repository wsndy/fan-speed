/*
  用NANO通过L298N对风扇进行调速。
  风扇正负极接到L298N的电机接口，这种方式对所有风扇适用。
  缺点是要占用6个IO口进行调速。
  如果发现电机转动方向不对，可互换电机引脚的两个定义接口
  当使用电位器调节转速时，若电机不动，是因为电位器输入值太小，可转动电位器增大PWM值，电机就会转动
*/
#define motor1pin1 1                             //定义IN1引脚
#define motor1pin2 2                              //定义IN2引脚
#define motor1pwm  3                            //定义ENA引脚,Arduino中PWM只能使用3，5，6，9，10，11引脚。8266所有引脚都支持PWM

//用电位器调节转速
#define Pot A0    //电位器输入引脚
int PotBuffer=0;  //电位器读取数据缓存
int Speed_PWM=0;  

void motor(int motorpin1,int motorpin2,int motorpwm,int val)  //定义一个电机转动函数
{
pinMode(motorpin1,OUTPUT);                              //输出第一个引脚
pinMode(motorpin2,OUTPUT);                              //输出第二个引脚
digitalWrite(motorpin2,0);                              //将第二个引脚置低
digitalWrite(motorpin1,1);                              //将第一个引脚抬高
analogWrite(motorpwm,val);                              //给EN引脚设定模拟值，设定转速
}

void setup()
{   
    pinMode(motor1pin1,OUTPUT);
    pinMode(motor1pin2,OUTPUT);
    pinMode(motor1pwm,OUTPUT);
    //设置端口为HIGH,电机保持不动 (都为LOW也可以，也是制动)
    digitalWrite(motor1pin1,HIGH);
    digitalWrite(motor1pin2,HIGH);
  Serial.begin(115200);  
}

void loop()
{
  PotBuffer=analogRead(Pot);  //读取AD值
  Speed_PWM=map(PotBuffer,0,1023,0,255);  //将AD值映射为PWM数值
  Serial.print("Speed_PWM=");
  Serial.println(Speed_PWM);
  motor(motor1pin1,motor1pin2,motor1pwm,Speed_PWM);          //电机A转速根据电位器转动而改变
}


