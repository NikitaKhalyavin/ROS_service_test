/*
 * Author: Nikita Khalyavin
 */

#include "ros/ros.h"
#include "service_test/ServiceType.h"

//for generating of random numbers
#include <ctime>


int main(int argc, char **argv)
{

  //prepare node
  ros::init(argc, argv, "service_test_client"); 
  ros::NodeHandle n = ros::NodeHandle();

  //init service
  const std::string SERVICE_NAME = "service_test";
  ros::ServiceClient client = n.serviceClient<service_test::ServiceType>(SERVICE_NAME);
  
  //prepare frequency control
  ros::Rate loop_rate(1);
  
  //prepare generator of random numbers
  std::srand(time(0));
  
  ROS_INFO("client is ready");
  
  while(ros::ok())
  {
  	//preparing of request data
  	service_test::ServiceType serviceRequest;
  	
  	//calculate random values of argument in range -500000 - 500000
  	serviceRequest.request.firstValue = ((double)std::rand()) / RAND_MAX * 
  								1000000 - 500000;
  	serviceRequest.request.secondValue = ((double)std::rand()) / RAND_MAX * 
  								1000000 - 500000;
  	//select random action of 4 allowed actions
  	char serviceAction;
  	int actionIndex = std::rand() % 4;
  	switch(actionIndex)
  	{
  		case 0:
  			serviceAction = '+';
  			break;
  		case 1:
  			serviceAction = '-';
  			break;
  		case 2:
  			serviceAction = '*';
  			break;
  		default:
  			serviceAction = '/';
  			break;
  	} 	
  	serviceRequest.request.action = serviceAction;
  	
  	//try to call the service
   	if (client.call(serviceRequest))
        {
        	//successful calling, show the results
       	ROS_INFO("Succesfull calling of the service.\nValues was:\n" 
       	"first value: %f\nsecondValue: %f\naction: %c\nResponse is: %f",
       	serviceRequest.request.firstValue, 
       	serviceRequest.request.secondValue, 
       	serviceRequest.request.action, 
       	serviceRequest.response.response
  		);
        }
	else
 	{
 		//error occured, stop the node
       	ROS_ERROR("Failed to call service");
       	return 1;
  	}
  	
  	//wait for next iteration
  	ros::spinOnce();
  	loop_rate.sleep();
  }

  return 0;
}
