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


#ifndef AWSM_DUMMY__AWSM_DUMMY_HPP_
#define AWSM_DUMMY__AWSM_DUMMY_HPP_

#include "rclcpp/rclcpp.hpp"

#include "tier4_api_utils/tier4_api_utils.hpp"
#include "tier4_external_api_msgs/srv/engage.hpp"

namespace awsm_dummy
{

class Dummy : public rclcpp::Node
{
public:
  explicit Dummy(const rclcpp::NodeOptions & options);

private:
  using ExternalEngage = tier4_external_api_msgs::srv::Engage;

  // Callback group
  rclcpp::CallbackGroup::SharedPtr callback_group_service_;

  // Service
  rclcpp::Service<tier4_external_api_msgs::srv::Engage>::SharedPtr srv_engage_;

  // Callback
  void execEngageProcess(
    const tier4_external_api_msgs::srv::Engage::Request::SharedPtr request,
    const tier4_external_api_msgs::srv::Engage::Response::SharedPtr response);
};

}  // namespace engage_relay_service

#endif  // AWSM_DUMMY__AWSM_DUMMY_HPP_