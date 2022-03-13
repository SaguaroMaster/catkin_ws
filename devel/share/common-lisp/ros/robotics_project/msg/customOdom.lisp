; Auto-generated. Do not edit!


(cl:in-package robotics_project-msg)


;//! \htmlinclude customOdom.msg.html

(cl:defclass <customOdom> (roslisp-msg-protocol:ros-message)
  ((odometry_type
    :reader odometry_type
    :initarg :odometry_type
    :type cl:string
    :initform "")
   (odometry
    :reader odometry
    :initarg :odometry
    :type nav_msgs-msg:Odometry
    :initform (cl:make-instance 'nav_msgs-msg:Odometry)))
)

(cl:defclass customOdom (<customOdom>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <customOdom>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'customOdom)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name robotics_project-msg:<customOdom> is deprecated: use robotics_project-msg:customOdom instead.")))

(cl:ensure-generic-function 'odometry_type-val :lambda-list '(m))
(cl:defmethod odometry_type-val ((m <customOdom>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robotics_project-msg:odometry_type-val is deprecated.  Use robotics_project-msg:odometry_type instead.")
  (odometry_type m))

(cl:ensure-generic-function 'odometry-val :lambda-list '(m))
(cl:defmethod odometry-val ((m <customOdom>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robotics_project-msg:odometry-val is deprecated.  Use robotics_project-msg:odometry instead.")
  (odometry m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <customOdom>) ostream)
  "Serializes a message object of type '<customOdom>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'odometry_type))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'odometry_type))
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'odometry) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <customOdom>) istream)
  "Deserializes a message object of type '<customOdom>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'odometry_type) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'odometry_type) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'odometry) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<customOdom>)))
  "Returns string type for a message object of type '<customOdom>"
  "robotics_project/customOdom")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'customOdom)))
  "Returns string type for a message object of type 'customOdom"
  "robotics_project/customOdom")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<customOdom>)))
  "Returns md5sum for a message object of type '<customOdom>"
  "137ce4daeefae7f73f3f6058efe4b8cb")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'customOdom)))
  "Returns md5sum for a message object of type 'customOdom"
  "137ce4daeefae7f73f3f6058efe4b8cb")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<customOdom>)))
  "Returns full string definition for message of type '<customOdom>"
  (cl:format cl:nil "string odometry_type~%nav_msgs/Odometry odometry~%================================================================================~%MSG: nav_msgs/Odometry~%# This represents an estimate of a position and velocity in free space.  ~%# The pose in this message should be specified in the coordinate frame given by header.frame_id.~%# The twist in this message should be specified in the coordinate frame given by the child_frame_id~%Header header~%string child_frame_id~%geometry_msgs/PoseWithCovariance pose~%geometry_msgs/TwistWithCovariance twist~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/PoseWithCovariance~%# This represents a pose in free space with uncertainty.~%~%Pose pose~%~%# Row-major representation of the 6x6 covariance matrix~%# The orientation parameters use a fixed-axis representation.~%# In order, the parameters are:~%# (x, y, z, rotation about X axis, rotation about Y axis, rotation about Z axis)~%float64[36] covariance~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%================================================================================~%MSG: geometry_msgs/TwistWithCovariance~%# This expresses velocity in free space with uncertainty.~%~%Twist twist~%~%# Row-major representation of the 6x6 covariance matrix~%# The orientation parameters use a fixed-axis representation.~%# In order, the parameters are:~%# (x, y, z, rotation about X axis, rotation about Y axis, rotation about Z axis)~%float64[36] covariance~%~%================================================================================~%MSG: geometry_msgs/Twist~%# This expresses velocity in free space broken into its linear and angular parts.~%Vector3  linear~%Vector3  angular~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'customOdom)))
  "Returns full string definition for message of type 'customOdom"
  (cl:format cl:nil "string odometry_type~%nav_msgs/Odometry odometry~%================================================================================~%MSG: nav_msgs/Odometry~%# This represents an estimate of a position and velocity in free space.  ~%# The pose in this message should be specified in the coordinate frame given by header.frame_id.~%# The twist in this message should be specified in the coordinate frame given by the child_frame_id~%Header header~%string child_frame_id~%geometry_msgs/PoseWithCovariance pose~%geometry_msgs/TwistWithCovariance twist~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/PoseWithCovariance~%# This represents a pose in free space with uncertainty.~%~%Pose pose~%~%# Row-major representation of the 6x6 covariance matrix~%# The orientation parameters use a fixed-axis representation.~%# In order, the parameters are:~%# (x, y, z, rotation about X axis, rotation about Y axis, rotation about Z axis)~%float64[36] covariance~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%================================================================================~%MSG: geometry_msgs/TwistWithCovariance~%# This expresses velocity in free space with uncertainty.~%~%Twist twist~%~%# Row-major representation of the 6x6 covariance matrix~%# The orientation parameters use a fixed-axis representation.~%# In order, the parameters are:~%# (x, y, z, rotation about X axis, rotation about Y axis, rotation about Z axis)~%float64[36] covariance~%~%================================================================================~%MSG: geometry_msgs/Twist~%# This expresses velocity in free space broken into its linear and angular parts.~%Vector3  linear~%Vector3  angular~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <customOdom>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'odometry_type))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'odometry))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <customOdom>))
  "Converts a ROS message object to a list"
  (cl:list 'customOdom
    (cl:cons ':odometry_type (odometry_type msg))
    (cl:cons ':odometry (odometry msg))
))
