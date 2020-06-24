#include <ar_drone/cameraCV.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
camera::camera() : it_(n) {
	front = it_.subscribe("ardrone/front/image_raw",10,&camera::imageFront, this);
	redColor = n.advertise<std_msgs::String>("red",10);
	faceDetected = n.advertise<std_msgs::String>("face_present",10);
	if(!face_cascade.load("/home/salman/catkin_ws/src/ar_drone/data/haarcascades/haarcascade_frontalface_alt.xml")) 
		std::cout<< "OOF" << "\n";
}
camera::~camera(){
	cv::destroyWindow("front image");
	cv::destroyWindow("modifed");
	cv::destroyWindow("facial detection");
}

void camera::imageFront(const sensor_msgs::ImageConstPtr& msg){
	try{
		front_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
		cv::Mat f(front_ptr->image);
		cv::imshow("front image", f);
		cv::waitKey(1);
		detectFace(front_ptr->image);
	}
	catch(cv_bridge::Exception& e){
		ROS_ERROR("front %s",e.what());
		return;
	}
	cv::namedWindow("modifed", cv::WINDOW_AUTOSIZE);

	cv::Mat mat;
	cv::cvtColor(front_ptr->image, mat, cv::COLOR_BGR2HSV);
	if (mat.rows > 60 && mat.cols > 60){
      for(int x = 0; x < mat.rows; x+=20){
        for(int y =0; y < mat.cols; y+=20){
          cv::circle(mat, cv::Point(mat.cols/2, mat.rows/2), 10, CV_RGB(0,0,255));
        }
      }
    }
    cv::imshow("modifed",mat);
    cv::Vec3b inten = mat.at<cv::Vec3b>(mat.cols/2,mat.rows/2);

	float hue = (float)inten.val[0];
	float saturation = (float)inten.val[1];
	float value = (float)inten.val[2];
	//RED COLOR
	if(hue > 150 && saturation > 70 && value > 30){
		std::cout<< "RED"<< "\n";
	   	strRED.data = "RED";
	   	redColor.publish(strRED);
  	}
}
void camera::detectFace(cv::Mat mat){
	std::vector<cv::Rect> faces;
    cv::Mat frame_gray;
    cv::cvtColor( mat, frame_gray, cv::COLOR_BGR2GRAY );
    cv::equalizeHist( frame_gray, frame_gray );
    face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30) );
    for( size_t i = 0; i < faces.size(); i++ ){
        cv::Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
        cv::rectangle(mat, cv::Point(faces[i].x , faces[i].y) ,cv::Point(faces[i].x+faces[i].width, faces[i].y+faces[i].height),cv::Scalar(255,0,0),1,4);
        std::cout<< "Face detected\n" ;
        cv::Mat faceROI = frame_gray(faces[i]);
    }
    imshow("facial detection",mat);
    strFace.data = "face_detected";
    faceDetected.publish(strFace);
}
int main(int argc, char** argv){
	ros::init(argc, argv, "cameraCV");
  	camera subCam;
  	ros::spin();
  	return 0;
}
		
