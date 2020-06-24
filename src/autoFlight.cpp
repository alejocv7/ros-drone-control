#include <ar_drone/autoFlight.h>
#include "ardrone_autonomy/Navdata.h"
#define MAX_STREAM_WIDTH 640
#define MAX_STREAM_HEIGHT 360
/*
Autoflight mode allows the drone to run autonomously until it find a specifed object. In this case it would run
until the color red is located.
*/
bool isFace = 0;

Drone::~Drone(){
}

Drone::Drone() : it_(n), loop_rate(10){
	xyMove = n.advertise<geometry_msgs::Twist>("cmd_vel",10,true);
	flight = n.advertise<std_msgs::Empty>("ardrone/takeoff",1,true);
	land = n.advertise<std_msgs::Empty>("ardrone/land",10,true);
	camFront = it_.advertise("ardrone/front/image_raw",10);
	camSub = n.subscribe<std_msgs::String>("face_present", 10,&Drone::msgCallback, this);
}

void Drone::setZero(){
	vel.angular.x=0;
	vel.angular.y=0;
	vel.angular.z=0;
	vel.linear.x =0;
	vel.linear.y =0;
	vel.linear.z =0;
	xyMove.publish(vel);
	std::cout<<"stoped"<< "\n";
}

void Drone::msgCallback(const std_msgs::String::ConstPtr& msg){
	std::cout << msg << "\n";
}

void Drone::publishVideo(){
	image.width = MAX_STREAM_WIDTH;
	image.height = MAX_STREAM_HEIGHT;
	image.encoding = "rgb8";
	image.is_bigendian = false;
	image.step = MAX_STREAM_WIDTH*3;
	image.data.resize(MAX_STREAM_WIDTH*MAX_STREAM_HEIGHT*3);
	ci.width = MAX_STREAM_WIDTH;
	ci.height = MAX_STREAM_HEIGHT;
	camFront.publish(image);
}
void Drone::turnLeft(){
	vel.angular.z = .25;
	xyMove.publish(vel);
}
void Drone::turnRight(){
	vel.angular.z = -.25;
	xyMove.publish(vel);
}

void Drone::movement(){
	flight.publish(em);
	double start = ros::Time::now().toSec();
	while((double)ros::Time::now().toSec() < start+.025){
		std::cout<<"turning" << "\n";
		turnLeft();
		ros::spinOnce();
		loop_rate.sleep();
		if(isFace == 1){
			break;
			

		}
	}
	land.publish(em);
}
int main(int argc, char** argv){
	ros::init(argc,argv,"flight");
	Drone drone;
	drone.publishVideo();
	drone.movement();
	while(ros::ok()){
		ros::spinOnce();
		drone.loop_rate.sleep();
	}
}