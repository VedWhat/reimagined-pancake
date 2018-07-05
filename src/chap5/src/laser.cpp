#include <ros/ros.h>
#include<sensor_msgs/LaserScan.h>
using namespace ros;
using namespace sensor_msgs;
int main(int a, char** b)
{
	init(a,b,"laser_scan_pub");
	NodeHandle n;
	Publisher scan_pub = n.advertise<LaserScan>("scan",50);
	int num_readings=100;
	double laser_freq=40;
	double ranges[num_readings];
	double intensities[num_readings];
	int count=0;
	Rate r(1.0);
	while(n.ok())
	{
		for(int i =0;i<num_readings;i++)
		{
			ranges[i]=count;
			intensities[i]=100+count;
		}
		Time scan_time=Time::now();
		LaserScan scan;
		scan.header.stamp=scan_time;
		scan.header.frame_id="base_link";
		scan.angle_min=-0.785;
		scan.angle_max=-0.785;
		scan.angle_increment=3.14/num_readings;
		scan.time_increment=(1/laser_freq)/(num_readings);
		scan.range_min=0.0;
		scan.range_max=100.0;
		scan.ranges.resize(num_readings);
		scan.intensities.resize(num_readings);
		for(int i =0; i<num_readings;i++)
		{
			scan.ranges[i]=ranges[i];
			scan.intensities[i]=intensities[i];
		}
		scan_pub.publish(scan);
		++count;
		r.sleep();
	}

}
