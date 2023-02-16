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


#ifndef ENGAGE_SERVICE_DUMMY__ENGAGE_SERVICE_DUMMY_HPP_
#define ENGAGE_SERVICE_DUMMY__ENGAGE_SERVICE_DUMMY_HPP_

#include "rclcpp/rclcpp.hpp"

#include "tier4_api_utils/tier4_api_utils.hpp"
#include "tier4_external_api_msgs/srv/engage.hpp"

namespace engage_service_dummy
{

class EngageServiceDummy : public rclcpp::Node
{
public:
  explicit EngageServiceDummy(const rclcpp::NodeOptions & options);

private:
  using ExternalEngage = tier4_external_api_msgs::srv::Engage;

  // Service
  tier4_api_utils::Service<tier4_external_api_msgs::srv::Engage>::SharedPtr srv_engage_;

  // Callback
  void execEngageProcess(
    const ExternalEngage::Request::SharedPtr request,
    const ExternalEngage::Response::SharedPtr response);
};

}  // namespace engage_service_dummy

#endif  // ENGAGE_SERVICE_DUMMY__ENGAGE_SERVICE_DUMMY_HPP_
