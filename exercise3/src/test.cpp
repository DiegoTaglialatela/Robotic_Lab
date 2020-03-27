#include "ros/ros.h"
#include "exercise3/mess2.h"
#include <iostream>

class ROS_SUB{
public:
 ROS_SUB();
 void topic_cb( exercise3::mess2 data);

private:

 ros::NodeHandle _nh;
 ros::Subscriber _topic_sub;

};

ROS_SUB::ROS_SUB() {

_topic_sub=_nh.subscribe( "/numbers_3", 10, &ROS_SUB::topic_cb, this);

}

void ROS_SUB::topic_cb( exercise3::mess2 data){
std::cout<< "data:"<<data<<std::endl;
}

int main(int argc, char **argv) {


 ros::init ( argc, argv, "rex3_test" );
 ROS_SUB rs;


 ros::spin();

 }
