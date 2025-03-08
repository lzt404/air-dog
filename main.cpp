#include "serialPort/SerialPort.h"
#include <unistd.h>

#include "misc.h"

void set_motor_static(int a_id) {
  cmd.id = a_id;
  cmd.K_P = 0.0;
  cmd.K_W = 0.0;
  cmd.Pos = 0.0;
  cmd.W = 0.0;
  cmd.T = 0.0;
  serial.sendRecv(&cmd, &data); // 发送数据并获取电机反馈数据
  usleep(200);
  cmd.Pos = data.Pos;
  cmd.K_P = 15;
  serial.sendRecv(&cmd, &data); // 发送数据并获取电机反馈数据
  usleep(200);
}

int main()
{
  all_zero_moment_mode();
  //零力矩获取电机状态
  while (1);
  
  for (int i = 1; i <= 12; i ++) 
  {
    set_motor_static(i);
  }
  while(1);

  while (1) {
    
    
    if (data.correct) { //成功收到反馈数据
      if(data.MError == 0) {
        std::cout << std::endl;
        std::cout << "motor.id : " << cmd.id << std::endl;
        std::cout << "motor.Pos: " << data.Pos << " rad" << std::endl;
        std::cout << "motor.Temp: " << data.Temp << " ℃" << std::endl;
        std::cout << "motor.W: " << data.W << " rad/s" << std::endl;
        std::cout << "motor.T: " << data.T << " N.m" << std::endl;
        std::cout << "motor.MError: " << data.MError << std::endl;
        std::cout << std::endl;
      }
      else {
        std::cerr << "电机报错!!!!!!" << std::endl;
        while (1) {all_zero_moment_mode();}
      }
    }
  }
    
  // //
  // if (data.correct) {
  //   cmd.Pos = data.Pos;
  // }

  // while(true) {

  //   //位置模式
  //   // cmd.T = 0.0;
  //   // cmd.W = 0.0;
  //   // cmd.Pos = 3.14*6.33;
  //   // cmd.K_P = 0.02;
  //   // cmd.K_W = 0.0;

  //   cmd.T = 0.0;
  //   cmd.W = 6.28*6.33*1.5;
  //   cmd.Pos = 0.0;
  //   cmd.K_P = 0.0;
  //   cmd.K_W = 0.02;

  //   serial.sendRecv(&cmd,&data);

  //   if(data.correct == true)
  //   {
  //     std::cout <<  std::endl;
  //     std::cout <<  "motor.Pos: "    << data.Pos    << " rad" << std::endl;
  //     std::cout <<  "motor.Temp: "   << data.Temp   << " ℃"  << std::endl;
  //     std::cout <<  "motor.W: "      << data.W      << " rad/s"<<std::endl;
  //     std::cout <<  "motor.T: "      << data.T      << " N.m" << std::endl;
  //     std::cout <<  "motor.MError: " << data.MError <<  std::endl;
  //     std::cout <<  std::endl;
  //   }
  //   uint8_t *p = (uint8_t *)cmd.get_motor_send_data();
  //   for(int i =0; i<17; i++)
  //   printf("0X%02X ", *p++);

  //   usleep(200);

  // }
}
