#!/usr/bin/env python3
import rospy
import tf_conversions
import tf2_ros
import geometry_msgs.msg
from sensor_msgs.msg import Temperature, Imu


def handle_imu_pose(msg):
    br = tf2_ros.TransformBroadcaster()   
    br2 = tf2_ros.TransformBroadcaster()  
    t = geometry_msgs.msg.TransformStamped()

    t.header.stamp = rospy.Time.now()
    t.header.frame_id = "plane"
    t.child_frame_id = "imu_link"
    t.transform.translation.x = 0
    t.transform.translation.y = 0
    t.transform.translation.z = 0
    t.transform.rotation.x = msg.orientation.x
    t.transform.rotation.y = msg.orientation.y
    t.transform.rotation.z = msg.orientation.z
    t.transform.rotation.w = msg.orientation.w
    br.sendTransform(t)
    t.header.frame_id = "imu_link"
    t.child_frame_id = "base_link"
    t.transform.translation.x = 0
    t.transform.translation.y = 0
    t.transform.translation.z = 0
    t.transform.rotation.x = msg.orientation.x
    t.transform.rotation.y = msg.orientation.y
    t.transform.rotation.z = msg.orientation.z
    t.transform.rotation.w = msg.orientation.w
    br2.sendTransform(t)


def handle_temp_pose(msg):
    sensor_frame = 'temperature_sensor'
    parent_frame = 'base_link'
    temp = tf2_ros.TransformBroadcaster()    

    transform = geometry_msgs.msg.TransformStamped()

    transform.header.stamp = rospy.Time.now()
    transform.header.frame_id = parent_frame
    transform.child_frame_id = sensor_frame
    transform.transform.translation.x = 0.0
    transform.transform.translation.y = 0.0
    transform.transform.translation.z = 0.0
    transform.transform.rotation.x = 0.0
    transform.transform.rotation.y = 0.0
    transform.transform.rotation.z = 0.0
    transform.transform.rotation.w = 1.0
    # Publish the transform
    temp.sendTransform(transform)

def handle_mq_pose():
    sensor_frame = 'MQ7_sensor'
    parent_frame = 'base_link'
    mq = tf2_ros.TransformBroadcaster()    

    transform = geometry_msgs.msg.TransformStamped()

    transform.header.stamp = rospy.Time.now()
    transform.header.frame_id = parent_frame
    transform.child_frame_id = sensor_frame
    transform.transform.translation.x = 0.0
    transform.transform.translation.y = 0.0
    transform.transform.translation.z = 0.0
    transform.transform.rotation.x = 0.0
    transform.transform.rotation.y = 0.0
    transform.transform.rotation.z = 0.0
    transform.transform.rotation.w = 1.0
    # Publish the transform
    mq.sendTransform(transform)
     

if __name__ == '__main__':
      rospy.init_node('tf_broadcaster_imu')
      rospy.Subscriber('/imu', Imu, handle_imu_pose)
      rospy.Subscriber('/temp', Imu, handle_temp_pose)
      rospy.Subscriber('/MQ7', Imu, handle_mq_pose)


      rospy.spin()
