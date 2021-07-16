#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include "geometry_msgs/PoseStamped.h"
#include "opencv2/opencv.hpp"
#include <iostream>
#include "std_msgs/Byte.h"
#define PI 3.1415927
#define TRANSFERR 1200
#define LINE_DEAD_AREA 10

using namespace cv;
using namespace std;

VideoCapture capture;
Mat srcImage;
int iLowH = 155;
int iHighH = 179;
int iLowS = 50;
int iHighS = 245;
int iLowV = 50;
int iHighV = 245;
int g_cannyLowThreshold = 20;
int g_houghlines1 = 80;
int g_houghlines2 = 50;
int g_houghlines3 = 10;
int g_houghcircles1 = 46;
int g_houghcircles2 = 90;
int g_houghcircles3 = 66;
int thresh = 110;
int threshold_type = 1;
int line_mode=1;
float position_x=0;//中心点的水平偏移量
float position_y=0;//距离值
float position_z=0;//没有识别到线则发1

void find_line();//寻找奇怪颜色的线
Point3f minor_line(Mat imgThresholded);//缩小像素点的霍夫线变换
void find_cot();//定点

void mode_callback(const std_msgs::Byte& msg)
{
	line_mode=msg.data;
}

int main(int argc,char **argv) 
{
	ros::init(argc,argv,"crackdetection");
	ros::NodeHandle node_obj;
	ros::Publisher number_publisher=node_obj.advertise<geometry_msgs::PoseStamped>("/mydrone", 10);//发送图像数据的话题
	ros::Subscriber number_subscriber = node_obj.subscribe("/my_change_mode",10,mode_callback);//高度的话题
	ros::Rate loop_rate(30);
	
	FILE *inFile;
    inFile=fopen("/sys/class/video4linux/video0/name", "r");
	if (inFile)  //条件成立，则说明文件打开成功
	{
		char ch=fgetc(inFile);
		if(ch=='c')
		{
			capture.open(1);//打开摄像头
		}
		else
		{
			capture.open(0);//打开摄像头
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
	capture.set(CAP_PROP_FPS, 15);

	//巡线
	while (1)
	{
		if(line_mode==3)
			break;
		double fps;//计算帧率
		double t = 0;
		t = cv::getTickCount();
		
		geometry_msgs::PoseStamped msg; //发送的消息
		capture >> srcImage;//等价于 capture.read(frame);
		if (srcImage.empty())//如果某帧为空则退出循环
		{
			cout << "摄像头断开！" << endl;
			break;
		}
		//旋转图像

		find_line();//找线
		
		//发送数据
		msg.pose.position.x = position_x;
		msg.pose.position.y = position_y;
		msg.pose.position.z = position_z;
		msg.header.stamp = ros::Time::now (); 
		ROS_INFO("%.2f , %.2f", msg.pose.position.x, msg.pose.position.y);
		number_publisher.publish(msg);
		ros::spinOnce();
		loop_rate.sleep();

		waitKey(1);//每帧延时 1 毫秒，如果不延时，图像将无法显示
		
		t = ((double)cv::getTickCount() - t) / cv::getTickFrequency();
		fps = 1.0 / t;
		ROS_INFO("fps=%.2f \n", fps);
	}
	capture.release();//释放资源
	
	//打开另一个摄像头
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
	capture.set(CAP_PROP_FPS, 15);
	
	//定点
	while(1)
	{
		double fps;//计算帧率
		double t = 0;
		t = cv::getTickCount();
		
		geometry_msgs::PoseStamped msg; //发送的消息
		capture >> srcImage;//等价于 capture.read(frame);
		if (srcImage.empty())//如果某帧为空则退出循环
		{
			cout << "摄像头断开！" << endl;
			break;
		}

		find_cot();//定点
		
		//发送数据
		msg.pose.position.x = position_x;
		msg.pose.position.y = position_y;
		msg.pose.position.z = position_z;
		msg.header.stamp = ros::Time::now (); 
		ROS_INFO("%.2f , %.2f , %.2f", msg.pose.position.x, msg.pose.position.y,msg.pose.position.z);
		number_publisher.publish(msg);
		ros::spinOnce();
		loop_rate.sleep();

		waitKey(1);//每帧延时 1 毫秒，如果不延时，图像将无法显示
		
		t = ((double)cv::getTickCount() - t) / cv::getTickFrequency();
		fps = 1.0 / t;
		ROS_INFO("fps=%.2f \n", fps);
	}

	capture.release();//释放资源
	return 0;
}

//寻找奇怪颜色的线
void find_line()
{	
	//创建显示窗口和滑动条
	namedWindow("Color");
	createTrackbar("LowH", "Color", &iLowH, 179); //Hue (0 - 179)
	createTrackbar("HighH", "Color", &iHighH, 179);
	createTrackbar("LowS", "Color", &iLowS, 255); //Saturation (0 - 255)
	createTrackbar("HighS", "Color", &iHighS, 255);
	createTrackbar("LowV", "Color", &iLowV, 255); //Value (0 - 255)
	createTrackbar("HighV", "Color", &iHighV, 255);
	createTrackbar("累加平面的阈值参数（巡线）", "video", &g_houghlines1, 300);
	createTrackbar("最短线段长度", "video", &g_houghlines2, 250);
	createTrackbar("允许连接的最大距离", "video", &g_houghlines3, 250);
	
	Mat imgHSV;
	Mat imgThresholded1;
	Mat imgThresholded2;
	Mat imgThresholded3;
	Mat imgThresholded;//输出的检测后的二值图
	Mat element;
	//颜色空间转换
	cvtColor(srcImage, imgHSV, COLOR_BGR2HSV);
	//颜色检测
	if(line_mode==0)//表示同时识别红色和绿色
	{
		inRange(imgHSV, Scalar(155, 50, 50), Scalar(179, 245, 245), imgThresholded1);
		inRange(imgHSV, Scalar(0, 50, 50), Scalar(12, 245, 245), imgThresholded2);
		inRange(imgHSV, Scalar(63, 50, 40), Scalar(101, 245, 245), imgThresholded3);
		imgThresholded=imgThresholded1+imgThresholded2+imgThresholded3;
	}
	else if(line_mode==1)//表示识别红色
	{
		inRange(imgHSV, Scalar(155, 50, 50), Scalar(179, 245, 245), imgThresholded1);
		inRange(imgHSV, Scalar(0, 50, 50), Scalar(12, 245, 245), imgThresholded2);
		imgThresholded=imgThresholded1+imgThresholded2;
	}
	else if(line_mode==2)//表示识别绿色
		inRange(imgHSV, Scalar(63, 50, 40), Scalar(101, 245, 245), imgThresholded);
	//先开操作后闭操作去除噪点
	element = getStructuringElement(MORPH_RECT, Size(1, 4));
	morphologyEx(imgThresholded, imgThresholded, MORPH_OPEN, element);

	//计算出应该读取的像素点范围
	Point3f temp_point=minor_line(imgThresholded);
	if(temp_point==Point3f(-1,-1,-1))
	{
		imshow("Color", imgThresholded);
		imshow("video", srcImage);
		position_z=1;
		return;
	}
	position_z=0;
	double read_line_left=temp_point.x*2;
	double read_line_right=temp_point.y*2;
	double ratiomedium=temp_point.z;
	//开始计算线的粗细
	vector<int> all_line;
	double img_distance1=0,img_distance2=0,img_distance3=0;
	//y=240时的粗细
	uchar *Data = imgThresholded.ptr<uchar>(240);
	for (int j = (read_line_left-LINE_DEAD_AREA); j <= (read_line_right+LINE_DEAD_AREA); j++)
	{
		if(Data[j] == saturate_cast<uchar>(255))
			all_line.push_back(j);
	}
	if(all_line.size()>0)
		img_distance1=all_line[all_line.size()-1]-all_line[0];
	//y=200时的粗细
	all_line.clear();
	Data = imgThresholded.ptr<uchar>(200);
	for (int j = (read_line_left-LINE_DEAD_AREA); j <= (read_line_right+LINE_DEAD_AREA); j++)
	{
		if(Data[j] == saturate_cast<uchar>(255))
			all_line.push_back(j);
	}
	if(all_line.size()>0)
		img_distance2=all_line[all_line.size()-1]-all_line[0];
	//y=280时的粗细
	all_line.clear();
	Data = imgThresholded.ptr<uchar>(280);
	for (int j = (read_line_left-LINE_DEAD_AREA); j <= (read_line_right+LINE_DEAD_AREA); j++)
	{
		if(Data[j] == saturate_cast<uchar>(255))
			all_line.push_back(j);
	}
	if(all_line.size()>0)
		img_distance3=all_line[all_line.size()-1]-all_line[0];
	//取三者的中位数
	double img_distance=0;
	if(img_distance1>img_distance2)
	{
		if(img_distance1<img_distance3)
			img_distance=img_distance1;
		else if(img_distance2>img_distance3)
			img_distance=img_distance2;
		else
			img_distance=img_distance3;
	}
	else if(img_distance1>img_distance3)
		img_distance=img_distance1;
	else if(img_distance2<img_distance3)
		img_distance=img_distance2;
	else
		img_distance=img_distance3;
	img_distance/=(1+ratiomedium*ratiomedium);
	double true_distance=TRANSFERR/img_distance;
	//给出距离参数
	position_y=true_distance;

	imshow("Color", imgThresholded);
	imshow("video", srcImage);
}

//缩小像素点的霍夫线变换
Point3f minor_line(Mat imgThresholded1)
{
	Mat imgThresholded=imgThresholded1.clone();
	Mat imgCanny;//canny算子轮廓检测的图
	createTrackbar("canny", "Canny", &g_cannyLowThreshold, 100);
	resize(srcImage, srcImage, Size(320, 240), 0, 0, INTER_AREA);
	resize(imgThresholded, imgThresholded, Size(320, 240), 0, 0, INTER_AREA);
	//寻找轮廓,进行霍夫线变换
	//寻找轮廓
	Canny(imgThresholded, imgCanny, g_cannyLowThreshold, g_cannyLowThreshold * 3);
	imshow("Canny",imgCanny);//显示图像
	//进行霍夫线变换
	vector<Vec4i> lines;//定义一个矢量结构lines用于存放得到的线段矢量集合
	HoughLinesP(imgCanny, lines, 1, CV_PI / 180, g_houghlines1, g_houghlines2, g_houghlines3);
	
	vector<Point2f> points_to_fit;
	double line_left=0;//最左边的线的截距
	double line_right=0;//最右边的线的截距
	int line_first_mode=1;
	//将竖直方向的线存入数组中
	for (size_t i = 0; i < lines.size(); i++)
	{
		Vec4i l = lines[i];
		float ratio;
		float intercept;
		//忽略水平的线
		if (abs(l[0] - l[2]) < abs(l[1] - l[3]))
		{
			line(srcImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 255, 0), 1, LINE_AA);
			//计算斜率和横截距
			ratio = (l[0] - l[2])*1.0 / (l[1] - l[3]);
			intercept = l[0] * 1.0 - ratio*l[1];
			//将竖直方向的线存入数组中
			points_to_fit.push_back(Point2f(ratio, intercept));
			//得出最左边和最右边的线的截距
			if(line_first_mode)
			{
				line_first_mode=0;
				line_left=intercept;
				line_right=intercept;
			}
			else
			{
				if(intercept<line_left)
					line_left=intercept;
				else if(intercept>line_right)
					line_right=intercept;
			}
		}
	}
	//计算出中间的线在哪里
	double ratiomedium,interceptmedium;//中间的线
	double ratios=0,intercepts=0;
	//如果识别到了线
	if (points_to_fit.size()>0)
	{
		for (size_t i = 0; i<points_to_fit.size(); i++)
		{
			ratios += points_to_fit[i].x;
			intercepts += points_to_fit[i].y;
		}
		ratiomedium = ratios*1.0 / points_to_fit.size();
		interceptmedium = intercepts*1.0 / points_to_fit.size();
		position_x=160-(120*ratiomedium+interceptmedium);
		if (ratiomedium<0)
		{
			line(srcImage, Point2f(interceptmedium, 0), Point2f(0, -interceptmedium*1.0 / ratiomedium), Scalar(186, 88, 255), 2, LINE_AA);
		}
		else if (ratiomedium>0)
		{
			line(srcImage, Point2f(interceptmedium, 0), Point2f( 320, ((320 - interceptmedium)*1.0 / ratiomedium)), Scalar(186, 88, 255), 2, LINE_AA);
		}
		else
		{
			line(srcImage, Point2f(interceptmedium, 0), Point2f(interceptmedium, 240), Scalar(186, 88, 255), 2, LINE_AA);
		}

		//计算出应该读取的像素点范围
		double read_line_left=ratiomedium*120+line_left;
		double read_line_right=ratiomedium*120+line_right;
		//返回数据		
		return Point3f(read_line_left,read_line_right,ratiomedium);
	}
	//如果没有识别到线
	else
	{
		return Point3f(-1,-1,-1);
	}
}

//定点（最大轮廓检测）
void find_cot()
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
			position_z=1;
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
			position_x=cvRound(circles[k_circle][0])-160;
			position_y=120-cvRound(circles[k_circle][1]);
			position_z=0;
		}
		else
			position_z=1;
	}
	else
		position_z=1;

	imshow("thresh", dstImage);
	imshow("dot", srcImage);
}