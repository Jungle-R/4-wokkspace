#include "ros/ros.h"
#include "geometry_msgs/PoseStamped.h"
#include<opencv2/opencv.hpp>
#include <iostream>

#define PI 3.1415927

int g_houghcircles1 = 46;
int g_houghcircles2 = 90;
int g_houghcircles3 = 66;
int thresh = 110;
int threshold_type = 1;

using namespace cv;
using namespace std;

VideoCapture capture;
Mat srcImage;

Point find_cot();//定点

int main(int argc,char **argv) 
{
	ros::init(argc,argv,"find_circle");
	ros::NodeHandle node_obj;
	ros::Publisher number_publisher=node_obj.advertise<geometry_msgs::PoseStamped>("/mycircle", 10);//发送图像数据的话题
	ros::Rate loop_rate(20);
	
	FILE *inFile;
    inFile=fopen("/sys/class/video4linux/video0/name", "r");
	if (inFile)  //条件成立，则说明文件打开成功
	{
		char ch=fgetc(inFile);
		if(ch=='c')
		{
			capture.open(0);//打开摄像头
		}
		else
		{
			capture.open(2);//打开摄像头
		}
        fclose(inFile);
	}
    if(inFile==NULL)
	{
        cout << "无法打开文件！" << endl;
	}
	if (!capture.isOpened())//如果视频不能正常打开则返回
	{
		cout << "摄像头打开失败！" << endl;
		return 1;
	}
	
	capture.set(CAP_PROP_FPS, 20);

	while (1)
	{
		capture >> srcImage;//等价于 capture.read(frame);
		if (srcImage.empty())//如果某帧为空则退出循环
		{
			cout << "摄像头断开！" << endl;
			break;
		}
		Point circle=find_cot();//定点（最大轮廓检测）
		geometry_msgs::PoseStamped msg; //发送的消息
		//发送数据
		msg.pose.position.x = 160-circle.x;
		msg.pose.position.y = 120-circle.y;		
		if(circle==Point(-1,-1))
			msg.pose.position.z=1;
		else
			msg.pose.position.z=0;
		number_publisher.publish(msg);
		ros::spinOnce();
		loop_rate.sleep();
		waitKey(1);//每帧延时 1 毫秒，如果不延时，图像将无法显示
	}

	capture.release();//释放资源
	return 0;
}

//定点（最大轮廓检测）
Point find_cot()
{
	Mat grayImage, dstImage;
	Mat element;
	//改变图像大小
	resize(srcImage, srcImage, Size(320, 240), 0, 0, INTER_AREA);
	//创建窗口和滑动条
	createTrackbar("thresh", "thresh", &thresh, 255);
	createTrackbar("threshold_type", "thresh", &threshold_type, 4);
	createTrackbar("最小半径：", "dot", &g_houghcircles1, 300);
	createTrackbar("最大半径", "dot", &g_houghcircles2, 1000);
	createTrackbar("累加器阈值", "dot", &g_houghcircles3, 300);

	//阈值化
	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
	threshold(grayImage, dstImage, thresh, 255, threshold_type);
	//先开操作后闭操作去除噪点
	element = getStructuringElement(MORPH_RECT, Size(5, 5));
	morphologyEx(dstImage, dstImage, MORPH_OPEN, element);
	
	//检测轮廓
	vector<vector<Point>> contours;
	findContours(dstImage, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);

	//寻找最大轮廓
	int i, k;
	double length_max = 0;
	if (contours.size()>0)
	{
		k = 0;
		for (i = 0; i<contours.size(); i++)
		{

			if (arcLength(contours[i], 0)>length_max)
			{
				length_max = arcLength(contours[i], 0);
				k = i;
			}
		}
		//绘制最大轮廓
		drawContours(srcImage, contours, k, Scalar(122, 135, 255), 3);
		//cout<<length_max<<"     ";
		//如果轮廓过小，则返回识别不到
		if(length_max<300)
		{
			imshow("thresh", dstImage);
			imshow("dot", srcImage);
			return Point(-1,-1);
		}
		//进行霍夫圆变换
		vector<Vec3f> circles;
		HoughCircles(grayImage, circles, HOUGH_GRADIENT, 1.5, 100, 100, g_houghcircles3, g_houghcircles1, g_houghcircles2);
		int k_circle = 0;
		for (size_t i = 0; i < circles.size(); i++)
		{
			//参数定义
			Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
			int radius = cvRound(circles[i][2]);
			if (cvRound(circles[k_circle][2])<cvRound(circles[i][2]))//找出最大的圆
			{
				k_circle = i;
			}
			//绘制圆轮廓
			circle(srcImage, center, radius, Scalar(155, 50, 255), 2, 8, 0);
			//printf("%d,%d\n",center.x,center.y);
		}
		//画圆心
		if(circles.size()!=0)
		{
			//绘制圆心
			circle(srcImage, Point(cvRound(circles[k_circle][0]),cvRound(circles[k_circle][1])), 3, Scalar(0, 255, 0), -1, 8, 0);
			imshow("thresh", dstImage);
			imshow("dot", srcImage);
			return Point(cvRound(circles[k_circle][0]),cvRound(circles[k_circle][1]));
		}
	}

	imshow("thresh", dstImage);
	imshow("dot", srcImage);
	//没有闭合轮廓
	return Point(-1,-1);
}