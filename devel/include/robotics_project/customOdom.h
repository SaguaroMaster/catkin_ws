// Generated by gencpp from file robotics_project/customOdom.msg
// DO NOT EDIT!


#ifndef ROBOTICS_PROJECT_MESSAGE_CUSTOMODOM_H
#define ROBOTICS_PROJECT_MESSAGE_CUSTOMODOM_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <nav_msgs/Odometry.h>

namespace robotics_project
{
template <class ContainerAllocator>
struct customOdom_
{
  typedef customOdom_<ContainerAllocator> Type;

  customOdom_()
    : odometry_type()
    , odometry()  {
    }
  customOdom_(const ContainerAllocator& _alloc)
    : odometry_type(_alloc)
    , odometry(_alloc)  {
  (void)_alloc;
    }



   typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _odometry_type_type;
  _odometry_type_type odometry_type;

   typedef  ::nav_msgs::Odometry_<ContainerAllocator>  _odometry_type;
  _odometry_type odometry;





  typedef boost::shared_ptr< ::robotics_project::customOdom_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::robotics_project::customOdom_<ContainerAllocator> const> ConstPtr;

}; // struct customOdom_

typedef ::robotics_project::customOdom_<std::allocator<void> > customOdom;

typedef boost::shared_ptr< ::robotics_project::customOdom > customOdomPtr;
typedef boost::shared_ptr< ::robotics_project::customOdom const> customOdomConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::robotics_project::customOdom_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::robotics_project::customOdom_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::robotics_project::customOdom_<ContainerAllocator1> & lhs, const ::robotics_project::customOdom_<ContainerAllocator2> & rhs)
{
  return lhs.odometry_type == rhs.odometry_type &&
    lhs.odometry == rhs.odometry;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::robotics_project::customOdom_<ContainerAllocator1> & lhs, const ::robotics_project::customOdom_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace robotics_project

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsFixedSize< ::robotics_project::customOdom_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::robotics_project::customOdom_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::robotics_project::customOdom_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::robotics_project::customOdom_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::robotics_project::customOdom_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::robotics_project::customOdom_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::robotics_project::customOdom_<ContainerAllocator> >
{
  static const char* value()
  {
    return "137ce4daeefae7f73f3f6058efe4b8cb";
  }

  static const char* value(const ::robotics_project::customOdom_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x137ce4daeefae7f7ULL;
  static const uint64_t static_value2 = 0x3f3f6058efe4b8cbULL;
};

template<class ContainerAllocator>
struct DataType< ::robotics_project::customOdom_<ContainerAllocator> >
{
  static const char* value()
  {
    return "robotics_project/customOdom";
  }

  static const char* value(const ::robotics_project::customOdom_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::robotics_project::customOdom_<ContainerAllocator> >
{
  static const char* value()
  {
    return "string odometry_type\n"
"nav_msgs/Odometry odometry\n"
"================================================================================\n"
"MSG: nav_msgs/Odometry\n"
"# This represents an estimate of a position and velocity in free space.  \n"
"# The pose in this message should be specified in the coordinate frame given by header.frame_id.\n"
"# The twist in this message should be specified in the coordinate frame given by the child_frame_id\n"
"Header header\n"
"string child_frame_id\n"
"geometry_msgs/PoseWithCovariance pose\n"
"geometry_msgs/TwistWithCovariance twist\n"
"\n"
"================================================================================\n"
"MSG: std_msgs/Header\n"
"# Standard metadata for higher-level stamped data types.\n"
"# This is generally used to communicate timestamped data \n"
"# in a particular coordinate frame.\n"
"# \n"
"# sequence ID: consecutively increasing ID \n"
"uint32 seq\n"
"#Two-integer timestamp that is expressed as:\n"
"# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n"
"# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n"
"# time-handling sugar is provided by the client library\n"
"time stamp\n"
"#Frame this data is associated with\n"
"string frame_id\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/PoseWithCovariance\n"
"# This represents a pose in free space with uncertainty.\n"
"\n"
"Pose pose\n"
"\n"
"# Row-major representation of the 6x6 covariance matrix\n"
"# The orientation parameters use a fixed-axis representation.\n"
"# In order, the parameters are:\n"
"# (x, y, z, rotation about X axis, rotation about Y axis, rotation about Z axis)\n"
"float64[36] covariance\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/Pose\n"
"# A representation of pose in free space, composed of position and orientation. \n"
"Point position\n"
"Quaternion orientation\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/Point\n"
"# This contains the position of a point in free space\n"
"float64 x\n"
"float64 y\n"
"float64 z\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/Quaternion\n"
"# This represents an orientation in free space in quaternion form.\n"
"\n"
"float64 x\n"
"float64 y\n"
"float64 z\n"
"float64 w\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/TwistWithCovariance\n"
"# This expresses velocity in free space with uncertainty.\n"
"\n"
"Twist twist\n"
"\n"
"# Row-major representation of the 6x6 covariance matrix\n"
"# The orientation parameters use a fixed-axis representation.\n"
"# In order, the parameters are:\n"
"# (x, y, z, rotation about X axis, rotation about Y axis, rotation about Z axis)\n"
"float64[36] covariance\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/Twist\n"
"# This expresses velocity in free space broken into its linear and angular parts.\n"
"Vector3  linear\n"
"Vector3  angular\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/Vector3\n"
"# This represents a vector in free space. \n"
"# It is only meant to represent a direction. Therefore, it does not\n"
"# make sense to apply a translation to it (e.g., when applying a \n"
"# generic rigid transformation to a Vector3, tf2 will only apply the\n"
"# rotation). If you want your data to be translatable too, use the\n"
"# geometry_msgs/Point message instead.\n"
"\n"
"float64 x\n"
"float64 y\n"
"float64 z\n"
;
  }

  static const char* value(const ::robotics_project::customOdom_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::robotics_project::customOdom_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.odometry_type);
      stream.next(m.odometry);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct customOdom_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::robotics_project::customOdom_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::robotics_project::customOdom_<ContainerAllocator>& v)
  {
    s << indent << "odometry_type: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.odometry_type);
    s << indent << "odometry: ";
    s << std::endl;
    Printer< ::nav_msgs::Odometry_<ContainerAllocator> >::stream(s, indent + "  ", v.odometry);
  }
};

} // namespace message_operations
} // namespace ros

#endif // ROBOTICS_PROJECT_MESSAGE_CUSTOMODOM_H
