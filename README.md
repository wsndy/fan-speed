L298N_fan.ino：
  用NANO通过L298N对风扇进行调速。
  
  风扇正负极接到L298N的电机接口1，NANO的D1/D2接L298N的IN1,IN2;D3接L298N的ENA。A0口接一个可调电位器，通过电阻的变化来调节风扇转速。
  
  这种方式对所有风扇适用。缺点是要占用3个IO口进行调速。
  
  如果发现电机转动方向不对，可互换电机引脚的两个定义接口。
  
  当使用电位器调节转速时，若电机不动，是因为电位器输入值太小，可转动电位器增大PWM值，电机就会转动。

pwm_fan.ino：（<b>推荐</b>）
  通过风扇的PWM接口进行调速，只占用1个io口，也可以再用另一个io口进行测速。   
