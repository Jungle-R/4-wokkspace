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
using namespace cv;
using namespace std;
#define dis_max 100
#define dis_min 20
#define DEAD_AREA 15
#define PI 3.1415927
const float speed=15;
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
struct   timeval   start,stop;
float Height=0;//飞机高度
float Height_init=0;
float x_distance=0;
float position_x=0;//图像返回的数据
float position_y=50;
float position_z=1;
float yaw_old=0;
float front_dis=0;//前置激光的距离数据
float line_position_red=0;//两个竿子的位置
float line_position_green=0;
int height_flag=1;
int yaw_alined_flag=0;
int return_end_pitch=0;
int first_red_green=0;
int change_color=0;
Point2f init_position=Point2f(0,0);
Point2f now_position=Point2f(0,0);
vector<Point2f> crack_position;//裂纹位置
Point2f plan_path[5]={Point2f(0,0.9),Point2f(0.5,0.9),Point2f(0.5,0)};

float posx_t265=0;
float posy_t265=0;
float yaw=0;

float posx_t265_start=0;
float posy_t265_start=0;
float yaw_t265_start=0;
signed char state=-2;
bool video_ready=false;
bool button_ready=false;
bool t265_ready=false;


//返回高度的数据
float constrain_float( float x , float bound )
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
	position_z=msg.pose.position.z;
	pthread_mutex_unlock(&mutex_cam_data);
//	ROS_INFO("video:%.2f , %.2f", msg.pose.position.x, msg.pose.position.y);
}

//yaw数据
void camera_callback(const nav_msgs::Odometry& msg)
{
	t265_ready=true;
	pthread_mutex_lock(&mutex_t265);
	yaw = tf::getYaw(msg.pose.pose.orientation);
	posx_t265=msg.pose.pose.position.x;
	posy_t265=msg.pose.pose.position.y;
	pthread_mutex_unlock(&mutex_t265);
	//ROS_INFO("video:%.2f , %.2f", msg.pose.position.x, msg.pose.position.y);
}

//yaw数据
void switch_callback(const std_msgs::Bool& msg)
{
	button_ready=msg.data;
	//ROS_INFO("video:%.2f , %.2f", msg.pose.position.x, msg.pose.position.y);
}

