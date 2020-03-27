#include "ros/ros.h"
#include <sstream>
#include "exercise2/fibo.h"
#include<stdio.h>

using namespace std;




int main(int argc, char **argv) {
float i;
float l;
ros::init( argc, argv, "fibo_client");
ros::NodeHandle nh;

ros::Rate loop_rate(10);
ros::ServiceClient client = nh.serviceClient< exercise2::fibo >("fibo");

while(ros::ok()){

  exercise2::fibo srv;
  cout<<"Insert index"<<endl;
  cin>>i;
  while ((!cin)||i<0||(i!=(int)i)){
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cout<<"valore non valido inserire un numero intero maggiore o uguale a 0"<<endl;
  cin>>i;}
  srv.request.i=i;
  
  cout<<"Insert lenght"<<endl;
  cin>>l;
  while ((!cin)||l<=0||(l!=(int)l)){
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cout<<"valore non valido inserire un numero intero maggiore di 0"<<endl;
  cin>>l;}
  
  srv.request.l=l;
    

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
