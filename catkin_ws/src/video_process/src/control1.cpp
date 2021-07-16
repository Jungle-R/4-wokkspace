#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>
#include <mavros_msgs/CommandTOL.h>
#include <mavros_msgs/CommandHome.h>
#include <mavros_msgs/PositionTarget.h>
#include <sensor_msgs/Range.h>
#include <iostream>
#include <stdio.h>
#include <wiringPi.h>
#include "opencv2/opencv.hpp"
#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include "geometry_msgs/PoseStamped.h"
using namespace cv;
using namespace std;
#define dis_max 100
#define dis_min 20
#define DEAD_AREA 15
//RFU XYZ
typedef enum POSITION_TARGET_TYPEMASK
{
   POSITION_TARGET_TYPEMASK_X_IGNORE=1, /* Ignore position x | */
   POSITION_TARGET_TYPEMASK_Y_IGNORE=2, /* Ignore position y | */
   POSITION_TARGET_TYPEMASK_Z_IGNORE=4, /* Ignore position z | */
   POSITION_TARGET_TYPEMASK_VX_IGNORE=8, /* Ignore velocity x | */
   POSITION_TARGET_TYPEMASK_VY_IGNORE=16, /* Ignore velocity y | */
   POSITION_TARGET_TYPEMASK_VZ_IGNORE=32, /* Ignore velocity z | */
   POSITION_TARGET_TYPEMASK_AX_IGNORE=64, /* Ignore acceleration x | */
   POSITION_TARGET_TYPEMASK_AY_IGNORE=128, /* Ignore acceleration y | */
   POSITION_TARGET_TYPEMASK_AZ_IGNORE=256, /* Ignore acceleration z | */
   POSITION_TARGET_TYPEMASK_FORCE_SET=512, /* Use force instead of acceleration | */
   POSITION_TARGET_TYPEMASK_YAW_IGNORE=1024, /* Ignore yaw | */
   POSITION_TARGET_TYPEMASK_YAW_RATE_IGNORE=2048, /* Ignore yaw rate | */
   POSITION_TARGET_TYPEMASK_ENUM_END=2049, /*  | */
} POSITION_TARGET_TYPEMASK;

float Height=0;//飞机高度
float Height_init=0;
float x_distance=0;
float position_x=0;//图像返回的数据
float position_y=0;
float position_z=0;
float front_dis=0;//前置激光的距离数据
int height_flag=1;
Point2f init_position=Point2f(0,0);
Point2f now_position=Point2f(0,0);
vector<Point2f> crack_position;//裂纹位置
Point2f plan_path[5]={Point2f(0,0.9),Point2f(0.5,0.9),Point2f(0.5,0)};

//返回高度的数据
void pose_callback(const geometry_msgs::PoseStamped& msg)
{
	if(height_flag==0)
	{
		height_flag=1;
		Height_init=msg.pose.position.z;
	}
	Height=msg.pose.position.z-Height_init;
	x_distance=msg.pose.position.x;
//	ROS_INFO("Height  [%f]",Height);
}

//图像返回的数据
void drone_callback(const geometry_msgs::PoseStamped& msg)
{
	position_x=msg.pose.position.x;
	position_y=msg.pose.position.y;
	position_z=msg.pose.position.z;
	//ROS_INFO("video:%.2f , %.2f", msg.pose.position.x, msg.pose.position.y);
}


