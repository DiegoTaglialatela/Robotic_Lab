#include "ros/ros.h"
#include <sstream>
#include "exercise2/fibo.h"
#include <string>
#include <sstream>

using namespace std;

bool service_callback( exercise2::fibo::Request &req, exercise2::fibo::Response &res ){

 cout<<"Client index:"<<req.i<<endl;
 cout<<"Client lenght:"<<req.l<<endl;
  

 int fib[req.i+req.l-1];
 fib[0]=0;
 fib[1]=1;   
 
 for (int i=2; i<=(req.i+req.l-1); i++) {
 fib[i]=fib[i-1]+fib[i-2];
   }
    
 ostringstream SS;

 for (int i=0; i<req.l; i++){
 SS <<fib[req.i+i] << " ";
 }
 res.out=SS.str();
ROS_INFO("From client, server says: Recieved Here");

 return true;
}

int main(int argc, char **argv) {

  ros::init( argc, argv, "fibo_server");
  ros::NodeHandle nh;
  ros::ServiceServer service=nh.advertiseService("fibo", service_callback);
  ROS_INFO("ready to get request");

  ros::spin();


  return 0;
}
