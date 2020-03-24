#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include <iostream>

class ROS_SUB{
public:
 ROS_SUB();
 void topic_cb( std_msgs::Int32ConstPtr data);

private:

 ros::NodeHandle _nh;
 ros::Subscriber _topic_sub;

};

ROS_SUB::ROS_SUB() {

_topic_sub=_nh.subscribe( "/numbers", 10, &ROS_SUB::topic_cb, this);

}

void ROS_SUB::topic_cb( std_msgs::Int32ConstPtr data){
std::cout<< "data:"<<data->data<<std::endl;
}

int main(int argc, char **argv) {


 ros::init ( argc, argv, "ros_topic_sub" );
 ROS_SUB rs;


 ros::spin();

 }