int sleeptime=0;
int move_count=0;
int consistant_count=0;
unsigned int loop_timer=0;
int main(int argc,char **argv) 
{
	ros::init(argc,argv,"control");
	wiringPiSetup () ;
	pinMode (0, OUTPUT) ;
	digitalWrite (0, HIGH);
	pthread_mutex_init (&mutex_height, NULL);
	pthread_mutex_init (&mutex_cam_data, NULL);
	pthread_mutex_init (&mutex_t265, NULL);
	
	ros::NodeHandle node_obj;
	ros::Publisher number_publisher2=node_obj.advertise<mavros_msgs::PositionTarget>("/mavros/setpoint_raw/local", 10);//向飞控发送信息的话题
	ros::Publisher number_publisher1=node_obj.advertise<std_msgs::Byte>("/my_change_mode", 10);//向图像发送信息的话题
	ros::Publisher number_publisher3=node_obj.advertise<std_msgs::Byte>("/drone/beeper", 10);//beeper 
	ros::Subscriber number_subscriber1 = node_obj.subscribe("/mavros/local_position/pose",10,pose_callback);//高度的话题
	ros::Subscriber number_subscriber2 = node_obj.subscribe("/mydrone",10,drone_callback);//接收图像的数据的话题
	ros::Subscriber number_subscriber3 = node_obj.subscribe("/camera/odom/sample",10,camera_callback);//接收角度数据的话题
	ros::Subscriber number_subscriber4 = node_obj.subscribe("/drone/button",10,switch_callback);//接收开关数据
	ros::spinOnce();
	ros::ServiceClient takeoff_client = node_obj.serviceClient<mavros_msgs::CommandTOL> ("mavros/cmd/takeoff");
	ros::ServiceClient landing_client = node_obj.serviceClient<mavros_msgs::CommandTOL> ("mavros/cmd/land");
	ros::ServiceClient set_mode_client = node_obj.serviceClient<mavros_msgs::SetMode> ("mavros/set_mode");	
	ros::spinOnce();
	height_flag=0;
	//解锁
	ros::Rate rate(200);
	mavros_msgs::PositionTarget msg_velocity;
	std_msgs::Byte msg_img_mode;
	int count=0;
	float start_now_diff_yaw;
	float start_stop_diff_yaw;
	ros::AsyncSpinner spinner(3); 
	spinner.start();
	while(ros::ok( ))
	{
		if(++loop_timer>=10)
		{
			pthread_mutex_lock(&mutex_cam_data);
			float position_x_local=position_x;//图像返回的数据
			float position_y_local=position_y;
			float position_z_local=position_z;
			pthread_mutex_unlock(&mutex_cam_data);
			pthread_mutex_lock(&mutex_height);
			float Height_local=Height;
			pthread_mutex_unlock(&mutex_height);
			pthread_mutex_lock(&mutex_t265);
			//当前的角度、绝对坐标
			float yaw_local=yaw;
			float posx_t265_local=posx_t265;
			float posy_t265_local=posy_t265;
			pthread_mutex_unlock(&mutex_t265);			
			
			
			switch(state)
			{
				case -2:
				{
					if(video_ready&&t265_ready)
					{
						state=-1;
						std_msgs::Byte beeper;
						beeper.data=3;
						number_publisher3.publish(beeper);
						ROS_INFO("State -1");
					}
				}
				break;
				case -1:
				{
					if(button_ready)
					{
						std_msgs::Byte beeper;
						beeper.data=0;
						number_publisher3.publish(beeper);
						state=0;
						ROS_INFO("State 0");
					}
				}
				break;				
				//解锁
				case 0:
				{
					//记录初始的时候的参数值
					posx_t265_start=posx_t265_local;
					posy_t265_start=posy_t265_local;
					yaw_t265_start=yaw_local;
					mavros_msgs::SetMode offb_set_mode;
					offb_set_mode.request.custom_mode = "M36";
					if(set_mode_client.call(offb_set_mode))
					{
						state=1;
						ROS_INFO("State 1");
					}
					else
					state=0;
				}
				break;
				//若数据错误则重新解锁
				case 1:
				{
					if(++sleeptime>=60)
					{
						sleeptime=0;
						state=2;
						ROS_INFO("State 2");
					}
				}
				break;
				//起飞
				case 2:
				{
					mavros_msgs::CommandTOL takeoff_cmd;
					takeoff_cmd.request.altitude = 1.30;//高度
					takeoff_cmd.request.longitude = 0;
					takeoff_cmd.request.latitude = 0;
					if(takeoff_client.call(takeoff_cmd))
					{
						state=3;
						ROS_INFO("State 3");
					}
					else
					state=2;
				}
				break;
				//定高，若高度到了设定值，则下一步
				case 3:
				{
					if(Height>0.95)
					{
						state=4;
						ROS_INFO("State 4");
					}
					else
					state=3;
				}
				break;
				//定点
				case 4:
				{
					if(++sleeptime>=66)
					{
						sleeptime=0;
						yaw_alined_flag=0;
						state=5;
						ROS_INFO("State 5");
						//将模式转换为识别红色
						msg_img_mode.data=1;
						number_publisher1.publish(msg_img_mode);
					}	
				}
				break;
				//寻找哪个竿子在右边
				case 5:
				{
					//识别红色，转圈圈，标记角度
					msg_velocity.coordinate_frame = 12;
					msg_velocity.type_mask=1|2|4|8|16|32|64|128|256|512|1024;
					msg_velocity.yaw_rate=-PI/8.0;
					number_publisher2.publish(msg_velocity);
					//红色竿子在图像中间则记录角度
					float now_yaw_diss=abs(yaw_t265_start-yaw_local);
					if(now_yaw_diss>PI)
						now_yaw_diss=2*PI-now_yaw_diss;
					if(abs(position_x_local)<DEAD_AREA && !position_z_local)
					{
						line_position_red=now_yaw_diss;
					}
					if(now_yaw_diss>PI/2-0.18)
					{
						state=6;
						ROS_INFO("State 6");
						msg_img_mode.data=2;
						number_publisher1.publish(msg_img_mode);
					}
				}
				break;
				case 6:
				{
					//识别绿色，转圈圈，标记角度
					msg_velocity.coordinate_frame = 12;
					msg_velocity.type_mask=1|2|4|8|16|32|64|128|256|512|1024;
					msg_velocity.yaw_rate=PI/8.0;
					number_publisher2.publish(msg_velocity);
					//绿色竿子在图像中间则记录角度
					float now_yaw_diss=abs(yaw_t265_start-yaw_local);
					if(now_yaw_diss>PI)
						now_yaw_diss=2*PI-now_yaw_diss;
					if(abs(position_x_local)<DEAD_AREA && !position_z_local)
					{
						line_position_green=now_yaw_diss;
					}
					if(now_yaw_diss<0.18)
					{
						state=18;
						ROS_INFO("State 18");
						if(line_position_green<line_position_red)
							first_red_green=1;
						else
						{
							//如果是红色，则切图像模式
							msg_img_mode.data=1;
							number_publisher1.publish(msg_img_mode);
						}
					}
				}
				break;
				//寻找线的位置，调节yaw对准
				case 7:
				{
					if(position_z!=1)
					{
						msg_velocity.coordinate_frame = 12;
						msg_velocity.type_mask=1|2|4|8|16|32|64|128|256|512|1024;
						msg_velocity.velocity.x=0;
						if(abs(position_x_local)<DEAD_AREA)
							yaw_alined_flag=1;
						if(1==yaw_alined_flag)
						{
							msg_velocity.type_mask=1|2|4|32|64|128|256|512|1024;
							msg_velocity.velocity.y=constrain_float((position_y_local-50)/100.0,0.2);
						}
						
						msg_velocity.yaw_rate=-position_x_local/3.0/180.0;
						if(msg_velocity.yaw_rate>PI/6.0)
							msg_velocity.yaw_rate=PI/6.0;
						else if(msg_velocity.yaw_rate<-PI/6.0)
							msg_velocity.yaw_rate=-PI/6.0;
						//向飞控发送信息
						number_publisher2.publish(msg_velocity);
						//定准了则下一步
						if(abs(position_x_local)<DEAD_AREA&&abs(position_y_local-50)<DEAD_AREA/2.0)
						{
							count++;
							if(count>=10)
							{
								yaw_old=yaw;
								gettimeofday(&start,0);   
								state=8;
								ROS_INFO("State 8");
							}
						}
						else
							count=0;
						std_msgs::Byte beeper;
						beeper.data=(first_red_green==0?2:1);
						number_publisher3.publish(beeper);
					}

				}
				break;
				//开始转圈圈
				case 8:
				{
					if(position_z!=1)
					{
						msg_velocity.coordinate_frame = 12;
						msg_velocity.type_mask=1|2|4|32|64|128|256|512|1024;
						msg_velocity.velocity.x=speed/100.0;
						msg_velocity.velocity.y=constrain_float((position_y_local-50)/100.0,0.2);
						msg_velocity.yaw_rate=-position_x_local/3.0/180.0;
						if(msg_velocity.yaw_rate>PI/6.0)
							msg_velocity.yaw_rate=PI/6.0;
						else if(msg_velocity.yaw_rate<-PI/6.0)
							msg_velocity.yaw_rate=-PI/6.0;
						//如果是红色则顺时针转动
						if(first_red_green==0)
						{
							msg_velocity.yaw_rate+=speed/50.0;
							msg_velocity.velocity.x=-speed/100.0;
						}
						else
						{
							msg_velocity.yaw_rate-=speed/50.0;
						}
						//向飞控发送信息
						number_publisher2.publish(msg_velocity);
						gettimeofday(&stop,0);
						
						if(abs(yaw-yaw_old)<=0.18&&(stop.tv_sec-start.tv_sec)>=3*20/speed)
						{
								state=9;
								ROS_INFO("State 9");
						}
						else
							count=0;
					}

				}
				break;
				//将相对速度设置为0
				case 9:
				{
					msg_velocity.coordinate_frame = 12;
					msg_velocity.type_mask=1|2|4|32|64|128|256|512|1024;
					msg_velocity.yaw_rate=0;
					msg_velocity.velocity.x=0;
					msg_velocity.velocity.y=0;
					number_publisher2.publish(msg_velocity);
					std_msgs::Byte beeper;
					beeper.data=0;
					number_publisher3.publish(beeper);
					state=10;
					ROS_INFO("State 10");
				}
				break;
				//锁定，将相对坐标设置为0
				case 10:
				{
					msg_velocity.coordinate_frame = 12;
					msg_velocity.type_mask=4|8|16|32|64|128|256|512|2048;
					msg_velocity.yaw=0;
					msg_velocity.position.x=0;
					msg_velocity.position.y=0;
					number_publisher2.publish(msg_velocity);
					state=11;
					ROS_INFO("State 11");
				}
				break;
				//定几秒的样子
				case 11:
				{
					if(++sleeptime>=60)
					{
						sleeptime=0;
						state=16;
						ROS_INFO("State 16");
						count=0;
					}
				}
				break;
				//转向，朝向终点坐标方向
				case 12:
				{
					msg_velocity.coordinate_frame = 12;
					msg_velocity.type_mask=1|2|4|8|16|32|64|128|256|512|1024;
					//计算初始和当前yaw的角度差
					start_now_diff_yaw=abs(yaw_local-yaw_t265_start);
					if(start_now_diff_yaw>PI)
						start_now_diff_yaw=2*PI-start_now_diff_yaw;
					//计算初始和最终yaw的角度差
					start_stop_diff_yaw=abs(atan((posx_t265_local-posx_t265_start)/(1.73-posy_t265_start+posy_t265_local)));
					start_stop_diff_yaw+=PI/2;
					//计算当前转速
					msg_velocity.yaw_rate=(start_now_diff_yaw-start_stop_diff_yaw)/1.25;
					if(msg_velocity.yaw_rate>PI/6.0)
						msg_velocity.yaw_rate=PI/6.0;
					else if(msg_velocity.yaw_rate<-PI/6.0)
						msg_velocity.yaw_rate=-PI/6.0;
					//发送数据
					number_publisher2.publish(msg_velocity);
					if(abs(start_now_diff_yaw-start_stop_diff_yaw)<0.18)
					{
						count++;
						if(count>=15)
						{
							yaw_old=yaw;
							state=13;
							ROS_INFO("State 13");
						}
					}
					else
						count=0;
				}
				break;				
				//将相对速度设置为0
				case 13:
				{
					msg_velocity.coordinate_frame = 12;
					msg_velocity.type_mask=1|2|4|32|64|128|256|512|1024;
					msg_velocity.yaw_rate=0;
					msg_velocity.velocity.x=0;
					msg_velocity.velocity.y=0;
					number_publisher2.publish(msg_velocity);
					msg_img_mode.data=3;//切图像为定点模式
					number_publisher1.publish(msg_img_mode);
					state=14;
					ROS_INFO("State 14");
				}
				break;
				//锁定，将相对坐标设置为0
				case 14:
				{
					msg_velocity.coordinate_frame = 12;
					msg_velocity.type_mask=4|8|16|32|64|128|256|512|2048;
					msg_velocity.yaw=0;
					msg_velocity.position.x=0;
					msg_velocity.position.y=0;
					number_publisher2.publish(msg_velocity);
					state=19;
					ROS_INFO("State 19");
				}
				break;
				//降落
				case 15:
				{
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
				break;
				//判断识别了几根竿子，并作出选择
				case 16:
				{
					//如果只识别到了一根竿子
					if(change_color==0)
					{
						change_color=1;
						first_red_green=!first_red_green;
						//切换图像模式
						if(!first_red_green)
						{
							//切成红色
							msg_img_mode.data=1;
							number_publisher1.publish(msg_img_mode);
						}
						else
						{
							//切成绿色
							msg_img_mode.data=2;
							number_publisher1.publish(msg_img_mode);
						}
						state=17;
						ROS_INFO("State 17");
					}
					//如果两个竿子都识别过了
					else
					{
						state=12;
						ROS_INFO("State 12");
					}
				}
				break;
				case 17:
				{
					//转圈圈，找图像
					msg_velocity.coordinate_frame = 12;
					msg_velocity.type_mask=1|2|4|8|16|32|64|128|256|512|1024;
					msg_velocity.yaw_rate=-PI/8.0;
					number_publisher2.publish(msg_velocity);
					//如果找到图像
					if(abs(position_x_local)<DEAD_AREA && !position_z_local)
					{
						state=7;
						ROS_INFO("State 7");
						yaw_alined_flag=0;
					}
				}
				break;
				//巡检完之后找图像
				case 18:
				{
					//转圈圈，找线
					msg_velocity.coordinate_frame = 12;
					msg_velocity.type_mask=1|2|4|8|16|32|64|128|256|512|1024;
					msg_velocity.yaw_rate=-PI/8.0;
					number_publisher2.publish(msg_velocity);
					if(abs(position_x_local)<DEAD_AREA && !position_z_local)
					{
						state=7;
						ROS_INFO("State 7");
						yaw_alined_flag=0;
					}
				}
				break;
				case 19://接续14 向前 探测圆
				{
					if(++move_count<=8*20&&position_z_local)
					{
						msg_velocity.coordinate_frame = 12;
						msg_velocity.type_mask=1|2|4|32|64|128|256|512|1024;
						msg_velocity.yaw_rate=0;
						msg_velocity.velocity.x=0;
						msg_velocity.velocity.y=15;
						number_publisher2.publish(msg_velocity);
						consistant_count=0;
					}
					else if(!position_z_local)
					{
						if(++consistant_count>=3)
						{
							consistant_count=0;
							move_count=0;
							state=20;
							ROS_INFO("State 20");
						}
					}
					else if(move_count>8*20)
					{
						consistant_count=0;
						move_count=0;
						state=21;
						ROS_INFO("State 21");
					}
				}
				break;
				case 20://定圆
				{
						msg_velocity.coordinate_frame = 12;
						msg_velocity.type_mask=1|2|4|32|64|128|256|512|1024;
						msg_velocity.yaw_rate=0;
						msg_velocity.velocity.x=position_x_local/8.0/100.0;
						msg_velocity.velocity.y=position_y_local/8.0/100.0;
						number_publisher2.publish(msg_velocity);
					 if(abs(position_x_local)<DEAD_AREA&&abs(position_y_local)<DEAD_AREA)
					{
						state=21;
						ROS_INFO("State 21");
					}
				}
				break;
				case 21://将相对速度设置为0
				{
					msg_velocity.coordinate_frame = 12;
					msg_velocity.type_mask=1|2|4|32|64|128|256|512|1024;
					msg_velocity.yaw_rate=0;
					msg_velocity.velocity.x=0;
					msg_velocity.velocity.y=0;
					number_publisher2.publish(msg_velocity);
					state=22;
					ROS_INFO("State 22");
				}
				break;
				case 22://锁定，将相对坐标设置为0
				{
					msg_velocity.coordinate_frame = 12;
					msg_velocity.type_mask=4|8|16|32|64|128|256|512|2048;
					msg_velocity.yaw=0;
					msg_velocity.position.x=0;
					msg_velocity.position.y=0;
					number_publisher2.publish(msg_velocity);
					state=15;
					ROS_INFO("State 15");
				}
			}
			loop_timer=0;
		}
//		ros::spinOnce();
		rate.sleep();
	}
	return 0;
}