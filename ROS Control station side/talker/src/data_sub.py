#!/usr/bin/env python3

import rospy
from std_msgs.msg import String
from std_msgs.msg import Float64

import I2C
import data_sender

frame = 0
def callback(data):
    # Callback function to process received data
    rospy.loginfo("Received data: %s", data.data)
    frame[1] = data
    if (data<0):
        frame[3] = '+'
    else:
        frame[3] = '-'


def callback(data):
    rospy.loginfo("Received data: %s", data.data)
    pwm_left = data[0]
    if (data<0):
        dir_left = '+'
    else:
        dir_left = '-'
    pwm_right= data[1]
    if (data<0):
        dir_right = '+'
    else:
        dir_right = '-'
    movement_data = data_sender.movement_data_prepare(pwm_right, dir_right, pwm_left, dir_left)
    I2C.send_movement_data(I2C,movement_data)

def subscriber():
    # Initialize the ROS node
    rospy.init_node ('movement_data_node', anonymous=True)
    rospy.Subscriber('two_wheel_effort_controller/command', Float64, callback)


    # Set the publishing rate (10Hz in this example)
    rate = rospy.Rate(10)

    while not rospy.is_shutdown():
        # Create a message object
        msg = String()

        # Sleep for the specified rate
        rate.sleep()

if __name__ == '__main__':
    try:
        subscriber()
    except rospy.ROSInterruptException:
        pass
