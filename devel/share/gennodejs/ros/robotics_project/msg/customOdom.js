// Auto-generated. Do not edit!

// (in-package robotics_project.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let nav_msgs = _finder('nav_msgs');

//-----------------------------------------------------------

class customOdom {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.odometry_type = null;
      this.odometry = null;
    }
    else {
      if (initObj.hasOwnProperty('odometry_type')) {
        this.odometry_type = initObj.odometry_type
      }
      else {
        this.odometry_type = '';
      }
      if (initObj.hasOwnProperty('odometry')) {
        this.odometry = initObj.odometry
      }
      else {
        this.odometry = new nav_msgs.msg.Odometry();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type customOdom
    // Serialize message field [odometry_type]
    bufferOffset = _serializer.string(obj.odometry_type, buffer, bufferOffset);
    // Serialize message field [odometry]
    bufferOffset = nav_msgs.msg.Odometry.serialize(obj.odometry, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type customOdom
    let len;
    let data = new customOdom(null);
    // Deserialize message field [odometry_type]
    data.odometry_type = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [odometry]
    data.odometry = nav_msgs.msg.Odometry.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.odometry_type.length;
    length += nav_msgs.msg.Odometry.getMessageSize(object.odometry);
    return length + 4;
  }

  static datatype() {
    // Returns string type for a message object
    return 'robotics_project/customOdom';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '137ce4daeefae7f73f3f6058efe4b8cb';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string odometry_type
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
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new customOdom(null);
    if (msg.odometry_type !== undefined) {
      resolved.odometry_type = msg.odometry_type;
    }
    else {
      resolved.odometry_type = ''
    }

    if (msg.odometry !== undefined) {
      resolved.odometry = nav_msgs.msg.Odometry.Resolve(msg.odometry)
    }
    else {
      resolved.odometry = new nav_msgs.msg.Odometry()
    }

    return resolved;
    }
};

module.exports = customOdom;
