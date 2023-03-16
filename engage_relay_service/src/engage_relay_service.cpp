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

#include <chrono>
#include <memory>
#include "engage_relay_service/engage_relay_service.hpp"

namespace engage_relay_service
{

EngageRelayService::EngageRelayService(
  const rclcpp::NodeOptions & options = rclcpp::NodeOptions())
: Node("engage_relay_service", options)
{
  using std::placeholders::_1;
  using std::placeholders::_2;
  tier4_api_utils::ServiceProxyNodeInterface proxy(this);

  // Callback group
  callback_group_service_ = create_callback_group(
    rclcpp::CallbackGroupType::MutuallyExclusive);

  // Service
  srv_auto_engage_ = proxy.create_service<ExternalEngage>(
    "/in_parking/set/auto_engage",
    std::bind(&EngageRelayService::execEngageProcess, this, _1, _2),
    rmw_qos_profile_services_default, callback_group_service_);

  // Client
  cli_engage_ = proxy.create_client<ExternalEngage>(
    "/api/external/set/engage", rmw_qos_profile_services_default);
}

void EngageRelayService::execEngageProcess(
  const tier4_external_api_msgs::srv::Engage::Request::SharedPtr request,
  const tier4_external_api_msgs::srv::Engage::Response::SharedPtr response)
{
  const auto [status, resp] = cli_engage_->call(request);
  if (!tier4_api_utils::is_success(status)) {
    response->status = status;
    return;
  }

  response->status = resp->status;
}
}  // namespace engage_relay_service
