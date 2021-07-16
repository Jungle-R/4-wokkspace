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
#include "std_msgs/Byte.h"
#include "std_msgs/Bool.h"
#include "geometry_msgs/PoseStamped.h"
#include "nav_msgs/Odometry.h"
#include <tf/transform_broadcaster.h>
#include   <sys/time.h>
#include <pthread.h>
pthread_mutex_t mutex_height;
pthread_mutex_t mutex_cam_data;
pthread_mutex_t mutex_t265;
pthread_mutex_t mutex_cvtomp;
using namespace cv;
using namespace std;
//RFU XYZ
float x_goal[7]={3.30,3.30,0.50,0.50,3.30,3.30,0.50},
      y_goal[7]={0,0.80,0.80,1.60,1.60,2.40,2.40};
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
struct   timeval   start,stop;
float Height=0;//飞机高度
float Height_init=0;
float x_distance=0;
float position_x=0;//图像返回的数据
float position_y=50;
float position_z=1;
float yaw_old=0;
float posz_t265=0;
float front_dis=0;//前置激光的距离数据
float line_position_red=0;//两个竿子的位置
float line_position_green=0;
int height_flag=1;
//int yaw_alined_flag=0;
int return_end_pitch=0;
int first_red_green=0;
int change_color=0;
Point2f init_position=Point2f(0,0);
Point2f now_position=Point2f(0,0);
vector<Point2f> crack_position;//裂纹位置
Point2f plan_path[5]={Point2f(0,0.9),Point2f(0.5,0.9),Point2f(0.5,0)};




float posx_t265=0;
float posy_t265=0;

float posx_t265_start=0;
float posy_t265_start=0;
float yaw_t265_start=0;
signed char state=-1;
bool video_ready=false;
bool button_ready=false;
bool t265_ready=false;
char cvstate=0;

int i=0;
int bz_x_1=0,bz_y_1=0,bz_2=0;

float max_xy(float xx,float yy)
{
	if(xx>=yy) return xx;
	else return yy;
}
float jdz(float jj)
{
	if(jj<0) jj=jj*(-1);
	return jj;
}
void sudu_xy(float xnow,float xgoal,float ynow,float ygoal,float sudu_xy[2])
{
	float x_v_a=0.3;
	float y_v_a=jdz(0.3*(ygoal-ynow)/(xgoal-xnow));
	if(xgoal-xnow>=0) sudu_xy[0]=x_v_a;
	if(xgoal-xnow<0) sudu_xy[0]=x_v_a*(-1);
	if(xgoal-xnow>=0) sudu_xy[1]=y_v_a;
	if(xgoal-xnow<0) sudu_xy[1]=y_v_a;
}
//返回高度的数据
float constrain_float(float x,float bound)
{
	if( x > bound )
		return bound;
	else if( x < -bound )
		return -bound;
	else return x;
}

void pose_callback(const geometry_msgs::PoseStamped& msg)
{
	if(height_flag==0)
	{
		height_flag=1;
		Height_init=msg.pose.position.z;
	}
	pthread_mutex_lock(&mutex_height);
	Height=msg.pose.position.z-Height_init;
	posx_t265=msg.pose.position.x;
	posy_t265=msg.pose.position.y;
	//x_distance=msg.pose.position.x;
	pthread_mutex_unlock(&mutex_height);
//	ROS_INFO("Height  [%f]",Height);
}

//图像返回的数据
void drone_callback(const geometry_msgs::PoseStamped& msg)
{
	video_ready=true;
	pthread_mutex_lock(&mutex_cam_data);
	position_x=msg.pose.position.x;
	position_y=msg.pose.position.y;
	//position_z=msg.pose.position.z;
	pthread_mutex_unlock(&mutex_cam_data);
//	ROS_INFO("video:%.2f , %.2f", msg.pose.position.x, msg.pose.position.z);
}


void cvtomp_callback(const std_msgs::Byte& msg)
{
	pthread_mutex_lock(&mutex_cvtomp);
	cvstate=msg.data;
	pthread_mutex_unlock(&mutex_cvtomp);
	//ROS_INFO("video:%.2f , %.2f", msg.pose.position.x, msg.pose.position.z);
}

void camera_callback(const nav_msgs::Odometry& msg)
{
	t265_ready=true;
	pthread_mutex_lock(&mutex_t265);
//	posx_t265=msg.pose.pose.position.x;
//	posy_t265=msg.pose.pose.position.y;
	posz_t265=msg.pose.pose.position.z;//added by ujj
	//Height=msg.pose.pose.position.z-posz_t265_start;//ujj
	pthread_mutex_unlock(&mutex_t265);
//ujj	ROS_INFO("video:%.2f , %.2f ,%.2f", msg.pose.position.x, msg.pose.position.y,msg.pose.position.z);
//		ROS_INFO("video:%.2f , %.2f ,%.2f", posx_t265,posy_t265,posz_t265);
}




