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
char template_mps=0;
std_msgs::Byte cvtomp;
int summ=0,sum_x=0,sum_y=0,count_x=0,count_y=0,zone_x=0,zone_y=0;
int sum_dis=0,dis_xy[2];
float ave_x=0,ave_y=0,v_x=0,v_y=0,err_x=0,err_y=0;
float err_dis_x=0,err_dis_y=0,v_dis_x=0,v_dis_y=0,dis=0;
unsigned char bz_start=0,bz_send=0,bz_close=0;
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
	template_mps=msg.data;
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
    ros::Rate rate(20);
    geometry_msgs::PoseStamped msg_velocity;

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
    
    //under the mutex_lock traslate 
    pthread_mutex_lock(&mutex_mptocv);
    mpstate = template_mps;
    pthread_mutex_unlock(&mutex_mptocv);
	
    t = (double)cv::getTickCount();
    printf("bb");
    if(mpstate==1)
    {
	printf("cc");
	capture>>frame;
	printf("dd");
	Mat fff=frame.clone();
	rectangle(fff,Rect(240,147,180,180),Scalar(0,0,255),1,1,0);
	//imshow("ddd",fff);
	
	/*************second time added******************/
      Rect rec = Rect(240,147,180,180);
       img=frame(rec);
       Mat hsv;
       cvtColor(img, hsv, COLOR_BGR2HSV);//转为HSV
       Mat1b mask1,mask2;
       inRange(hsv,Scalar(0,120,50),Scalar(6,255,255),mask1);
       inRange(hsv,Scalar(174,120,50),Scalar(180,255,255),mask2);
       mask = mask1|mask2;
       Mat element = getStructuringElement(MORPH_RECT, Size(7,7));
       morphologyEx(mask, mask, MORPH_ERODE, element);
       int i_c=0,j_c=0;
        for (i_c = 0; i_c < mask.cols; ++i_c)
       {
           for (j_c = 0; j_c < mask.rows; ++j_c)
           {
               if(mask.at<uchar>(j_c,i_c)==255) {sum_y++;summ++;}
           }
           if(sum_y>=5)
           {
               sum_y=0;
               count_x++;
               zone_x+=i_c;
           }
           sum_y=0;
       }
       if(count_x!=0)
           ave_x=zone_x/count_x;
      
           for (j_c = 0; j_c < mask.rows; ++j_c)
       {
           for (i_c = 0; i_c < mask.cols; ++i_c)
           {
               if(mask.at<uchar>(j_c,i_c)==255) sum_x++;
           }
           if(sum_x>=5)
           {
               sum_x=0;
               count_y++;
               zone_y+=j_c;
           }
           sum_x=0;
       }
       if(count_y!=0)
           ave_y=zone_y/count_y;
	   
        zone_x=0;
	zone_y=0;
	count_x=0;
	count_y=0;

       err_x=((float)(mask.rows)/2)-ave_y;
       err_y=((float)(mask.cols)/2)-ave_x;
       v_x=err_x*0.0022;
       v_y=err_y*0.0022;
       if(v_x>0.2)    v_x=0.2;
       if(v_x<(-0.2)) v_x=-0.2;
       if(v_y>0.2)    v_y=0.2;
       if(v_y<(-0.2)) v_y=-0.2;
       //printf();
       circle(fff, Point(ave_x+240-v_y*300,ave_y+147-v_x*300), 3,Scalar(0,0,255),-1);
       circle(fff, Point(ave_x+240,ave_y+147), 3,Scalar(255,0,0),-1);
       imshow("ddd",fff);
       
       if(summ==0)  
            bz_close=0;

    if(bz_close==0)
    {
       if(summ>=200)
       {
            cvtomp.data=4;
		    number_publisher2.publish(cvtomp);
            bz_send=1;
       if((jdz(err_x)<=35)&&(jdz(err_y)<=35))
       {
           if(bz_start==0)
           {
               bz_start=1;
               timecount=0;
           }
           if(bz_start==1)
           {
                if(timecount>2.5)
                {
                    bz_start=0;
                    timecount=0;
                    bz_send=0;
                    bz_close=1;
                    cvtomp.data=2;
		            number_publisher2.publish(cvtomp);
                }  
           }
       }
       else
       {
           bz_start=0;
           timecount=0;
       }
       //imshow("111",mask);
       }
       else
       {
           cvtomp.data=2;
		    number_publisher2.publish(cvtomp);
       }
       //summ=0;

        if(bz_send==1)
       {
			msg_velocity.pose.position.x=v_x;
			msg_velocity.pose.position.y=v_y;
			msg_velocity.pose.position.z=0;
			tomain_publisher.publish(msg_velocity);
        }

    }
	imshow("111",mask);
	summ=0;
    waitKey(1);
    }
    
	
    t = ((double)cv::getTickCount() - t) / cv::getTickFrequency();
    fps = 1.0 / t;
    timecount+=t;
    //printf("FPS:%d//////miaoshu:%.4f\n",(int)fps,t);

   rate.sleep();
}
  return(0);
}

