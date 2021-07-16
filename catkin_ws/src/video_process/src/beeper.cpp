#include "ros/ros.h"
#include "std_msgs/Byte.h"
#include "std_msgs/Bool.h"
#include <wiringPi.h>
#include <stdio.h>
#include <unistd.h>
void beeper_callback(const std_msgs::Byte& msg)
{
	if(msg.data==0) //off
	{
		digitalWrite (25, LOW);
		digitalWrite (27, LOW);
		digitalWrite (0, HIGH);
	}
	if(msg.data==1)//green
	{
		digitalWrite (0, LOW);
		digitalWrite (25, HIGH);
		digitalWrite (27, LOW);
	}
	if(msg.data==2)//red
	{
		digitalWrite (0, LOW);
		digitalWrite (27, HIGH);
		digitalWrite (25, LOW);
	}
	if(msg.data==3)//red
	{
		digitalWrite (0, HIGH);
		digitalWrite (27, HIGH);
		digitalWrite (25, HIGH);
	}
	
}

int main(int argc,char **argv) 
{
	ros::init(argc,argv,"beeper");
	ros::NodeHandle node_obj;
	ros::Rate loop_rate(50);
	wiringPiSetup () ;
	pinMode (0, OUTPUT) ;
	digitalWrite (0, HIGH);
	pinMode (25, OUTPUT) ;//green
	digitalWrite (25, LOW);
	pinMode (27, OUTPUT) ;//red
	digitalWrite (27, LOW);
	pinMode (22, INPUT); // 设置按钮引脚为输入
    pullUpDnControl (22, PUD_UP); // 接按钮的引脚设置成上拉
	ros::Subscriber beeper_subscriber= node_obj.subscribe("/drone/beeper",10,beeper_callback);
	ros::Publisher 	beeper_publisher=node_obj.advertise<std_msgs::Bool>("/drone/button", 10);
	while (ros::ok())
	{
		ros::spinOnce();
		if(digitalRead(22) == 0){ // 检测到低电平
        delay(20); // 延时销抖
        if(digitalRead(22) == 0){ // 检测到低电平
		std_msgs::Bool button;
		button.data=true;
		beeper_publisher.publish(button);	// 发消息
        }
		}
		loop_rate.sleep();
	}
	return 0;
}
