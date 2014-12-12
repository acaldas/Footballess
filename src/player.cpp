#include "ros/ros.h"
#include <nav_msgs/GetMap.h>
#include <stdlib.h> 
#include <iostream> 
#include <string> 
#include <sstream> 

using namespace std;

int main(int argc, char **argv)
{
  ros::init(argc, argv, "player");

  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<nav_msgs::GetMap>("static_map");
  nav_msgs::GetMap::Request req;
  nav_msgs::GetMap::Response res;
	
  
  if (client.call(req,res))
  {
    ROS_INFO_STREAM("Map: " << res.map.info);
	int width = res.map.info.width;
	int height = res.map.info.height;
	double board[width][height];
	int n=0;	
	ostringstream os;
	for(int i=0;i<height;i++) {
		os << endl;
		for(int j=0;j<width;j++) {
			board[j][i] = res.map.data[n];
			n++;
			if(board[j][i] == 100)
				os << "X";
			else
				os << " ";
		}		
	}
	
	ROS_INFO_STREAM(os.str());
	ROS_INFO_STREAM("Cell: " << board[6][60]);
  }
  else
  {
    ROS_ERROR("Failed to call service static_map");
    return 1;
  }

  return 0;
}