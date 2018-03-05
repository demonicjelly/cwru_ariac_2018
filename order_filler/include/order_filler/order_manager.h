//order_filler class
#ifndef ORDER_FILLER_H_
#define ORDER_FILLER_H_
#include <string>
#include <vector>
#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <ariac_xform_utils/ariac_xform_utils.h>
#include <bin_inventory/bin_inventory.h>
#include <osrf_gear/Order.h>

using namespace std;

const int ORDER_VECTOR_PENDING = 0;
const int ORDER_VECTOR_PRIORITY= 1;
const int ORDER_VECTOR_UNFILLABLE=2;

class OrderManager
{
public:
  OrderManager(ros::NodeHandle* nodehandle);
  bool order_is_fillable(osrf_gear::Order order);
  void update_inventory();
  void print_parts_list(std::vector<int> parts_list);
  bool parts_available(std::vector<int> parts_list);
  bool choose_order(osrf_gear::Order &order);
  bool current_order_has_been_filled(); //delete order from its vector
  
  void print_inventory(std::vector<PartInventory> inventory);
  void get_inventory(std::vector<PartInventory> &inventory);

private:
  ros::NodeHandle nh_; 
  BinInventory * p_binInventory_;
  XformUtils xformUtils;
  std::vector<osrf_gear::Order> pending_orders_;
  std::vector<osrf_gear::Order> priority_orders_;
  std::vector<osrf_gear::Order> unfillable_orders_;
  osrf_gear::Order current_order_in_process_;
  int current_order_vector_code_;
  int current_order_index_;
  bool order_is_in_process_;
  ros::Subscriber order_subscriber_;
  void order_callback(const osrf_gear::Order::ConstPtr & order_msg);
  geometry_msgs::PoseStamped target_pose_to_world_coords(geometry_msgs::Pose part_pose_wrt_box, 
     geometry_msgs::PoseStamped box_pose_wrt_world);
  bool is_priority(osrf_gear::Order order);
  void move_order_to_unfillable(int order_num,std::vector<osrf_gear::Order> order_vec);
  std::vector<PartInventory> inventory_;
//  int num_rcvd_new_orders_;

// {
//    ROS_INFO_STREAM("Received order:\n" << *order_msg);
//    received_orders_.push_back(*order_msg);
//  }


  
}; // note: a class definition requires a semicolon at the end of the definition

#endif
