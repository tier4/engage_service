// Copyright 2021 eve autonomy inc. All Rights Reserved.
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

#include <chrono>
#include <memory>
#include "awsm_dummy/awsm_dummy.hpp"

namespace awsm_dummy
{

Dummy::Dummy(
  const rclcpp::NodeOptions & options = rclcpp::NodeOptions())
: Node("awsm_dummy", options)
{
  using namespace std::placeholders;

  // Callback group
  callback_group_service_ = this->create_callback_group(
    rclcpp::CallbackGroupType::MutuallyExclusive);

  // Service
  srv_engage_ = this->create_service<tier4_external_api_msgs::srv::Engage>(
    "/api/external/set/engage",
    std::bind(
      &Dummy::execEngageProcess, this,
      std::placeholders::_1, std::placeholders::_2));

}

void Dummy::execEngageProcess(
  const tier4_external_api_msgs::srv::Engage::Request::SharedPtr request,
  const tier4_external_api_msgs::srv::Engage::Response::SharedPtr response)
{
  std::cout << "Request: engage = " << request->engage << std::endl;

  // Waiting a response
  response->status = tier4_api_utils::response_error("Received by Dummy.");

  return;
}
}  // namespace engage_relay_service

#include "rclcpp_components/register_node_macro.hpp"

RCLCPP_COMPONENTS_REGISTER_NODE(awsm_dummy::Dummy)
