/*********************************************************************
 *
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2020 Samsung Research Russia
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of the <ORGANIZATION> nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************/

#ifndef NAV2_COSTMAP_2D__COSTMAP_FILTER_HPP_
#define NAV2_COSTMAP_2D__COSTMAP_FILTER_HPP_

#include "rclcpp/rclcpp.hpp"

#include <string>

#include "nav2_costmap_2d/costmap_layer.hpp"

namespace nav2_costmap_2d
{

class CostmapFilter : public CostmapLayer
{
public:
  CostmapFilter();
  ~CostmapFilter();

  /** Layer API **/
  virtual void onInitialize();
  virtual void updateBounds(
    double robot_x, double robot_y, double robot_yaw,
    double * min_x, double * min_y, double * max_x, double * max_y);
  virtual void updateCosts(
    nav2_costmap_2d::Costmap2D & master_grid,
    int min_i, int min_j, int max_i, int max_j);
  virtual void matchSize();

  virtual void activate();
  virtual void deactivate();
  virtual void reset();

  /** CostmapFilter API **/
  /**
   * @brief: Loads map filter. Creates subscriptions to a map filter related topics
   * @param: Name of semantic info topic for map filter
   */
  virtual void loadFilter(
    const std::string semantic_info_topic) = 0;

  /**
   * @brief: An algorithm for how to use that map's information. Fills the Costmap2D with
   *         calculated data and makes an action based on processed data
   * @param: Reference to a master costmap2d
   * @param: Low window map boundary OX
   * @param: Low window map boundary OY
   * @param: High window map boundary OX
   * @param: High window map boundary OY
   * @param: Robot position x
   * @param: Robot position y
   * @param: Robot orientation
   */
  virtual void process(
    nav2_costmap_2d::Costmap2D & master_grid,
    int min_i, int min_j, int max_i, int max_j,
    double robot_x, double robot_y, double robot_yaw) = 0;

  /**
   * @brief: Unloads map filter. Stops all subscriptions
   */
  virtual void unloadFilter() = 0;

private:
  /**
   * @brief: Name of semantic info topic
   */
  std::string semantic_info_topic_;

  /**
   * @brief: (Re)allocates a costmap_ member (inherited from Costmap2D and required for
   *         updating costmaps) when it is not allocated yet or master_grid size was changed
   * @param: Reference to a master costmap2d
   */
  void reAllocateCostmap(
    const nav2_costmap_2d::Costmap2D & master_grid);

  /**
   * @brief: Sets NO_INFORMATION value to costmap_ within given bounds
   * @param: Low window map boundary OX
   * @param: Low window map boundary OY
   * @param: High window map boundary OX
   * @param: High window map boundary OY
   */
  void clearCostmap(
    int min_i, int min_j, int max_i, int max_j);

  /**
   * @brief: Latest robot position
   */
  double latest_robot_x, latest_robot_y, latest_robot_yaw;

  /**
   * @brief: Sizes of costmap_
   */
  int costmap_size_x, costmap_size_y;
};

}  // namespace nav2_costmap_2d

#endif  // NAV2_COSTMAP_2D__COSTMAP_FILTER_HPP_
