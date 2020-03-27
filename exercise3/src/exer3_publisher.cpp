#include "ros/ros.h"
#include "exercise3/mess1.h"
#include <iostream>

int main(int argc, char **argv) {

 std::cout<< "hello!" << std::endl;

 ros::init ( argc, argv, "exer3_publisher" );

 ros::NodeHandle nh;
 ros::Publisher  topic_pub = nh.advertise < exercise3::mess1 > ("/numbers_2", 10);

 ros::Rate rate(10); //run at 10Hz

 

 while( ros::ok() ){

   exercise3::mess1 msg;
   msg.data1 = rand() % 1000;
   msg.data2 = rand() % 1000;
   ROS_INFO("First number: %d",msg.data1);
   ROS_INFO("Second number: %d",msg.data2);
   topic_pub.publish(msg);

   rate.sleep();
 }


}
