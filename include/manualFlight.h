#ifndef __MANUALFLIGHT_H_
#define __MANUALFLIGHT_H_
#include <ros/ros.h>
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/Joy.h"
#include "sensor_msgs/Image.h"
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
	image_transport::Publisher camFront;
	ros::Subscriber joyNode;
	void joyStick(const sensor_msgs::Joy::ConstPtr& joy);
	void moveForward();
	void moveBackwards();
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
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
	Drone();
	~Drone();
};
#endif