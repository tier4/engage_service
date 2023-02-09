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


#ifndef ENGAGE_RELAY_SERVICE__ENGAGE_RELAY_SERVICE_HPP_
#define ENGAGE_RELAY_SERVICE__ENGAGE_RELAY_SERVICE_HPP_

#include "rclcpp/rclcpp.hpp"

#include "tier4_api_utils/tier4_api_utils.hpp"
#include "tier4_external_api_msgs/srv/engage.hpp"

namespace engage_relay_service
{

class EngageRelayService : public rclcpp::Node
{
public:
  explicit EngageRelayService(const rclcpp::NodeOptions & options);

private:
  using ExternalEngage = tier4_external_api_msgs::srv::Engage;

  // Callback group
  rclcpp::CallbackGroup::SharedPtr callback_group_service_;

  // Service
  tier4_api_utils::Service<ExternalEngage>::SharedPtr srv_auto_engage_;

  // Client
  tier4_api_utils::Client<ExternalEngage>::SharedPtr cli_engage_;

  // Callback
  void execEngageProcess(
    const tier4_external_api_msgs::srv::Engage::Request::SharedPtr request,
    const tier4_external_api_msgs::srv::Engage::Response::SharedPtr response);
};

}  // namespace engage_relay_service

#endif  // ENGAGE_RELAY_SERVICE__ENGAGE_RELAY_SERVICE_HPP_
