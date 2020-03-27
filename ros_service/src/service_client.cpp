#include "ros/ros.h"
#include <sstream>
#include "ros_service/service.h"

using namespace std;




int main(int argc, char **argv) {


ros::init( argc, argv, "service_client");
ros::NodeHandle nh;

ros::Rate loop_rate(10);
ros::ServiceClient client = nh.serviceClient< ros_service::service >("service");

while(ros::ok()){

  ros_service::service srv;

  srv.request.in="this is input";
  if( client.call( srv ) ){

    cout<<"Server called:"<< srv.response.out<<endl;

  }
  else{
    ROS_ERROR("No service");
  }
  ros::spinOnce();
  loop_rate.sleep();
 }

 return 1;

}
