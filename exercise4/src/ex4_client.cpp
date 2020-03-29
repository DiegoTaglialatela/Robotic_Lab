#include "ros/ros.h"
#include <iostream>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include "exercise4/motorAction.h"

int main (int argc, char **argv) {

	ros::init(argc, argv, "motor_action_client");
  if(argc != 5){
		ROS_INFO("%d",argc);
		ROS_WARN("Usage: motor_action_client <initial_position> <final_position> <max_angular_velocity> <time>");
		return 1;
	}

  // create the action client
  // true causes the client to spin its own thread
  actionlib::SimpleActionClient<exercise4::motorAction> ac("motor_action", true);

  ROS_INFO("Waiting for action server to start.");

  // wait for the action server to start
  ac.waitForServer(); //will wait for infinite time

  ROS_INFO("Action server started, sending goal.");

  // send a goal to the action
  exercise4::motorGoal goal;
  goal.initial_position = atoi(argv[1]);
  goal.final_position = atoi(argv[2]);
  goal.max_angular_velocity = atoi(argv[3]);
  
  ROS_INFO("Sending Goal [%d] and Preempt time of [%d]",goal.final_position, atoi(argv[4]));
  ac.sendGoal(goal);

  //wait for the action to return
  bool finished_before_timeout = ac.waitForResult(ros::Duration(atoi(argv[4])));
  //Preempting task
  ac.cancelGoal();

  if (finished_before_timeout) {
    actionlib::SimpleClientGoalState state = ac.getState();
    ROS_INFO("Action finished: %s",state.toString().c_str());
    //Preempting the process
		ac.cancelGoal();

  }
  else
    ROS_INFO("Action did not finish before the time out.");
    
  //exit
  return 0;
}
