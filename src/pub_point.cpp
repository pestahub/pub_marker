#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
//#include <geometry_msgs/Point.h>

geometry_msgs::Point pp;
bool b_post = false;
void rec(const geometry_msgs::Point& p)
{
    //ROS_INFO(" x = %f y = %f z = %f",p.x,p.y,p.z);
    //cout<<p.x<<" "<<p.y<<" " << p.x <<endl;
    pp = p;
    ROS_INFO("I got a hit!");
    b_post = true;
    return;    
}
int main(int argc, char **argv)
{
    ros::init(argc,argv,"point_to_marker");
    ros::NodeHandle n;

    ros::Subscriber sub = n.subscribe("/input", 100, rec);
    ros::Publisher pub = n.advertise<visualization_msgs::Marker>("/output",100);//, true);
    
    // Running at 10Hz
    ros::Rate loop_rate(10);
    int count = 0;
    ros::spinOnce();
    
    pp.x = 1.0;
    pp.y = 0.0;
    pp.z = 0.0;

    while(ros::ok())
    {
        if (b_post)
        {
            visualization_msgs::Marker mrk;
            
            mrk.header.frame_id = "/point_on_map";
            mrk.header.stamp = ros::Time::now();
            mrk.ns = "there_is_point";
            mrk.id = count;
            mrk.action = visualization_msgs::Marker::ADD;
            
            mrk.type = visualization_msgs::Marker::POINTS;
            mrk.scale.x = 0.5;
            mrk.scale.y = 0.5;
            mrk.color.r = 1.0;
            mrk.color.g = 0.0;
            mrk.color.b = 0.0;
            mrk.color.a = 1.0;
        
            mrk.points.push_back(pp);
            
            pub.publish(mrk);
            ++count;
            b_post = false;
        }
        ros::spinOnce();
        loop_rate.sleep();
    }
    
    return 0;
}