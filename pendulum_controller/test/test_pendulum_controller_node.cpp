// Copyright 2020 Igor Recio
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
// limitations under the License.

#include <gtest/gtest.h>
#include <memory>
#include <vector>
#include "rclcpp/rclcpp.hpp"
#include "pendulum_controller/pendulum_controller_node.hpp"

using pendulum::pendulum_controller::PendulumControllerNode;

using lifecycle_msgs::msg::State;
using lifecycle_msgs::msg::Transition;

class InitNodesTest : public ::testing::Test
{
protected:
  std::vector<rclcpp::Parameter> params;
  rclcpp::NodeOptions node_options;
  std::vector<double> feedback_matrix = {-10.0000, -51.5393, 356.8637, 154.4146};

  static void SetUpTestCase()
  {
    ASSERT_FALSE(rclcpp::ok());
    rclcpp::init(0, nullptr);
    ASSERT_TRUE(rclcpp::ok());
  }

  void SetUp() override
  {
    params.emplace_back("state_topic_name", "joint_states");
    params.emplace_back("command_topic_name", "command");
    params.emplace_back("teleop_topic_name", "setpoint");
    params.emplace_back("command_publish_period_us", 10000);
    params.emplace_back("enable_topic_stats", false);
    params.emplace_back("topic_stats_topic_name", "controller_stats");
    params.emplace_back("topic_stats_publish_period_ms", 1000);
    params.emplace_back("deadline_duration_ms", 0);
    params.emplace_back("controller.feedback_matrix", feedback_matrix);
  }

  static void TearDownTestCase()
  {
    (void)rclcpp::shutdown();
  }
};

TEST_F(InitNodesTest, test_options_constructor) {
  node_options.parameter_overrides(params);

  const auto test_node =
    std::make_shared<PendulumControllerNode>(node_options);

  // auto names = test_node->get_node_names();

  EXPECT_STREQ("pendulum_controller", test_node->get_name());
  // EXPECT_STREQ("/ns", test_node->get_namespace());
  // EXPECT_STREQ("/ns/my_node", test_node->get_fully_qualified_name());
  // EXPECT_EQ(names.size(), 1u);
  // EXPECT_STREQ(names[0].c_str(), "/pendulum_controller");
  // EXPECT_STREQ("/", test_node->get_namespace());
}

TEST_F(InitNodesTest, test_transition) {
  node_options.parameter_overrides(params);

  const auto test_node =
    std::make_shared<PendulumControllerNode>(node_options);

  EXPECT_EQ(State::PRIMARY_STATE_UNCONFIGURED, test_node->get_current_state().id());
  ASSERT_EQ(
    State::PRIMARY_STATE_INACTIVE, test_node->trigger_transition(
      rclcpp_lifecycle::Transition(Transition::TRANSITION_CONFIGURE)).id());
  ASSERT_EQ(
    State::PRIMARY_STATE_ACTIVE, test_node->trigger_transition(
      rclcpp_lifecycle::Transition(Transition::TRANSITION_ACTIVATE)).id());
  ASSERT_EQ(
    State::PRIMARY_STATE_INACTIVE, test_node->trigger_transition(
      rclcpp_lifecycle::Transition(Transition::TRANSITION_DEACTIVATE)).id());
  ASSERT_EQ(
    State::PRIMARY_STATE_UNCONFIGURED, test_node->trigger_transition(
      rclcpp_lifecycle::Transition(Transition::TRANSITION_CLEANUP)).id());
  ASSERT_EQ(
    State::PRIMARY_STATE_FINALIZED, test_node->trigger_transition(
      rclcpp_lifecycle::Transition(Transition::TRANSITION_UNCONFIGURED_SHUTDOWN)).id());
}

TEST_F(InitNodesTest, test_param_constructor) {
  node_options.parameter_overrides(params);

  const auto test_node_ptr =
    std::make_shared<PendulumControllerNode>(node_options);
  auto names = test_node_ptr->get_node_names();

  // EXPECT_EQ(names.size(), 1u);
  // EXPECT_STREQ(names[0].c_str(), "/pendulum_controller");
  // EXPECT_STREQ("/", test_node_ptr->get_namespace());
}