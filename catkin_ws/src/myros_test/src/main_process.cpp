#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>
#include <mavros_msgs/CommandTOL.h>
#include <mavros_msgs/CommandLong.h>
#include <mavros_msgs/CommandHome.h>
#include <mavros_msgs/PositionTarget.h>
#include <sensor_msgs/Range.h>
#include <iostream>
#include <stdio.h>
//#include <wiringPi.h>
#include "opencv2/opencv.hpp"
#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include "std_msgs/Byte.h"
#include "std_msgs/Bool.h"
#include "geometry_msgs/PoseStamped.h"
#include "nav_msgs/Odometry.h"
#include <tf/transform_broadcaster.h>
#include   <sys/time.h>
#include <pthread.h>
#include <mavros_msgs/State.h>


pthread_mutex_t mutex_t265;


using namespace cv;
using namespace std;

float yaw_old = 0;
float posz_t265 = 0;

float posx_t265 = 0;
float posy_t265 = 0;

float posz_t265_local = 0;
float posx_t265_start = 0;
float posy_t265_start = 0;
float yaw_t265_start = 0;
signed char state = -1;
int temp_step = 0;

bool t265_ready = false;



float constrain_float(float x, float bound)
{
	if (x > bound)
		return bound;
	else if (x < -bound)
		return -bound;
	else return x;
}

//返回高度的数据
float Height = 0;//飞机高度
float Height_init = 0;
int height_flag = 1;
pthread_mutex_t mutex_height;
void pose_callback(const geometry_msgs::PoseStamped& msg)
{
	if (height_flag == 0)
	{
		height_flag = 1;
		Height_init = msg.pose.position.z;
	}
	pthread_mutex_lock(&mutex_height);
	Height = msg.pose.position.z - Height_init;
	//posx_t265=msg.pose.position.y;
	//posy_t265=msg.pose.position.x;
	//x_distance=msg.pose.position.x;
	pthread_mutex_unlock(&mutex_height);
	//	ROS_INFO("Height  [%f]",Height);
}

//图像返回的数据
bool video_ready = false;
float position_x = 0;//图像返回的数据
float position_y = 50;
float position_z = 1;
pthread_mutex_t mutex_cam_data;
void drone_callback(const geometry_msgs::PoseStamped& msg)
{
	video_ready = true;
	pthread_mutex_lock(&mutex_cam_data);
	position_x = msg.pose.position.x;
	position_y = msg.pose.position.y;
	//position_z=msg.pose.position.z;
	pthread_mutex_unlock(&mutex_cam_data);
	//	ROS_INFO("video:%.2f , %.2f", msg.pose.position.x, msg.pose.position.z);
}

char cvstate = 0;
pthread_mutex_t mutex_cvtomp;
void cvtomp_callback(const std_msgs::Byte& msg)
{
	pthread_mutex_lock(&mutex_cvtomp);
	cvstate = msg.data;
	pthread_mutex_unlock(&mutex_cvtomp);
	//ROS_INFO("video:%.2f , %.2f", msg.pose.position.x, msg.pose.position.z);
}

void camera_callback(const nav_msgs::Odometry& msg)
{
	t265_ready = true;
	pthread_mutex_lock(&mutex_t265);
	posx_t265 = msg.pose.pose.position.x;
	posy_t265 = msg.pose.pose.position.y;
	posz_t265 = msg.pose.pose.position.z;//added by ujj
	//Height=msg.pose.pose.position.z-posz_t265_start;//ujj
	pthread_mutex_unlock(&mutex_t265);
	//ujj	ROS_INFO("video:%.2f , %.2f ,%.2f", msg.pose.position.x, msg.pose.position.y,msg.pose.position.z);
	//		ROS_INFO("video:%.2f , %.2f ,%.2f", posx_t265,posy_t265,posz_t265);
}

mavros_msgs::State current_state;
pthread_mutex_t mutex_State;
void state_cb(const mavros_msgs::State::ConstPtr& msg)
{
	pthread_mutex_lock(&mutex_State);
	current_state = *msg;
	pthread_mutex_unlock(&mutex_State);
}

