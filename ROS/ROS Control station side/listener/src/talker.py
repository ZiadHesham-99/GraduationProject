#!/usr/bin/python3.8

import queue
import rospy
from std_msgs.msg import Int32, Float32,String
from sensor_msgs.msg import Imu, Temperature


from I2C import I2C
from data_handler import Data_Handler

def talker():
    Data_Size           = 64
    temp_pub           =rospy.Publisher('/temp',Temperature , queue_size=10)
    mQ7_pub            =rospy.Publisher('/mq7', Int32, queue_size=10)
    lencoderval_pub    =rospy.Publisher('/left_wheel_encoder', Float32, queue_size=10)
    rencoderval_pub    =rospy.Publisher('/right_wheel_encoder', Float32, queue_size=10)
    lencoderdir_pub    =rospy.Publisher('/left_wheel_encoder_dir', String, queue_size=10)
    rencoderdir_pub    =rospy.Publisher('/right_wheel_encoder_dir', String, queue_size=10)
    imu_pub            =rospy.Publisher('/imu', Imu, queue_size=10)
    I2C_DEVICE = I2C()
    rospy.init_node('talker', anonymous=True)
    rate = rospy.Rate(10)  # 10hz
    hello_str = "hello world %s" % rospy.get_time()
    rospy.loginfo(hello_str)
    while not rospy.is_shutdown():
        Frame = I2C_DEVICE.recieve_sensors_data(Data_Size)
        Send = Data_Handler.String_parser(Frame)
        Send = [45,-211,-91,-75,995,8740,8740,'+',75,'+',75]
        temp = 75
        mQ7  = Send[0]
        lencoderval = Send[8]
        rencoderval = Send[10]
        lencoderdir = Send[7]
        rencoderdir = Send[9]
        imu_msg = Imu()
        temp_msg = Temperature()
        imu_msg.header.stamp = rospy.Time.now()
        imu_msg.angular_velocity.x = Send[1]
        imu_msg.angular_velocity.y = Send[2]
        imu_msg.angular_velocity.z = Send[3]
        imu_msg.linear_acceleration.x = Send[4]
        imu_msg.linear_acceleration.y = Send[5]
        imu_msg.linear_acceleration.z = Send[6]
        temp_msg.header.stamp = rospy.Time.now()
        temp_msg.temperature = 25.0
        temp_msg.variance = 0.1
        
        if Send != '':
            temp_pub.publish(temp_msg)
            mQ7_pub.publish(mQ7)
            lencoderdir_pub.publish(lencoderdir)
            lencoderval_pub.publish(lencoderval)
            rencoderdir_pub.publish(rencoderdir)
            rencoderval_pub.publish(rencoderval)
            imu_pub.publish(imu_msg)

            print(Send)
        rate.sleep()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
