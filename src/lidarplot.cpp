#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"
#include "opencv2/opencv.hpp"
#include <math.h>

#define RAD2DEG(x) ((x)*180./M_PI)
#define WIDTH   500
#define HEIGHT  500
#define RATIO ((WIDTH/2.0)/5000.0)  //5000mm->(WIDTH/2)pixel
cv::Mat img(HEIGHT, WIDTH, CV_8UC3, cv::Scalar(255, 255, 255));

//void plotLidar(cv::Mat& img, double dist, double angle)
void plotLidar(double dist, double angle)
{
	cv::Point2f cp(WIDTH / 2.0, HEIGHT / 2.0);
	cv::Point2f pt(WIDTH / 2.0, HEIGHT / 2.0 + dist * RATIO);
	cv::drawMarker(img, cp, cv::Scalar(255, 0, 0), cv::MARKER_CROSS, 10);
	//circle(img, pt, 3, Scalar(255,0,0),-1);
	cv::Mat M = cv::getRotationMatrix2D(cp, angle, 1);
	double array[3] = { pt.x, pt.y, 1.0 };
	cv::Mat ptM(3, 1, CV_64FC1, array);
	cv::Mat rotpt = M * ptM;
	//cout << rotpt;
  //circle(img, cp, 2, Scalar(255, 0, 0), -1);
	cv::circle(img, cv::Point2f(rotpt.at<double>(0, 0), rotpt.at<double>(1, 0)), 1, cv::Scalar(0, 0, 255), -1);
}

static void scanCb(sensor_msgs::msg::LaserScan::SharedPtr scan) {
  int count = scan->scan_time / scan->time_increment;
  printf("[SLLIDAR INFO]: I heard a laser scan %s[%d]:\n", scan->header.frame_id.c_str(), count);
  printf("[SLLIDAR INFO]: angle_range : [%f, %f]\n", RAD2DEG(scan->angle_min),
         RAD2DEG(scan->angle_max));
  img = cv::Scalar(255, 255, 255);
  for (int i = 0; i < count; i++) {
    float degree = RAD2DEG(scan->angle_min + scan->angle_increment * i);
    printf("[SLLIDAR INFO]: angle-distance : [%f, %f]\n", degree, scan->ranges[i]);
    //plotLidar(img, scan->ranges[i], degree);
    plotLidar(scan->ranges[i]*1000, degree);
    
  }
  cv::imshow("lidar",img);
  cv::waitKey(1);
}

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("lidarplot");
  // generate image window  
	//cv::line(img, cv::Point(WIDTH / 2, 0), cv::Point(WIDTH / 2, HEIGHT - 1), cv::Scalar(255, 0, 0));
	//cv::line(img, cv::Point(0, HEIGHT / 2), cv::Point(WIDTH-1, HEIGHT / 2), cv::Scalar(255, 0, 0));  
  auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
  auto lidar_info_sub = node->create_subscription<sensor_msgs::msg::LaserScan>("scan", qos_profile, scanCb);
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
