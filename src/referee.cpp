/*
 * referee.cpp
 *
 *  Created on: 09/12/2014
 *      Author: jorgemiguel
 */


#include <ros/ros.h>
#include <nav_msgs/Odometry.h> // for base_pose_ground_truth messages
#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <geometry_msgs/PoseWithCovariance.h>

/*
#include "../include/ros/ros.h"
#include "../include/geometry_msgs/Twist.h"
#include "../include/nav_msgs/Odometry.h"
#include "../include/message_filters/subscriber.h"
#include "../include/message_filters/time_synchronizer.h"
#include "../include/geometry_msgs/PoseWithCovariance.h"
*/
//#include "RobotsPose.h"

#define NR_ROBOTS 2

using namespace message_filters;
using namespace nav_msgs;


void pose_callback(const OdometryConstPtr& p1r1, const OdometryConstPtr& p1r2, const OdometryConstPtr& p2r1, const OdometryConstPtr& p2r2) {
	ROS_INFO_STREAM(p1r1->pose.pose);
	ROS_INFO_STREAM(p1r2->pose.pose);
	ROS_INFO_STREAM(p2r1->pose.pose);
	ROS_INFO_STREAM(p2r2->pose.pose);

	//enviar msg "Poses" para nó de poses


}

int main(int argc, char **argv) {

	ros::init(argc, argv, "referee");
	ros::NodeHandle nh;

	//ODOMETRIA
	Subscriber<Odometry> poserobot1(nh, "robot_0/base_pose_ground_truth", 10);
	Subscriber<Odometry> poserobot2(nh, "robot_1/base_pose_ground_truth", 10);
	Subscriber<Odometry> poserobot3(nh, "robot_2/base_pose_ground_truth", 10);
	Subscriber<Odometry> poserobot4(nh, "robot_3/base_pose_ground_truth", 10);
	TimeSynchronizer<Odometry, Odometry, Odometry, Odometry> sync(poserobot1, poserobot2, poserobot3, poserobot4, 10);
	sync.registerCallback( boost::bind(&pose_callback, _1, _2, _3, _4) );

	ros::spin(); //callback loop

	//ros::Subscriber sub = nh.subscribe("p1/base_pose_ground_truth", 1, &callback);
	//subscrever pose dos 4 robôs

	//criar 2 publishers com pose dos robôs de cada jogador



	//COMANDOS VELOCIDADE

	//subscrever 2 topicos com comandos dos jogadores

	//criar 4 publishers cmd_vel (1 p cada robô)
	//ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("p1/cmd_vel", 1000);


	return 0;
}
