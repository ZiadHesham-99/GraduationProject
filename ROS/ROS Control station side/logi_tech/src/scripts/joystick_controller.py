#!/usr/bin/env python3

import rospy
from sensor_msgs.msg import Joy
from std_msgs.msg import Float64
def joystick_callback(data):
    # Extract joystick axes
    vel = data.axes[1]  # Left joystick vertical axis
    steer = data.axes[2]  # Right joystick horizontal axis

    # Calculate desired commands
    left_cmd = vel + steer
    right_cmd = vel - steer

    # Publish commands to the effort controllers
    left_pub.publish(left_cmd)
    right_pub.publish(right_cmd)
    
if __name__ == '__main__':
    rospy.init_node('joystick_controller')

    # Create publishers for left and right effort commands
    left_pub = rospy.Publisher('joint1_Position_controller/command', Float64, queue_size=10)
    right_pub = rospy.Publisher('joint2_Position_controller/command', Float64, queue_size=10)

    # Subscribe to the joystick topic
    rospy.Subscriber('joy', Joy, joystick_callback)

    # Spin the node
    rospy.spin()

