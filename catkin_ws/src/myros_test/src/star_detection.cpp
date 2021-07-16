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
#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include "std_msgs/Byte.h"
#include "std_msgs/Bool.h"
#include "geometry_msgs/PoseStamped.h"
#include "nav_msgs/Odometry.h"
#include <tf/transform_broadcaster.h>
#include <sys/time.h>
#include <pthread.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdlib.h>
#include <math.h>

using namespace cv;
using namespace std;
//pthread_mutex_t mutex_cam_data;
pthread_mutex_t mutex_mptocv;
/// Global variables

double t = 0,fps,timecount=0;
char mpstate=0;
std_msgs::Byte cvtomp;
int summ=0,sum_x=0,sum_y=0,count_x=0,count_y=0,zone_x=0,zone_y=0;
int sum_dis=0,dis_xy[2];
float ave_x=0,ave_y=0,v_x=0,v_y=0,err_x=0,err_y=0;
float err_dis_x=0,err_dis_y=0,v_dis_x=0,v_dis_y=0,dis=0;
unsigned char bz_start=0,bz_send=0;
Mat frame,img,src,binary;
Mat1b mask;

float jdz(float jj)
{
	if(jj<0) jj=jj*(-1);
	return jj;
}

void mptocv_callback(const std_msgs::Byte& msg)
{
	pthread_mutex_lock(&mutex_mptocv);
	mpstate=msg.data;
	pthread_mutex_unlock(&mutex_mptocv);
	ROS_INFO("video:%d" ,msg.data );
	//ROS_INFO("video:%.2f , %.2f", msg.pose.position.x, msg.pose.position.z);
}

int main(int argc,char **argv)
{
    ros::init(argc,argv,"star_detection");
    ros::NodeHandle node_obj;
	pthread_mutex_init (&mutex_mptocv, NULL);

    ros::Publisher tomain_publisher=node_obj.advertise<geometry_msgs::PoseStamped>("/mydrone", 10);//向飞控发送信息的话题???
    ros::Publisher number_publisher2=node_obj.advertise<std_msgs::Byte>("/cvtomp", 10);
    //ros::Publisher beeper_publisher=node_obj.advertise<std_msgs::Bool>("/drone/button", 10);
    ros::Subscriber number_subscriber1 = node_obj.subscribe("/my_change_mode",10,mptocv_callback);//高度的话题
    ros::Rate rate(2);
    mavros_msgs::PositionTarget msg_velocity;

     //打开一个默认的相机
    VideoCapture capture(0);
    printf("aa");
    //检查是否成功打开
    if (!capture.isOpened())
    {  printf("err");
        return -1;}

while(1)
{  
    ros::spinOnce();
    
	t = (double)cv::getTickCount();
	printf("bb");
    capture>>frame;
    printf("cc");
imshow("ddd",frame);
    waitKey(1);
	t = ((double)cv::getTickCount() - t) / cv::getTickFrequency();
              fps = 1.0 / t;
              timecount+=t;
              //printf("FPS:%d//////miaoshu:%.4f\n",(int)fps,t);

   rate.sleep();
}
  return(0);
}

