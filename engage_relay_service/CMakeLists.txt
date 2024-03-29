# Copyright 2023 Tier IV, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

cmake_minimum_required(VERSION 3.5)
project(engage_relay_service)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic -Wno-unused-parameter)
endif()

find_package(ament_cmake_auto REQUIRED)
ament_auto_find_build_dependencies()

ament_auto_add_executable(engage_relay_service
  src/engage_relay_service.cpp
  src/engage_relay_service_node.cpp
)

set(LAUNCH_DIR launch)

if(BUILD_TESTING)
  ament_auto_add_library(engage_service_dummy SHARED
    test/src/engage_service_dummy.cpp
  )

  target_include_directories(engage_service_dummy
    PRIVATE test/src
  )

  rclcpp_components_register_node(engage_service_dummy
    PLUGIN "engage_service_dummy::EngageServiceDummy"
    EXECUTABLE engage_service_dummy_node)

  set(LAUNCH_DIR ${LAUNCH_DIR} test/launch)

endif()

ament_auto_package(INSTALL_TO_SHARE
  ${LAUNCH_DIR}
)
