
#include "ros/ros.h"
#include "geometry_msgs/Pose.h"
#include <tf/transform_datatypes.h>

using namespace std;

int main(int argc, char **argv){
	ros::init(argc, argv, "ex8pub");
    
    ros::NodeHandle nh;
    ros::Publisher pub;
    pub = nh.advertise<geometry_msgs::Pose> ("/pose", 0);

    ros::Rate rate(10);
    geometry_msgs::Pose pose;
    tf::Quaternion pos;
    double roll,pitch,yaw;
	
    while(ros::ok()){
        cout << "Posizione desiderata: " << endl;
        cin >> pose.position.x >> pose.position.y >> pose.position.z;
        cout << "Orientamento desiderato in rollio beccheggio e imbardata:" << endl;
        cin >> roll >> pitch >> yaw;
        pos.setRPY(roll,pitch,yaw);
        pose.orientation.x = pos.x();
        pose.orientation.y = pos.y();
        pose.orientation.z = pos.z();
        pose.orientation.w = pos.w();
        pub.publish(pose);
        cout << "Digirate S per fermarsi, qualsiasi altro carattere per continuare: ";
        string input;
        cin.ignore();
        getline(cin, input);
        if(!input.empty() && (input == "s" || input == "S"))
            break;
        rate.sleep();
    }
}