#!/usr/bin/env python3

import rospy
from sensor_msgs.msg import Joy, Imu
from std_msgs.msg import Float64, String
from control_msgs.msg import JointControllerState

class DifferentialDriveController:
    def __init__(self):
        rospy.init_node('differential_drive_controller')
        
        # Subscribe to joystick commands
        rospy.Subscriber('joystick_data', Joy, self.joy_callback)
        
        # Subscribe to wheel encoder data
        rospy.Subscriber('left_wheel_encoder', JointControllerState, self.left_encoder_callback)
        rospy.Subscriber('right_wheel_encoder', JointControllerState, self.right_encoder_callback)
        
        # Subscribe to IMU data
        rospy.Subscriber('imu', Imu, self.imu_callback)
        
        # Publish wheel efforts
        self.left_wheel_pub = rospy.Publisher('left_wheel_effort_controller/command', Float64, queue_size=10)
        self.right_wheel_pub = rospy.Publisher('right_wheel_effort_controller/command', Float64, queue_size=10)
        self.two_wheel_pub = rospy.Publisher('two_wheel_effort_controller/command', String, queue_size=10)

        # Initialize default wheel efforts
        self.left_wheel_effort = 0.0
        self.right_wheel_effort = 0.0
        self.stop = 0
        
        # Initialize PID gains
        self.p_gain = 0.1
        self.i_gain = 0.01
        self.d_gain = 0.001
        
        # Initialize encoder values
        self.left_encoder_value = 0.0
        self.right_encoder_value = 0.0
        
        # Initialize IMU data
        self.roll = 0.0
        self.pitch = 0.0
        self.yaw = 0.0
        
        # Initialize PID errors
        self.left_error_integral = 0.0
        self.right_error_integral = 0.0
        self.left_error_previous = 0.0
        self.right_error_previous = 0.0
        
        # Start the controller loop
        self.controller_loop()
    
    def joy_callback(self, data):
        # Convert joystick commands to wheel efforts
        max_joy_value = 1.0  # Maximum joystick value
        max_effort = 100.0  # Maximum wheel effort
        
        # Scale joystick commands to desired effort range
        self.left_wheel_effort = data.axes[0] #* max_effort * max_joy_value
        self.right_wheel_effort = data.axes[1] #* max_effort * max_joy_value
        self.stop = data.buttons[0]

    def left_encoder_callback(self, data):
        # Get the left wheel encoder value
        self.left_encoder_value = data.process_value
    
    def right_encoder_callback(self, data):
        # Get the right wheel encoder value
        self.right_encoder_value = data.process_value
    
    def imu_callback(self, data):
        # Get the IMU roll, pitch, and yaw
        self.roll = data.orientation.x
        self.pitch = data.orientation.y
        self.yaw = data.orientation.z
    
    def controller_loop(self):
        rate = rospy.Rate(10)  # Controller loop rate (10 Hz)
        
        while not rospy.is_shutdown():
            # Compute the PID errors
            left_error = self.left_wheel_effort - self.left_encoder_value
            right_error = self.right_wheel_effort - self.right_encoder_value
            
            # Update the integral term
            self.left_error_integral += left_error
            self.right_error_integral += right_error
            
            # Compute the derivative term
            left_error_derivative = left_error - self.left_error_previous
            right_error_derivative = right_error - self.right_error_previous
            
            # Compute the PID command
            left_command = (self.p_gain * left_error) + (self.i_gain * self.left_error_integral) + (self.d_gain * left_error_derivative)
            right_command = (self.p_gain * right_error) + (self.i_gain * self.right_error_integral) + (self.d_gain * right_error_derivative)
            
            # Apply IMU feedback to the commands (example: adjust left wheel effort based on roll angle)
            left_command += self.roll * 0.1  # Example scaling factor of 0.1 for roll angle adjustment
            right_command -= self.roll * 0.1  # Example scaling factor of 0.1 for roll angle adjustment
            left_command = ((self.left_wheel_effort + 0.99) / 1.9899) * 100
            right_command =((self.right_wheel_effort + 0.99) / 1.9899) * 100
            if (self.stop == 1):
                left_command = 0
                right_command = 0
            # Publish the PID commands as wheel efforts
            self.left_wheel_pub.publish(Float64(left_command))
            self.right_wheel_pub.publish(Float64(right_command))
            both = '@'+str(left_command)+'@'+str(right_command)
            print(both)
            self.two_wheel_pub.publish(both)

            # Store the previous errors
            self.left_error_previous = left_error
            self.right_error_previous = right_error
            
            rate.sleep()

if __name__ == '__main__':
    try:
        DifferentialDriveController()
    except rospy.ROSInterruptException:
        pass
