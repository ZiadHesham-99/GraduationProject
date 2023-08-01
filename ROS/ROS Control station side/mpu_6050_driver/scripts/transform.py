#!/usr/bin/env python3

import rospy
import tf2_ros
import geometry_msgs.msg

def publish_transform():
    rospy.init_node('transform_publisher')
    broadcaster = tf2_ros.TransformBroadcaster()

    while not rospy.is_shutdown():
        transform = geometry_msgs.msg.TransformStamped()
        transform.header.stamp = rospy.Time.now()
        transform.header.frame_id = 'world'
        transform.child_frame_id = 'imu_link'
        transform.transform.translation.x = 1.0  # Adjust the translation values as needed
        transform.transform.translation.y = 2.0
        transform.transform.translation.z = 3.0
        transform.transform.rotation.x = 0.0  # Adjust the rotation values as needed
        transform.transform.rotation.y = 0.0
        transform.transform.rotation.z = 0.0
        transform.transform.rotation.w = 1.0

        broadcaster.sendTransform(transform)
        rospy.sleep(0.1)  # Adjust the publishing rate as needed

if __name__ == '__main__':
    try:
        publish_transform()
    except rospy.ROSInterruptException:
        pass
