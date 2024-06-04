# lidarplot

ros2 test package for RPLIDAR C1 on Jetson nano and WSL2

dependency : ros2 foxy, opencv 4.8, cmake 3.16

RPLIDAR C1 ROS2 package : https://github.com/Slamtec/sllidar_ros2

sllidar_node of sllidar_ros2 package publishes /scan topic.
Subscriber node lidarplot subscribes /scan topic and plot an image of scan view using opencv.

# Open linux terminal on Jetson nano

`$ cd ~/ros2_ws/src
$ git clone https://github.com/Slamtec/sllidar_ros2.git
$ cd ~/ros2_ws
$ colcon build --symlink-install --packages-select sllidar_ros2
$ source install/local_setup.bash`

Make sure your lidar sensor is connected to /dev/ttyUSB0.

`$ sudo chmod a+rw /dev/ttyUSB0
$ ros2 run sllidar_ros2 sllidar_node`

![image](https://github.com/2sungryul/lidarplot/assets/67367753/2a9864a8-5207-4bcd-964e-665dba9504ca)


# Open linux terminal on WSL2

`$ export LIBGL_ALWAYS_INDIRECT=0
$ export LIBGL_ALWAYS_SOFTWARE=1
$ wget https://raw.githubusercontent.com/Slamtec/sllidar_ros2/main/rviz/sllidar_ros2.rviz
$ ros2 run rviz2 rviz2 sllidar_ros2.rviz`

![image](https://github.com/2sungryul/lidarplot/assets/67367753/7bfa9fd8-9b67-480d-b5c6-db0c306ac32f)

`$ cd ~/ros2_ws/src
$ git clone https://github.com/2sungryul/lidarplot.git
$ cd ~/ros2_ws
$ colcon build --symlink-install --packages-select lidarplot
$ source install/local_setup.bash
$ ros2 run lidarplot lidarplot`

![image](https://github.com/2sungryul/lidarplot/assets/67367753/7bbd37e9-748b-40a3-927e-3a9ea9ddf54f)


