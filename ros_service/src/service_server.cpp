#include "ros/ros.h"
#include <sstream>
#include "ros_service/service.h"

using namespace std;

bool service_callback( ros_service::service::Request &req, ros_service::service::Response &res ){

 cout<<"Client req:"<<req.in<<endl;
 //std::stringstream ss:
 //ss<< "Recieved Here"
 res.out= "Received Here!";
 ROS_INFO("From client, server says: Recieved Here");

 return true;
}

int main(int argc, char **argv) {

  ros::init( argc, argv, "service_server");
  ros::NodeHandle nh;
  ros::ServiceServer service=nh.advertiseService("service", service_callback);
  ROS_INFO("ready to get request");

  ros::spin();


  return 0;
}
