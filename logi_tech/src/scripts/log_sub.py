#!/usr/bin/env python3

import rospy
from sensor_msgs.msg import Joy

def joystick_callback(data):
    # Extract joystick directions
    x_axis = data.axes[0]
    y_axis = data.axes[1]
    
    pump_on = data.buttons[0]
    pump_off = data.buttons[2]
    servo_right = data.buttons[1]
    servo_left = data.buttons[3]
    stop = data.buttons[10]
    Manual = data.buttons[4]
    Auto = data.buttons[6]
    
    
    
    # Print joystick directions
    rospy.loginfo("Joystick Directions - X: {}, Y: {}".format(x_axis, y_axis))
    rospy.loginfo("buttons Values: {}".format(data.buttons))

    

def joystick_subscriber():
    # Initialize the ROS node
    rospy.init_node('joystick_subscriber', anonymous=True)
    
    # Subscribe to the joystick data topic
    rospy.Subscriber('/joystick_data', Joy, joystick_callback)
    
    # Spin the node to receive callbacks
    rospy.spin()

if __name__ == '__main__':
    joystick_subscriber()
