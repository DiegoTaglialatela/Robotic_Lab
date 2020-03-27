#include "ros/ros.h"
#include "exercise3/mess1.h"
#include "exercise3/mess2.h"

#include <iostream>

class ROS_SUB{
public:
 ROS_SUB();
 void topic_cb( exercise3::mess1 data);

private:

 ros::NodeHandle _nh;
 ros::Subscriber _topic_sub;
 ros::Publisher  _topic_pub;
};

ROS_SUB::ROS_SUB() {

_topic_sub=_nh.subscribe( "/numbers_2", 10, &ROS_SUB::topic_cb, this);
_topic_pub = _nh.advertise < exercise3::mess2 > ("/numbers_3", 10);

}

void ROS_SUB::topic_cb( exercise3::mess1 data){
std::cout<< "First number:"<<data.data1;
std::cout<< " Second number:"<<data.data2<<std::endl;

   
 
 

   exercise3::mess2 msg;
   msg.data1 = data.data1;
   msg.data2 = data.data2;
   msg.sum = data.data1+data.data2;
   ROS_INFO("Sum is: %d",msg.sum);
   _topic_pub.publish(msg);

}

int main(int argc, char **argv) {

 ros::init ( argc, argv, "ros_topic_sub" );

 
 ROS_SUB rs;

 ros::spin();

 }
