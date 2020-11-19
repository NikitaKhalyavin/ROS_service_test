/*
 * Author: Nikita Khalyavin
 */

#include "ros/ros.h"
#include "service_test/ServiceType.h"

//callback function which is called each time the service request is received
bool getMessageCallback(service_test::ServiceType::Request& req, 
		service_test::ServiceType::Response& res)
{
 
 //get valus from the request
 double firstValue = req.firstValue;
 double secondValue = req.secondValue;
 char action = req.action;
 double result;
 
 //run the required action
 switch(action)
 {
 	case '+':
 		result = firstValue + secondValue;
 		break;
 	case '-':
 		result = firstValue - secondValue;
 		break;
 	case '*':
 		result = firstValue * secondValue;
 		break;
 	case '/':
 		result = firstValue / secondValue;
 		break;
	default:
		//this action is not supported 
 		ROS_INFO("ERROR: unknown action");
 		return false;    		
 }
 
  //write and return the result
  res.response = result;
  return true;
}


int main(int argc, char **argv)
{

  //prepare node
  ros::init(argc, argv, "service_test_server"); 
  ros::NodeHandle n = ros::NodeHandle();

  //init service
  const std::string SERVICE_NAME = "service_test";
  ros::ServiceServer service = n.advertiseService(SERVICE_NAME, getMessageCallback);
  
  ROS_INFO("node server is ready");
  
  //wait for requests 
  ros::spin();

  return 0;
}
