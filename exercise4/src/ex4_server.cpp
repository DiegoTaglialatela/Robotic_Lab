#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include <actionlib/server/simple_action_server.h>
#include "exercise4/motorAction.h"
#include <iostream>
#include <sstream>

class action_class {

	private:
  	ros::NodeHandle nh_;
  	// NodeHandle instance must be created before this line. Otherwise strange error may occur.
  	actionlib::SimpleActionServer<exercise4::motorAction> as; 
  	// create messages that are used to published feedback/result
		exercise4::motorFeedback feedback;
		exercise4::motorResult result;

  	std::string action_name;
  	float goal;
  	float progress;

	public:
		action_class(std::string name) :
  	  as(nh_, name, boost::bind(&action_class::executeCB, this, _1), false),
  	  action_name(name) {
				as.registerPreemptCallback(boost::bind(&action_class::preemptCB, this));
				as.start();
  		}
	
		void preemptCB(){
			ROS_WARN("%s got preempted!", action_name.c_str());
			result.reached_position = progress;
			as.setPreempted(result,"I got Preempted"); 
  	}
  
		void executeCB(const exercise4::motorGoalConstPtr &goal) {
			if(!as.isActive() || as.isPreemptRequested()) return;
			ros::Rate rate(10);
			ROS_INFO("%s is processing the goal %f", action_name.c_str(), goal->final_position);
			for(progress = goal->initial_position ; progress <= goal->final_position+goal->max_angular_velocity;progress=progress+((goal->max_angular_velocity)/10)){
				//Check for ros
				if (!ros::ok()) {
					result.reached_position = progress;
					as.setAborted(result,"I failed !");
					ROS_INFO("%s Shutting down",action_name.c_str());
					break;
				}
		
				if(!as.isActive() || as.isPreemptRequested()){
					return;
				}	

				if(goal->final_position <= progress) {
					ROS_INFO("%s Succeeded at getting to goal %f", action_name.c_str(), goal->final_position);
					result.reached_position = progress;
					as.setSucceeded(result);
				}
				else {
					ROS_INFO("Setting to goal %f / %f",feedback.current_position,goal->final_position);
					feedback.current_position = progress;
					as.publishFeedback(feedback);
			}
		rate.sleep();
		}	
  }
};

int main(int argc, char** argv)
{

  ros::init(argc, argv, "motor_action");
  ROS_INFO("Starting motor Action Server");
  action_class motor_action_obj(ros::this_node::getName());
  ros::spin();
  return 0;
}
