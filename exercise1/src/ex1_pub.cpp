#include "ros/ros.h"
#include "std_msgs/String.h"
#include <string>
#include <iostream>
int main(int argc, char **argv) {



 ros::init ( argc, argv, "exercise1_publisher" );

 ros::NodeHandle nh;
 ros::Publisher  topic_pub = nh.advertise < std_msgs::String > ("/parole", 10);

 ros::Rate rate(10); //run at 10Hz

 std::string word;

 while( ros::ok() ){
   std::cout << "Digitare la parola: "; // no flush needed
   std::cin >> word;

   std_msgs::String msg;
   msg.data = word;

   ROS_INFO("%d", msg.data);

   topic_pub.publish(msg);

   rate.sleep();
 }


}
