#!/usr/bin/env python3

import rospy
import pygame

from sensor_msgs.msg import Joy



def joystick_publisher():
    # Initialize pygame
    pygame.init()

    # Set up the joystick
    pygame.joystick.init()
    joystick = pygame.joystick.Joystick(4)
    joystick.init()

    # Get the number of axes and buttons
    num_axes = joystick.get_numaxes()
    num_buttons = joystick.get_numbuttons()

    # Initialize the ROS node
    rospy.init_node('joystick_publisher', anonymous=True)

    # Create a publisher for the joystick data
    pub = rospy.Publisher('/joystick_data', Joy, queue_size=10)

    # Set the publishing rate
    rate = rospy.Rate(10)  # 10 Hz

    while not rospy.is_shutdown():
        # Handle events
        pygame.event.pump()

        # Read axes values
        axes = [joystick.get_axis(i) for i in range(num_axes)]

        # Read button states
        buttons = [joystick.get_button(i) for i in range(num_buttons)]

        # Create a Joy message
        joystick_msg = Joy()
        joystick_msg.axes = axes
        joystick_msg.buttons = buttons
        msg = joystick_msg

        # Publish the Joy message
        pub.publish(msg)

        # Sleep to maintain the publishing rate
        rate.sleep()

if __name__ == '__main__':
    try:
        joystick_publisher()
    except rospy.ROSInterruptException:
        pass
