;; Auto-generated. Do not edit!


(when (boundp 'robotics_project::customOdom)
  (if (not (find-package "ROBOTICS_PROJECT"))
    (make-package "ROBOTICS_PROJECT"))
  (shadow 'customOdom (find-package "ROBOTICS_PROJECT")))
(unless (find-package "ROBOTICS_PROJECT::CUSTOMODOM")
  (make-package "ROBOTICS_PROJECT::CUSTOMODOM"))

(in-package "ROS")
;;//! \htmlinclude customOdom.msg.html
(if (not (find-package "NAV_MSGS"))
  (ros::roseus-add-msgs "nav_msgs"))


(defclass robotics_project::customOdom
  :super ros::object
  :slots (_odometry_type _odometry ))

(defmethod robotics_project::customOdom
  (:init
   (&key
    ((:odometry_type __odometry_type) "")
    ((:odometry __odometry) (instance nav_msgs::Odometry :init))
    )
   (send-super :init)
   (setq _odometry_type (string __odometry_type))
   (setq _odometry __odometry)
   self)
  (:odometry_type
   (&optional __odometry_type)
   (if __odometry_type (setq _odometry_type __odometry_type)) _odometry_type)
  (:odometry
   (&rest __odometry)
   (if (keywordp (car __odometry))
       (send* _odometry __odometry)
     (progn
       (if __odometry (setq _odometry (car __odometry)))
       _odometry)))
  (:serialization-length
   ()
   (+
    ;; string _odometry_type
    4 (length _odometry_type)
    ;; nav_msgs/Odometry _odometry
    (send _odometry :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _odometry_type
       (write-long (length _odometry_type) s) (princ _odometry_type s)
     ;; nav_msgs/Odometry _odometry
       (send _odometry :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _odometry_type
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _odometry_type (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; nav_msgs/Odometry _odometry
     (send _odometry :deserialize buf ptr-) (incf ptr- (send _odometry :serialization-length))
   ;;
   self)
  )

(setf (get robotics_project::customOdom :md5sum-) "137ce4daeefae7f73f3f6058efe4b8cb")
(setf (get robotics_project::customOdom :datatype-) "robotics_project/customOdom")
(setf (get robotics_project::customOdom :definition-)
      "string odometry_type
nav_msgs/Odometry odometry
================================================================================
MSG: nav_msgs/Odometry
# This represents an estimate of a position and velocity in free space.  
# The pose in this message should be specified in the coordinate frame given by header.frame_id.
# The twist in this message should be specified in the coordinate frame given by the child_frame_id
Header header
string child_frame_id
geometry_msgs/PoseWithCovariance pose
geometry_msgs/TwistWithCovariance twist

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
string frame_id

================================================================================
MSG: geometry_msgs/PoseWithCovariance
# This represents a pose in free space with uncertainty.

Pose pose

# Row-major representation of the 6x6 covariance matrix
# The orientation parameters use a fixed-axis representation.
# In order, the parameters are:
# (x, y, z, rotation about X axis, rotation about Y axis, rotation about Z axis)
float64[36] covariance

================================================================================
MSG: geometry_msgs/Pose
# A representation of pose in free space, composed of position and orientation. 
Point position
Quaternion orientation

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

================================================================================
MSG: geometry_msgs/Quaternion
# This represents an orientation in free space in quaternion form.

float64 x
float64 y
float64 z
float64 w

================================================================================
MSG: geometry_msgs/TwistWithCovariance
# This expresses velocity in free space with uncertainty.

Twist twist

# Row-major representation of the 6x6 covariance matrix
# The orientation parameters use a fixed-axis representation.
# In order, the parameters are:
# (x, y, z, rotation about X axis, rotation about Y axis, rotation about Z axis)
float64[36] covariance

================================================================================
MSG: geometry_msgs/Twist
# This expresses velocity in free space broken into its linear and angular parts.
Vector3  linear
Vector3  angular

================================================================================
MSG: geometry_msgs/Vector3
# This represents a vector in free space. 
# It is only meant to represent a direction. Therefore, it does not
# make sense to apply a translation to it (e.g., when applying a 
# generic rigid transformation to a Vector3, tf2 will only apply the
# rotation). If you want your data to be translatable too, use the
# geometry_msgs/Point message instead.

float64 x
float64 y
float64 z
")



(provide :robotics_project/customOdom "137ce4daeefae7f73f3f6058efe4b8cb")


