#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>
#include <mavros_msgs/CommandTOL.h>
#include <mavros_msgs/CommandHome.h>
#include <mavros_msgs/PositionTarget.h>
#include <sensor_msgs/Range.h>
#include <iostream>
#include "opencv2/opencv.hpp"
#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include "geometry_msgs/PoseStamped.h"
using namespace cv;
using namespace std;

#define DEAD_AREA 15
float Height=0;//飞机高度
float Height_init=0;
float position_x=0;//图像返回的数据
float position_y=0;
float position_z=0;
float front_dis=0;//前置激光的距离数据
int height_flag=1;
vector<Point2f> crack_position;//裂纹位置
Point2f plan_path[5]={Point2f(0,110),Point2f(50,110),Point2f(50,0),Point2f(100,0),Point2f(100,110)};

//返回高度的数据
void pose_callback(const geometry_msgs::PoseStamped& msg)
{
	if(height_flag==0)
	{
		height_flag=1;
		Height_init=msg.pose.position.z;
	}
	Height=msg.pose.position.z-Height_init;
	ROS_INFO("Height  [%f]",Height);
}

//图像返回的数据
void drone_callback(const geometry_msgs::PoseStamped& msg)
{
	position_x=msg.pose.position.x;
	position_y=msg.pose.position.y;
	position_z=msg.pose.position.z;
	//ROS_INFO("video:%.2f , %.2f", msg.pose.position.x, msg.pose.position.y);
}

//前置激光的距离数据
void frontdis_callback(const sensor_msgs::Range& msg)
{
	front_dis=msg.range;
	ROS_INFO("distance:%.2f", front_dis);
}

int main(int argc,char **argv) 
{
	ros::init(argc,argv,"control");
//	ros::Rate loop_rate(1);
	ros::NodeHandle node_obj;
	ros::Publisher number_publisher1=node_obj.advertise<std_msgs::Int32>("/change_mode", 10);//向图像发送信息的话题
	ros::Publisher number_publisher2=node_obj.advertise<mavros_msgs::PositionTarget>("/mavros/setpoint_raw/local", 10);//向飞控发送信息的话题
	ros::Subscriber number_subscriber1 = node_obj.subscribe("/mavros/local_position/pose",10,pose_callback);//高度的话题
	ros::Subscriber number_subscriber2 = node_obj.subscribe("/mydrone",10,drone_callback);//接收图像的数据的话题
	ros::Subscriber number_subscriber3 = node_obj.subscribe("/mavros/distance_sensor/laser_pub",10,frontdis_callback);//前置激光距离的话题
	ros::spinOnce();
	ros::ServiceClient takeoff_client = node_obj.serviceClient<mavros_msgs::CommandTOL> ("mavros/cmd/takeoff");
	ros::ServiceClient landing_client = node_obj.serviceClient<mavros_msgs::CommandTOL> ("mavros/cmd/land");
	ros::ServiceClient set_mode_client = node_obj.serviceClient<mavros_msgs::SetMode> ("mavros/set_mode");
	ros::spinOnce();
	height_flag=0;
	while (ros::ok())
	{
	mavros_msgs::PositionTarget msg_position; //发送的消息
	msg_position.coordinate_frame = 12;
	msg_position.type_mask=1|2|4|64|128|256|512|1024|2048;
	msg_position.position.x=0.4;//RFU
	msg_position.position.y=0.5;
	msg_position.position.z=0.6;
	msg_position.velocity.x=0.7;//RFU
	msg_position.velocity.y=0.8;
	msg_position.velocity.z=0.9;	
	number_publisher2.publish(msg_position);
	ros::spinOnce();
//	loop_rate.sleep();
	usleep(1000000);
	}
	return 0;
}