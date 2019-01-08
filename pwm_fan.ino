/*
  Arduino Nano 使用pwm调节4线风扇转速
  D5接风扇的PWM，D2接风扇的测速端口，a0口接一个可调电阻，通过改变电阻来调节风扇转速
*/
#define pwm  5         //定义pwm输出io
#define fan_speed  2   //测速端口
//用电位器调节转速
#define Pot A0         //电位器输入引脚
int PotBuffer = 0;     //电位器读取数据缓存
int Speed_PWM = 0;
unsigned long duration = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(pwm, OUTPUT);
  pinMode(fan_speed, INPUT);
}

void loop()
{
  PotBuffer = analogRead(Pot);                 //读取AD值
  Speed_PWM = map(PotBuffer, 0, 1023, 0, 255); //将AD值映射为PWM数值
  Serial.print("Speed_PWM=");
  Serial.print(Speed_PWM);
  //pwm输出，用可调电阻调节占空比0~255。Speed_PWM为0时风扇转速最高，大于235时风扇停止转动
  analogWrite(pwm, Speed_PWM );

  duration = 0;
  if (Speed_PWM < 230) {                    // 当风扇开始转动时，计算转速
    for (int i = 0; i < 5; i++) {           //高低电平变化5个周期（如果要精确的话，可以多取几次），取总计时间（微秒）
      duration += pulseIn(fan_speed, HIGH);
      duration += pulseIn(fan_speed, LOW);
    }
  } else {
    duration = 4294967295;          //如果风扇未转动，设置为unsigned long类型的最大值，让计算后风扇转速接近为0
  }
  duration = duration / 5;          //高低电平变化1次用时
  duration = 1000000 / duration;    // 1秒内可变化几次（即转化为风扇转速频率Hz）
  Serial.print("   f is ");
  Serial.print(duration);
  Serial.print(" HZ");
  duration = duration * 60;         //1分钟内可变化几次（即转换为风扇转速 转/分钟）
  Serial.print("  v is ");
  Serial.print(duration);
  Serial.println(" r/min");

  delay(500);
}