int sleeptime = 0;
int move_count = 0;
int consistant_count = 0;
unsigned int loop_timer = 0;
int main(int argc, char** argv)
{
	ros::init(argc, argv, "main_process");
//	wiringPiSetup(); 	pinMode(0, OUTPUT);  digitalWrite(0, HIGH); //树莓派
	pthread_mutex_init(&mutex_height, NULL);
	pthread_mutex_init(&mutex_cam_data, NULL);
	pthread_mutex_init(&mutex_t265, NULL);
	pthread_mutex_init(&mutex_cvtomp, NULL);
	pthread_mutex_init(&mutex_State, NULL);

	ros::NodeHandle node_obj;
	ros::Publisher number_publisher1 = node_obj.advertise<std_msgs::Byte>("/my_change_mode", 10);//向图像发送信息的话题
	ros::Subscriber number_subscriber2 = node_obj.subscribe("/mydrone", 10, drone_callback);//接收图像的数据的话题
	ros::Subscriber number_subscriber4 = node_obj.subscribe("/cvtomp", 10, cvtomp_callback);

	ros::Subscriber number_subscriber3 = node_obj.subscribe("/camera/odom/sample", 10, camera_callback);//T265返回数据
	ros::Subscriber number_subscriber1 = node_obj.subscribe("/mavros/local_position/pose", 10, pose_callback);//飞控返回 的位置 
	ros::Subscriber state_sub = nh.subscribe<mavros_msgs::State>("mavros/state", 10, state_cb);//飞控返回的状态

	ros::spinOnce();

	ros::ServiceClient takeoff_client = node_obj.serviceClient<mavros_msgs::CommandTOL>("mavros/cmd/takeoff");//起飞
	ros::ServiceClient set_mode_client = node_obj.serviceClient<mavros_msgs::SetMode>("mavros/set_mode"); //进入35模式
	ros::Publisher number_publisher2 = node_obj.advertise<mavros_msgs::PositionTarget>("/mavros/setpoint_raw/local", 10);//向飞控发送命令
	ros::ServiceClient comand_long_client = node_obj.serviceClient<mavros_msgs::CommandLong>("mavros/cmd/command");	 //CMD命令
	ros::ServiceClient landing_client = node_obj.serviceClient<mavros_msgs::CommandTOL>("mavros/cmd/land"); //降落

	ros::spinOnce();
	height_flag = 0;

	ros::Rate rate(200);
	mavros_msgs::PositionTarget msg_velocity;
	std_msgs::Byte mptocv;
	mptocv.data = 1;

	ros::AsyncSpinner spinner(3);
	spinner.start();

	while (ros::ok())
	{
	
		if (++loop_timer >= 10)
		{
			pthread_mutex_lock(&mutex_cam_data);
			float goal_x_local = position_x;//图像返回的the goal speed
			float goal_y_local = position_y;
			//float goal_z_local=position_z;
			pthread_mutex_unlock(&mutex_cam_data);

			pthread_mutex_lock(&mutex_height);
			float Height_local = Height;
			float posx_t265_local = (-1) * posx_t265;
			float posy_t265_local = (-1) * posy_t265;
			pthread_mutex_unlock(&mutex_height);

			pthread_mutex_lock(&mutex_t265);
			//当前的角度、绝对坐标
			float posz_t265_local = posz_t265;//added by ujj
			pthread_mutex_unlock(&mutex_t265);

			switch (state)
			{

			//	ROS_INFO("State =  [%d]", state);

			case -1:
			{
				ROS_INFO("video_ready  [%d]", video_ready);
				ROS_INFO("t265_ready  [%d]", t265_ready);

				//if(video_ready&&t265_ready)
				if (t265_ready)  //是否不用等他
				{
					state++;
					ROS_INFO("*******T265 is Ready*******");
				}
				else
					state = -1;
			}
			break;

			//重启飞控、、
			case 0:
			{
				if (++sleeptime >= 20 && temp_step == 0) //秒数改
				{
					sleeptime = 0;
					mavros_msgs::CommandLong Reset_Sent_Cmd;
					Reset_Sent_Cmd.request.command = 0;
					Reset_Sent_Cmd.request.param1 = 0; //发送重新启动命令
					if (comand_long_client.call(Reset_Sent_Cmd))
					{
						ROS_INFO("***Reset_CMD is sent***");
						temp_step++;
					}
				}
				else if (++sleeptime >= 40 && temp_step) //2秒
				{
					sleeptime = 0;
					mavros_msgs::CommandLong Reset_Que_Cmd;
					Reset_Que_Cmd.request.command = 0;
					Reset_Que_Cmd.request.broadcast = 0;
					Reset_Que_Cmd.request.confirmation = 1;
					Reset_Que_Cmd.request.param1 = 1; //查询重新启动命令
					if (comand_long_client.call(Reset_Que_Cmd) && Reset_Que_Cmd.response.success)
					{
						temp_step = 0;
						ROS_INFO("***Reset Successfully***");
						state++;
					}
					else
					{
						ROS_INFO("***Waiting for reset ready***");

					}
					//++state;

				}
			}
			break;

			//
			case 1:
			{
				if (++sleeptime >= 20) //足够长的时间
				{
					sleeptime = 0;
					mavros_msgs::SetMode SetMode_Cmd;
					if (set_mode_client.call(SetMode_Cmd))
					{
						state = 50;
						ROS_INFO("State 100");
					}
				}
				else
					state = 1;
			}
			break;

			//起飞
			case 2:
			{
				ROS_INFO("State 2");
				mavros_msgs::CommandTOL takeoff_cmd;
				takeoff_cmd.request.altitude = 0.1;//高度
				takeoff_cmd.request.longitude = 0;
				takeoff_cmd.request.latitude = 0;
				//					if(takeoff_client.call(takeoff_cmd))
				{
					//						state=3;
					ROS_INFO("State 3");
					ROS_INFO("TAKEOFF responce [%d] ", takeoff_cmd.response.success);
					ROS_INFO("TAKEOFF responce [%hhu] ", takeoff_cmd.response.result);

				}
				//					else
				state = 2;
			}
			break;

			//定高，若高度到了设定值，则下一步
			case 3:
			{
				if (posz_t265_local > 0.1)
				{
					sleeptime = 0;
					state = 8;  //*********************ljj
					ROS_INFO("State 4");
				}
				else
					state = 3;
			}
			break;

			case 4:
			{
				state = 4;
			}
			break;

			case 5:
			{
				state = 5;
			}
			break;



			case 6:
			{
				state = 6;
			}
			break;


			case 7:
			{
				if (++sleeptime >= 20)
				{
					sleeptime = 0;
					msg_velocity.type_mask = 8 | 16 | 32 | 64 | 128 | 256 | 512 | 2048;
					msg_velocity.position.x = 0;
					msg_velocity.position.y = -2.5;
					msg_velocity.position.z = 0;
					msg_velocity.coordinate_frame = 0;
					number_publisher2.publish(msg_velocity);
					state = 8;
					ROS_INFO("State 8");
				}
				else
					state = 7;
			}
			break;

			case 8:
			{
				if (++sleeptime >= 160)
				{
					sleeptime = 0;
					mavros_msgs::CommandTOL land_cmd;
					land_cmd.request.altitude = 0;
					land_cmd.request.longitude = 0;
					land_cmd.request.latitude = 0;
					if (landing_client.call(land_cmd))
					{
						state = 50;
						ROS_INFO("State 50");
					}
				}
			}
			break;

			case 50:
			{
				if (++sleeptime >= 40)
				{
					sleeptime = 0;
					ROS_INFO("State 50");
				}
			}
			break;
			}
			loop_timer = 0;
		}
		rate.sleep();
	}
	return 0;
}

