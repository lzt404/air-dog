#include "serialPort/SerialPort.h"
#include <unistd.h>
#include <iostream>
#include "misc.h"
#include <chrono>
#include <iomanip>
#include <ctime>
#include <fstream>

#define stop_program() while(1)

void set_motor_static(int a_id) {
  float first_data;
  cmd.id = a_id;
  cmd.K_P = 0.0;
  cmd.K_W = 0.0;
  cmd.Pos = 0.0;
  cmd.W = 0.0;
  cmd.T = 0.0;
  serial.sendRecv(&cmd, &data); // 发送数据并获取电机反馈数据
  std::cout << std::endl;
  std::cout << "motor.id : " << cmd.id << std::endl;
  std::cout << "motor.Pos: " << data.Pos << " rad" << std::endl;
  std::cout << "motor.Temp: " << data.Temp << " ℃" << std::endl;
  std::cout << "motor.W: " << data.W << " rad/s" << std::endl;
  std::cout << "motor.T: " << data.T << " N.m" << std::endl;
  std::cout << "motor.MError: " << data.MError << std::endl;
  std::cout << std::endl;
  usleep(500);
  
  if(data.correct) {
    cmd.Pos = data.Pos;
    cmd.K_P = 15.0;
    first_data = data.Pos;
  }
  else {
    std::cerr << "错误数据" << std::endl;
    std::cout << __FILE__ << __LINE__ << std::endl;
    while(1);
  }

  while (1) {
    serial.sendRecv(&cmd, &data); // 发送数据并获取电机反馈数据
    if(data.correct) {
      std::cout << "数据正常" << std::endl;
    }
    else {
      std::cerr << "错误数据" << std::endl;
      std::cout << __FILE__ << __LINE__ << std::endl;
      while(1);
    }
    //std::cout << std::endl;
    std::cout << "motor.id : " << cmd.id << std::endl;
    std::cout << "motor.Pos: " << data.Pos << " rad" << std::endl;
    std::cout << "first_data: " << first_data << " rad" << std::endl;
    std::cout << "motor.Temp: " << data.Temp << " ℃" << std::endl;
    std::cout << "motor.W: " << data.W << " rad/s" << std::endl;
    std::cout << "motor.T: " << data.T << " N.m" << std::endl;
    std::cout << "motor.MError: " << data.MError << std::endl;
    std::cout << std::endl;
    usleep(500);
  }
    
  
}

float raw_pos[16];

int main()
{
  // 获取当前时间点
  auto now = std::chrono::system_clock::now();

  // 转换为时间戳（time_t）
  std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);

  // 转换为本地时间
  std::tm now_tm = *std::localtime(&now_time_t);

  // 生成文件名
  char filename[100];
  std::strftime(filename, sizeof(filename), "/home/dog/air-dog/log_%Y-%m-%d_%H-%M-%S.txt", &now_tm);

  // 打开文件
  std::ofstream outfile(filename);
  if (!outfile.is_open()) {
      std::cerr << "Failed to open file: " << filename << std::endl;
      return 1;
  }
  
  float target = 0.1;
  // for(int i = 1; i <= 12;  i ++) {
  //   set_zero_moment_mode(i);
  //   cmd.id = i;
  //   while (1) {
  //     cmd.T = target;
  //     cmd.W = 0.0;
  //     raw_pos[i] = data.Pos;
  //     cmd.Pos = data.Pos;
  //     cmd.K_P = 5.0;
  //     cmd.K_W = 0.0;
  //     serial.sendRecv(&cmd, &data);
  //     usleep(200);
  //     target += 0.1;
  //     if(1.5f - target < 0.0) {
  //       break;
  //     }
  //   }
  // }

  while (1) {
    for(int i = 1; i <= 12;  i ++) {
      cmd.id = i;
      cmd.T = 0.0f;
      cmd.W = 0.0f;
      cmd.Pos = raw_pos[i];
      cmd.K_P = 0.0f;
      cmd.K_W = 0.0f;
      serial.sendRecv(&cmd, &data);
      if(data.correct) {
        std::cout << "ID是:" << std::setw(2) << std::setfill(' ') << cmd.id << "     ";
        std::cout << "现在pos是:" << data.Pos << "     ";
        std::cout << "原始pos是:"  << raw_pos[i] << std::endl;
        
        outfile << "ID是:" << std::setw(2) << std::setfill(' ') << cmd.id << "     ";
        outfile << "现在pos是:" << data.Pos << "     ";
        outfile << "原始pos是:"  << raw_pos[i] << std::endl;
        
      }
      usleep(200);
      std::cout <<  std::endl;
      std::cout <<  std::endl;

      outfile <<  std::endl;
      outfile <<  std::endl;
    }
  }
  
  
  outfile.close();
  stop_program();
  //零力矩获取电机状态
  // while (1);

  

  set_motor_static(3);
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
