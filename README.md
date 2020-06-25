# Drone Control with ROS and OpenCV

<p align="center">
  <img width="400" src="https://whatsyourtech.ca/wp-content/uploads/2014/07/Parrot-AR-Drone-2-Elite-Edition.jpg">
</p>

## Skills and tools used

> ROS | C++ | Linux
                                                                                                                
## Summary

This project involves controlling the Parrot AR-Drone 2.0 using a Logitech joystick and Image Recognition. The software to control the drone's behavior was developed in ROS (Robot Operating System) with C++ implementation and used Image Recognition (with the OpenCV library). The drone had two control modes:</p>					

1. **Manual Mode:** Drone is controlled using a joystick. Drone's camera is active, but it does not trigger a specific action.
2. **Automatic Mode:** Once the drone is flying, it turns until it detects a target (a red ball), which triggers the landing action.

### Some of the ROS Packages and Libraries Used are

* `ardrone_autonomy:` This allows for messages to be sent and received by the drone. The drone takes off or lands if an ROS std_msgs/Empty message is published to ardrone/takeoff or ardrone/-land topics, respectively.

* `cmv_vel/geometry_msgs:` In order to move the drone around, a message is sent with ROS to the topic cmd_vel using geometry_msgs/Twist. The drone can then drive in any direction with a velocity specified in m/s.

* `joy:` The joy library contains a node called "joy_node". This node publishes a message with the current state of the joystick's buttons and axes.

* `cv_bridge for OpenCV:` This provides a bridge to convert between ROS image messages and OpenCV images.