int main(int argc,char **argv) 
{
	ros::init(argc,argv,"control");
	wiringPiSetup () ;
	pinMode (0, OUTPUT) ;
	digitalWrite (0, HIGH);
	ros::NodeHandle node_obj;
	ros::Publisher number_publisher2=node_obj.advertise<mavros_msgs::PositionTarget>("/mavros/setpoint_raw/local", 10);//向飞控发送信息的话题
	ros::Subscriber number_subscriber1 = node_obj.subscribe("/mavros/local_position/pose",10,pose_callback);//高度的话题
	ros::Subscriber number_subscriber2 = node_obj.subscribe("/mydrone",10,drone_callback);//接收图像的数据的话题
	ros::spinOnce();
	ros::ServiceClient takeoff_client = node_obj.serviceClient<mavros_msgs::CommandTOL> ("mavros/cmd/takeoff");
	ros::ServiceClient landing_client = node_obj.serviceClient<mavros_msgs::CommandTOL> ("mavros/cmd/land");
	ros::ServiceClient set_mode_client = node_obj.serviceClient<mavros_msgs::SetMode> ("mavros/set_mode");
	ros::spinOnce();
	height_flag=0;
	//解锁
	ros::Rate rate(20);
	mavros_msgs::SetMode offb_set_mode;
	offb_set_mode.request.custom_mode = "M36";
	while( !(set_mode_client.call(offb_set_mode)))
	{
		ros::spinOnce();
		usleep(1000000);
		//rate.sleep();
	}
	ROS_INFO("mode set");
	usleep(500000);
	ros::spinOnce();
	usleep(500000);
	
	//起飞
	mavros_msgs::CommandTOL takeoff_cmd;
	takeoff_cmd.request.altitude = 1.0;//高度
	takeoff_cmd.request.longitude = 0;
	takeoff_cmd.request.latitude = 0;
	ros::spinOnce();
	while( !(takeoff_client.call(takeoff_cmd)))
	{
		ros::spinOnce();
		usleep(1000000);
		//rate.sleep();
	}
	while(Height<0.95)
	{
		usleep(1000);
		ros::spinOnce();
	}
	ROS_INFO("in air");
	//悬停5s
	usleep(5000000);
	mavros_msgs::PositionTarget msg_velocity;
	int count=0;
	while(1)
	{
		if(position_x!=160)
		{
			msg_velocity.coordinate_frame = 12;
			msg_velocity.type_mask=1|2|4|8|16|32|64|128|256|512|1024;
//			msg_velocity.velocity.x=-position_x/3.0/100.0;
//			if(msg_velocity.velocity.x>0.2)
//				msg_velocity.velocity.x=0.2;
//			else if(msg_velocity.velocity.x<-0.2)
//				msg_velocity.velocity.x=-0.2;
			msg_velocity.yaw_rate=-position_x/6.0/180.0;
			if(msg_velocity.yaw_rate>3.14/6.0)
				msg_velocity.yaw_rate=3.14/6.0;
			else if(msg_velocity.yaw_rate<-3.14/6.0)
				msg_velocity.yaw_rate=-3.14/6.0;
	//		msg_velocity.velocity.y=(front_dis-0.55)/3.5;
	//		if(msg_velocity.velocity.y>0.15)
	//			msg_velocity.velocity.y=0.15;
	//		else if(msg_velocity.velocity.y<-0.15)
	//			msg_velocity.velocity.y=-0.15;
//			msg_velocity.velocity.y=0;
//			msg_velocity.velocity.z=0;
			//向飞控发送信息
			number_publisher2.publish(msg_velocity);
		}
		usleep(50000);
		ros::spinOnce();
		if(abs(position_x)*3*100<DEAD_AREA)
		{
			count++;
			if(count>=30)
			{
				msg_velocity.coordinate_frame = 12;
				msg_velocity.type_mask=1|2|4|8|16|32|64|128|256|512|2048;
				msg_velocity.yaw=0;
				number_publisher2.publish(msg_velocity);
				ros::spinOnce();
				break;
			}
		}
		else
			count=0;
	}
	//降落
	mavros_msgs::CommandTOL land_cmd;
	land_cmd.request.altitude = 0;
	land_cmd.request.longitude = 0;
	land_cmd.request.latitude = 0;
	while( !(landing_client.call(land_cmd)))
	{
		ros::spinOnce();
		rate.sleep();
	}
	
	return 0;
	
}