//yaw数据
//void finish_callback(const std_msgs::Bool& msg)
//{
//	button_ready=msg.data;
////	ROS_INFO("video:%.2f , %.2f", msg.pose.position.x, msg.pose.position.y);
//}

int sleeptime=0;
int move_count=0;
int consistant_count=0;
unsigned int loop_timer=0;
int main(int argc,char **argv) 
{
	ros::init(argc,argv,"main_process");
	wiringPiSetup () ;
	pinMode (0, OUTPUT) ;
	digitalWrite (0, HIGH);
	pthread_mutex_init (&mutex_height, NULL);
	pthread_mutex_init (&mutex_cam_data, NULL);
	pthread_mutex_init (&mutex_t265, NULL);
	pthread_mutex_init (&mutex_cvtomp, NULL);
	
	ros::NodeHandle node_obj;
	ros::Publisher number_publisher2=node_obj.advertise<mavros_msgs::PositionTarget>("/mavros/setpoint_raw/local", 10);//向飞控发送信息的话题
	ros::Publisher number_publisher1=node_obj.advertise<std_msgs::Byte>("/my_change_mode", 10);//向图像发送信息的话题
	ros::Subscriber number_subscriber1 = node_obj.subscribe("/mavros/local_position/pose",10,pose_callback);//高度的话题
	ros::Subscriber number_subscriber2 = node_obj.subscribe("/mydrone",10,drone_callback);//接收图像的数据的话题
	ros::Subscriber number_subscriber3 = node_obj.subscribe("/camera/odom/sample",10,camera_callback);//接收角度数据的话题
	ros::Subscriber number_subscriber4 = node_obj.subscribe("/cvtomp",10,cvtomp_callback);
	ros::spinOnce();
	ros::ServiceClient takeoff_client = node_obj.serviceClient<mavros_msgs::CommandTOL> ("mavros/cmd/takeoff");
	ros::ServiceClient landing_client = node_obj.serviceClient<mavros_msgs::CommandTOL> ("mavros/cmd/land");
	ros::ServiceClient set_mode_client = node_obj.serviceClient<mavros_msgs::SetMode> ("mavros/set_mode");	
	ros::spinOnce();
	height_flag=0;
	//解锁
	ros::Rate rate(200);
	mavros_msgs::PositionTarget msg_velocity;
	std_msgs::Byte mptocv;
	mptocv.data = 1;
//	int count=0;
//	float start_now_diff_yaw;
	ros::AsyncSpinner spinner(3); 
	spinner.start();

	
	while(ros::ok( ))
	{
		
	//	ROS_INFO("loop_timer  [%d]",loop_timer);		
		if(++loop_timer>=10)
		{			
			pthread_mutex_lock(&mutex_cam_data);
			float goal_x_local=position_x;//图像返回的the goal speed
			float goal_y_local=position_y;
			//float goal_z_local=position_z;
			pthread_mutex_unlock(&mutex_cam_data);

			pthread_mutex_lock(&mutex_height);
			float Height_local=Height;
			float posx_t265_local=posx_t265;
			float posy_t265_local=posy_t265;
			pthread_mutex_unlock(&mutex_height);
						
			switch(state)
			{
			 ROS_INFO("State =  [%d]",state);
				case -1:
				{
					ROS_INFO("State -1");
					ROS_INFO("video_ready  [%d]",video_ready);
					ROS_INFO("t265_ready  [%d]",t265_ready);
						
					//if(video_ready&&t265_ready)
					if(t265_ready)
					{
						state=1;

						ROS_INFO("State 0");
					}
				}
				break;
						
				//若数据错误则重新解锁
				case 1:
				{
	
					if(++sleeptime>=60)
					{
						mptocv.data=50;
						number_publisher1.publish(mptocv);
						
						sleeptime=0;
						//state=2;
						ROS_INFO("State 2");
					}
					else
					    state=1;
				}
				break;
				//起飞
				case 2:
				{
					ROS_INFO("State 2");
					mavros_msgs::CommandTOL takeoff_cmd;
					takeoff_cmd.request.altitude = 1.50;//高度
					takeoff_cmd.request.longitude = 0;
					takeoff_cmd.request.latitude = 0;
					if(takeoff_client.call(takeoff_cmd))
					{
						state=3;
						ROS_INFO("State 3");
						ROS_INFO("TAKEOFF responce [%d] ",takeoff_cmd.response.success);
						ROS_INFO("TAKEOFF responce [%hhu] ",takeoff_cmd.response.result);
						
					}
					else
					state=2;
				}
				break;
				//定高，若高度到了设定值，则下一步

				case 3:
				{
					if(posz_t265>1.5)
					{
						state=4;
						ROS_INFO("State 4");
					}
					else
					state=3;
				}
				break;
				//wait & send command<go to the top>
				case 4:
				{
					if(++sleeptime>=60)    //15sec
					{
						sleeptime=0;
						//yaw_alined_flag=0;
						msg_velocity.coordinate_frame = 12;
						msg_velocity.type_mask=1|2|4|64|128|256|512|1024|2048;
						msg_velocity.velocity.x=0.3;
						msg_velocity.velocity.y=0;
						msg_velocity.velocity.z=0;
						//msg_velocity.yaw=0;
						number_publisher2.publish(msg_velocity);
						//open the camera
						mptocv.data=1;
						number_publisher1.publish(mptocv);
						state=5;
						ROS_INFO("State 5");
					}
					else
					    state=4;	
				}
				break;
				
				//judge whether finished or not
				case 5:
				{
          
					if(cvstate==2)
					{
						float su_xy[2];
						msg_velocity.type_mask=1|2|4|64|128|256|512|2048;
						sudu_xy(posx_t265_local,x_goal[i],posy_t265_local,y_goal[i],su_xy);
						msg_velocity.velocity.x=su_xy[0];
            msg_velocity.velocity.y=su_xy[1];
						msg_velocity.velocity.z=0;
            number_publisher2.publish(msg_velocity);
						if(jdz(posx_t265_local-x_goal[i])<=0.02) bz_x_1=2;
						
						if(jdz(posy_t265_local-y_goal[i])<=0.02)  bz_y_1=2;
						if((bz_y_1==2)&&(bz_x_1==2))
						{
							msg_velocity.type_mask=1|2|4|64|128|256|512|2048;
						msg_velocity.velocity.x=0;
						msg_velocity.velocity.y=0;
						msg_velocity.velocity.z=0;
						number_publisher2.publish(msg_velocity);
							if(++sleeptime>=30)
							{
								sleeptime=0;  
								bz_2=2;
							}
						}
						if(bz_2==2)
						{                         //还要加上延时函数
							i=i+1;
							bz_x_1=0;
							bz_y_1=0;
							bz_2=0;
						}
						if(i>=7)
						{
							i=0;
							state=6;
						  ROS_INFO("State 6");
							mptocv.data=2;
						  number_publisher1.publish(mptocv);
						}
					}


					else if(cvstate==3)
					{
					  msg_velocity.type_mask=1|2|4|64|128|256|512|2048;
						msg_velocity.velocity.x=goal_x_local;
            msg_velocity.velocity.y=goal_y_local;
						msg_velocity.velocity.z=0;
            number_publisher2.publish(msg_velocity);
					}

					else
					    state=5;
				}
				break;
				//wait&open the camera
				case 6:
				{
          if(cvstate==10)
          {
						msg_velocity.type_mask=1|2|4|64|128|256|512|2048;
						msg_velocity.velocity.x=goal_x_local;
            msg_velocity.velocity.y=goal_y_local;
						msg_velocity.velocity.z=0;
            number_publisher2.publish(msg_velocity);
					}
                            //延时在图像那边
					else if(cvstate==11)
          {
						msg_velocity.type_mask=8|16|32|64|128|256|512|2048;
						msg_velocity.position.x=-0.5;
            msg_velocity.position.y=0;
						msg_velocity.position.z=0;
            number_publisher2.publish(msg_velocity);
						state=7;
						ROS_INFO("State 7");
						mptocv.data=50;
						number_publisher1.publish(mptocv);
					}
					
					else 
					    state=6;
				}
				break;


				case 7:
				{
          if(++sleeptime>=70)  
					{
						sleeptime=0;
						msg_velocity.type_mask=8|16|32|64|128|256|512|2048;
						msg_velocity.position.x=0;
            msg_velocity.position.y=-2.8;
						msg_velocity.position.z=0;
            number_publisher2.publish(msg_velocity);
						state=8;
						ROS_INFO("State 8");
					}
					else
						state=7;
				}
				break;
				
				case 8:
				{
					if(++sleeptime>=80)
					{
						sleeptime=0;
						mavros_msgs::CommandTOL land_cmd;
						land_cmd.request.altitude = 0;
						land_cmd.request.longitude = 0;
						land_cmd.request.latitude = 0;
						if(landing_client.call(land_cmd))
						{
							state=50;
							ROS_INFO("State 50");
						}
					}
				}
				break;
				
			}
			loop_timer=0;
		}
//		ros::spinOnce();
		rate.sleep();
	}
	return 0;
}
