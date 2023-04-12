// Copyright 2023 Tier IV, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License

#include <memory>
#include "engage_service_dummy.hpp"

namespace engage_service_dummy
{

EngageServiceDummy::EngageServiceDummy(
  const rclcpp::NodeOptions & options = rclcpp::NodeOptions())
: Node("engage_service_dummy", options)
{
  using std::placeholders::_1;
  using std::placeholders::_2;
  tier4_api_utils::ServiceProxyNodeInterface proxy(this);

  // Service
  srv_engage_ = proxy.create_service<tier4_external_api_msgs::srv::Engage>(
    "/api/external/set/engage",
    std::bind(&EngageServiceDummy::execEngageProcess, this,_1, _2));
}

void EngageServiceDummy::execEngageProcess(
  const tier4_external_api_msgs::srv::Engage::Request::SharedPtr request,
  const tier4_external_api_msgs::srv::Engage::Response::SharedPtr response)
{
  RCLCPP_DEBUG(this->get_logger(), "Requested /api/external/set/engage:%s",
               rosidl_generator_traits::to_yaml(*request).c_str());

  response->status = tier4_api_utils::response_success("Received by EngageServiceDummy.");
}
}  // namespace engage_service_dummy

#include "rclcpp_components/register_node_macro.hpp"

RCLCPP_COMPONENTS_REGISTER_NODE(engage_service_dummy::EngageServiceDummy)
