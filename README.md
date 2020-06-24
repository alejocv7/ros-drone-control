# Drone Control with ROS and OpenCV

## Summary

This project involves controlling the Parrot AR-Drone 2.0 using a Logitech joystick and Image Recognition. The software to control the drone's behavior was developed in ROS (Robot Operating System) with C++ implementation, as well as using Image Recognition (with the OpenCV library). The drone had two control modes:</p>					

1. **Manual Mode:** Drone is controlled using a joystick. Dron's camera is active but it does not trigger a specific action.
2. **Automatic Mode:** Once it's flying, the drone turns until it detects a target (a red ball) which triggers the landing action.

### Some of the ROS Packages and Libraries Used are

* **ardrone_autonomy:** This allows for messages to be sent and received by the drone. The drone takeoff or land if a ROS std_msgs/Empty message is published to ardrone/takeoff or ardrone/-land topics respectively.

* **geometry_msgs:** In order to move the drone around we have to send a message with ROS to the topic cmd_vel. We use the subscribed topic geometry_msgs/Twist. This lets us drive the drone in any direction with a velocity specified in m/s.

* **joy:** The joy library contains a node called "joy_node". This node publishes a message with the current state of the joystick's buttons and axes.

* **cv_bridge for OpenCV:** This provides a bridge to convert between ROS image messages and OpenCV images.
