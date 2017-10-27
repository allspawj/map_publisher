#include "ros/ros.h"
#include "nav_msgs/OccupancyGrid.h"
#include "nav_msgs/MapMetaData.h"
#include "std_msgs/Header.h"

int main(int argc, char **argv)
{
	ros::init(argc, argv, "talker");
	ros::NodeHandle n;
	ros::Publisher pub = n.advertise<nav_msgs::OccupancyGrid>("/map", 1);

	ros::Rate loop_rate(10);

	std_msgs::Header header = std_msgs::Header();
	header.stamp = ros::Time::now();
	header.frame_id = "/world";

	nav_msgs::MapMetaData metaD = nav_msgs::MapMetaData();
	metaD.map_load_time = ros::Time::now();
	metaD.resolution = 0.05; //each pixel will represent .05 meters
	metaD.width = 1200; //1200 pixels long , AKA 60 meters
	metaD.height = 300; //300 pixels tall, AKA 15 meters
	//metaD.origin will just init to 0, no need to change

	nav_msgs::OccupancyGrid map = nav_msgs::OccupancyGrid();
	map.header = header;
	map.info = metaD;
	
	for(int i =0; i < 1200*300; i++)
	{
		map.data.push_back(-1);
	}

	while (ros::ok())
	{
		pub.publish(map);
		ros::spinOnce();
	}
}