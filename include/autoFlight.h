#ifndef __AUTOFLIGHT_H__
#define __AUTOFLIGHT_H__
#include <ros/ros.h>
#include "sensor_msgs/Joy.h"
#include "sensor_msgs/Image.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/CameraInfo.h"
#include "std_msgs/Empty.h"
#include <image_transport/image_transport.h>

class Drone{
private: 
	ros::NodeHandle n;
	image_transport::ImageTransport it_;
	ros::Publisher xyMove;
	ros::Publisher flight;
	ros::Publisher land;
	ros::Subscriber camSub;
	image_transport::Publisher camFront;
	void msgCallback(const std_msgs::String::ConstPtr& msg);
	void setZero();
	void turnLeft();
	void turnRight();
public:
	geometry_msgs::Twist vel;
	std_msgs::Empty em;
	sensor_msgs::Image image;
	sensor_msgs::CameraInfo ci;
	ros::Rate loop_rate;
	void publishVideo();
	void movement();
	Drone();
	~Drone();
};
#endif