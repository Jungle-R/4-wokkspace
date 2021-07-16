// Generated by gencpp from file mavros_msgs/ParamSet.msg
// DO NOT EDIT!


#ifndef MAVROS_MSGS_MESSAGE_PARAMSET_H
#define MAVROS_MSGS_MESSAGE_PARAMSET_H

#include <ros/service_traits.h>


#include <mavros_msgs/ParamSetRequest.h>
#include <mavros_msgs/ParamSetResponse.h>


namespace mavros_msgs
{

struct ParamSet
{

typedef ParamSetRequest Request;
typedef ParamSetResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;

}; // struct ParamSet
} // namespace mavros_msgs


namespace ros
{
namespace service_traits
{


template<>
struct MD5Sum< ::mavros_msgs::ParamSet > {
  static const char* value()
  {
    return "c423cafb898fff374cbe8530ecd4d285";
  }

  static const char* value(const ::mavros_msgs::ParamSet&) { return value(); }
};

template<>
struct DataType< ::mavros_msgs::ParamSet > {
  static const char* value()
  {
    return "mavros_msgs/ParamSet";
  }

  static const char* value(const ::mavros_msgs::ParamSet&) { return value(); }
};


// service_traits::MD5Sum< ::mavros_msgs::ParamSetRequest> should match
// service_traits::MD5Sum< ::mavros_msgs::ParamSet >
template<>
struct MD5Sum< ::mavros_msgs::ParamSetRequest>
{
  static const char* value()
  {
    return MD5Sum< ::mavros_msgs::ParamSet >::value();
  }
  static const char* value(const ::mavros_msgs::ParamSetRequest&)
  {
    return value();
  }
};

// service_traits::DataType< ::mavros_msgs::ParamSetRequest> should match
// service_traits::DataType< ::mavros_msgs::ParamSet >
template<>
struct DataType< ::mavros_msgs::ParamSetRequest>
{
  static const char* value()
  {
    return DataType< ::mavros_msgs::ParamSet >::value();
  }
  static const char* value(const ::mavros_msgs::ParamSetRequest&)
  {
    return value();
  }
};

// service_traits::MD5Sum< ::mavros_msgs::ParamSetResponse> should match
// service_traits::MD5Sum< ::mavros_msgs::ParamSet >
template<>
struct MD5Sum< ::mavros_msgs::ParamSetResponse>
{
  static const char* value()
  {
    return MD5Sum< ::mavros_msgs::ParamSet >::value();
  }
  static const char* value(const ::mavros_msgs::ParamSetResponse&)
  {
    return value();
  }
};

// service_traits::DataType< ::mavros_msgs::ParamSetResponse> should match
// service_traits::DataType< ::mavros_msgs::ParamSet >
template<>
struct DataType< ::mavros_msgs::ParamSetResponse>
{
  static const char* value()
  {
    return DataType< ::mavros_msgs::ParamSet >::value();
  }
  static const char* value(const ::mavros_msgs::ParamSetResponse&)
  {
    return value();
  }
};

} // namespace service_traits
} // namespace ros

#endif // MAVROS_MSGS_MESSAGE_PARAMSET_H