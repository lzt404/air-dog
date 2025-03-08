#include "serialPort/SerialPort.h"
#include <unistd.h>

MotorCmd cmd;
MotorData data;
MotorData motor_state[13];

SerialPort serial("/dev/ttyUSB0");

void all_init()
{
}

/**
 * @brief 将所有电机设置成零力矩模式
 *
 * @details
 * @param 无
 * @return 无
 */
void all_zero_moment_mode()
{
    cmd.motorType = MotorType::GO_M8010_6;
    cmd.mode = 1;
    cmd.K_P = 0.0;
    cmd.K_W = 0.0;
    cmd.Pos = 0.0;
    cmd.W = 0.0;
    cmd.T = 0.0;
    for (int i = 1; i <= 12; i++)
    {
        cmd.id = i;
        serial.sendRecv(&cmd, &data); // 发送数据并获取电机反馈数据
        usleep(200);
        if (data.correct)
        { // 接收到了电机的反馈数据
            if (data.MError != 0)
            { // 非零表示电机报错了,见手册第18页
                std::cerr << __FILE__ << __LINE__ << ":" << std::endl;
                std::cerr << "id:" << cmd.id << "  " << data.MError << std::endl;
                goto bad_;
            }
            std::cout << std::endl;
            std::cout << "motor.Pos : " << i << std::endl;
            std::cout << "motor.Pos: " << data.Pos << " rad" << std::endl;
            std::cout << "motor.Temp: " << data.Temp << " ℃" << std::endl;
            std::cout << "motor.W: " << data.W << " rad/s" << std::endl;
            std::cout << "motor.T: " << data.T << " N.m" << std::endl;
            std::cout << "motor.MError: " << data.MError << std::endl;
            std::cout << std::endl;
        }
        else
        {
            std::cerr << "有坏数据" << std::endl;
        }
    }

    std::cout << "all is ok" << std::endl;
    return;

bad_:
    return;
}

void speed_mode()
{
}
