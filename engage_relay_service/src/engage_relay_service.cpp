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
#include "engage_relay_service/engage_relay_service.hpp"

namespace engage_relay_service
{

EngageRelayService::EngageRelayService(
  const rclcpp::NodeOptions & options = rclcpp::NodeOptions())
: Node("engage_relay_service", options)
{
  using namespace std::placeholders;

  // Callback group
  callback_group_service_ = this->create_callback_group(
    rclcpp::CallbackGroupType::MutuallyExclusive);

  // Service
  srv_auto_engage_ = this->create_service<tier4_external_api_msgs::srv::Engage>(
    "/in_parking/set/auto_engage",
    std::bind(
      &EngageRelayService::execEngageProcess, this,
      std::placeholders::_1, std::placeholders::_2));

  // Client
  cli_engage_ = this->create_client<tier4_external_api_msgs::srv::Engage>(
    "/api/external/set/engage",
    rmw_qos_profile_services_default, callback_group_service_);
}

void EngageRelayService::execEngageProcess(
  const tier4_external_api_msgs::srv::Engage::Request::SharedPtr request,
  const tier4_external_api_msgs::srv::Engage::Response::SharedPtr response)
{
  auto req =
    std::make_shared<tier4_external_api_msgs::srv::Engage::Request>();
  req->engage = request->engage;

  // Sending a request to autoware_state_machine
  auto result = cli_engage_->async_send_request(req);

  // Waiting a response
  if(result.wait_for(std::chrono::seconds(3)) == std::future_status::ready) {
    response->status = result.get()->status;
  } else {
    response->status = tier4_api_utils::response_error("No response from /api/external/set/engage.");
  }

  return;
}
}  // namespace engage_relay_service

#include "rclcpp_components/register_node_macro.hpp"

RCLCPP_COMPONENTS_REGISTER_NODE(engage_relay_service::EngageRelayService)
