#include <sensor_msgs/Range.h>
#include <iostream>
#include <stdio.h>
#include <wiringPi.h>
#include "opencv2/opencv.hpp"
#include "ros/ros.h"
#include "std_msgs/Float32.h"
#include "geometry_msgs/PoseStamped.h"
#include "nav_msgs/Odometry.h"
using namespace std;
ros::Publisher number_publisher1;
float position_y=0;
//图像返回的数据
#define NCoef 2
float iir(float NewSample) {
    float ACoef[NCoef+1] = {
        0.06745527606901530200,
        0.13491055213803060000,
        0.06745527606901530200
    };

    float BCoef[NCoef+1] = {
        1.00000000000000000000,
        -1.14298050253990090000,
        0.41280159809618860000
    };

    static float y[NCoef+1]; //output samples
    static float x[NCoef+1]; //input samples
    int n;

    //shift the old samples
    for(n=NCoef; n>0; n--) {
       x[n] = x[n-1];
       y[n] = y[n-1];
    }

    //Calculate the new output
    x[0] = NewSample;
    y[0] = ACoef[0] * x[0];
    for(n=1; n<=NCoef; n++)
        y[0] += ACoef[n] * x[n] - BCoef[n] * y[n];
    
    return y[0];
}


void drone_callback(const geometry_msgs::PoseStamped& msg)
{
	std_msgs::Float32 dis;
	position_y=msg.pose.position.y;
	dis.data=iir(position_y);
	number_publisher1.publish(dis);
	
	//ROS_INFO("video:%.2f , %.2f", msg.pose.position.x, msg.pose.position.y);
}
int main(int argc,char **argv) 
{
	ros::init(argc,argv,"filter");
	ros::NodeHandle node_obj;
	number_publisher1=node_obj.advertise<std_msgs::Float32>("/filtered", 10);
	ros::Subscriber number_subscriber1 = node_obj.subscribe("/mydrone",10,drone_callback);
	ros::spin();
}