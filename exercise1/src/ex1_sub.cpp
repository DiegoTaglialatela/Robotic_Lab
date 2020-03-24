#include "ros/ros.h"
#include "std_msgs/String.h"
#include <iostream>
#include <string>

class ROS_SUB{
public:
 ROS_SUB();
 void topic_cb( std_msgs::StringConstPtr data);

private:

 ros::NodeHandle _nh;
 ros::Subscriber _topic_sub;

};

ROS_SUB::ROS_SUB() {

_topic_sub=_nh.subscribe( "/parole", 10, &ROS_SUB::topic_cb, this);

}

void ROS_SUB::topic_cb( std_msgs::StringConstPtr data){
std::cout<< "data:"<<data->data<<std::endl;
}

int main(int argc, char **argv) {


 ros::init ( argc, argv, "ros_topic_sub" );
 ROS_SUB rs;


 ros::spin();

 }
