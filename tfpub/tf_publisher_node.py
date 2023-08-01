#!/usr/bin/env python3

import rospy
import tf
from std_msgs.msg import String
from std_msgs.msg import Float64

def myhook():
    print("********************************************************************************************************************")

class TFPublisher:
    def __init__(self):
        rospy.init_node('tf_publisher_node')

        # Create a tf broadcaster
        self.tf_broadcaster = tf.TransformBroadcaster()
        # sensor data
        self.imuData = [0.0, 0.0, 0.0]
        self.lwData = 1.0
        self.rwData = 1.0
        # Define the tf tree hierarchy
        self.parent_frames = ['map', 'odom', 'base_footprint', 'base_link']
        self.child_frames = ['odom', 'base_footprint', 'base_link', 'front_right', 'front_left', 'camera_link', 'back_right_link', 'back_left_link', '']
        self.links = [[0, 0, 0, 0, 0, 0, 1],
                      [-0.0001752, 0.0001843, 0.6, 9.13834883249e-05, -0.00099, -0.00067, -0.9999],
                      [0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, -1],
                      [0.1335, -0.147, 0.022499, -1.40502493196e-07, -0.098, 9.73363327716e-08, -0.995],
                      [0.133500, 0.1472, 0.02249, -1.40502493196e-07, -0.098, 9.73363327716e-08, -0.995],
                      [0.262, -0.001, 0.1399, -0.001, 0.0001, 0.0010, -1],
                      [-0.137, -0.148, 0.022, -0.001, -0.128, -0.001, -1],
                      [-0.1390, 0.148, 0.022, -0.001, -0.125, 0.001, -1]]

        # Subscribe to the /imu topic
        rospy.Subscriber('/imu', Float64, self.imu_callback)
        rospy.Subscriber('/lw', Float64, self.lw_callback)
        rospy.Subscriber('/rw', Float64, self.rw_callback)

    def imu_callback(self, msg):
        # Parse the sensor readings from the message
        # Calculate linear and rotational values for encoder and IMU nodes
        self.imuData = [float(msg.data), float(msg.data), float(msg.data)]
        print(self.imuData)

    def lw_callback(self, msg):
        # Parse the sensor readings from the message
        # Calculate linear and rotational values for encoder and IMU nodes
        self.lwData = float(msg.data)
        print(self.lwData)

    def rw_callback(self, msg):
        # Parse the sensor readings from the message
        # Calculate linear and rotational values for encoder and IMU nodes
        self.rwData = float(msg.data)
        print(self.rwData)

    def publish_tf(self):
        rate = rospy.Rate(10)

        # Update tf tree at 10 Hz
        rospy.on_shutdown(myhook)
        while not rospy.is_shutdown():
            for i in range(len(self.parent_frames) - 2):
                # Update the tf transformations based on the latest sensor readings
                # Publish the updated tf transformations
                self.tf_broadcaster.sendTransform((self.links[i][0], self.links[i][1], self.links[i][2]),
                                                  (self.links[i][3], self.links[i][4], self.links[i][5], self.links[i][6]),
                                                  rospy.Time.now(),
                                                  self.child_frames[i],
                                                  self.parent_frames[i])

            self.links[2] = self.links[2] + [(self.lwData + self.rwData) / 2, 0, 0, self.imuData, 0, 0, 0]

            self.tf_broadcaster.sendTransform((self.links[2][0], self.links[2][1], self.links[2][2]),
                                              (self.links[2][3], self.links[2][4], self.links[2][5], self.links[2][6]),
                                              rospy.Time.now(),
                                              'base_link',
                                              'base_footprint')

            for i in range(5):
                i = i + 3
                self.tf_broadcaster.sendTransform(((self.links[2][0]), (self.links[2][1]), (self.links[2][2])),
                                                  (self.links[2][3], self.links[2][4], self.links[2][5], self.links[i][6]),
                                                  rospy.Time.now(),
                                                  self.child_frames[i],
                                                  'base_link')

            rate.sleep()

if __name__ == '__main__':
    try:
        tf_publisher = TFPublisher()
        tf_publisher.publish_tf()
    except rospy.ROSInterruptException:
        pass
