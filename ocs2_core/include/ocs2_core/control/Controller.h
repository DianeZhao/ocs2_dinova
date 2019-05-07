#pragma once

#include <Eigen/Dense>
#include <memory>
#include <vector>

#include "ocs2_core/Dimensions.h"
#include "ocs2_core/control/ControllerType.h"

namespace ocs2 {

/**
 * The base class for all controllers.
 *
 * @tparam STATE_DIM: Dimension of the state space.
 * @tparam INPUT_DIM: Dimension of the control input space.
 */
template <size_t STATE_DIM, size_t INPUT_DIM>
class Controller
{
 public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  using dimensions_t = Dimensions<STATE_DIM, INPUT_DIM>;
  using scalar_t = typename dimensions_t::scalar_t;
  using scalar_array_t = typename dimensions_t::scalar_array_t;
  using state_vector_t = typename dimensions_t::state_vector_t;
  using input_vector_t = typename dimensions_t::input_vector_t;

  /**
   * Default constructor.
   */
  Controller() = default;

  /**
   * Default destructor.
   */
  virtual ~Controller() = default;

  /**
   * @brief Computes the control command at a given time and state.
   *
   * @param [in] t: Current time.
   * @param [in] x: Current state.
   * @return Current input.
   */
  virtual input_vector_t computeInput(const scalar_t& t, const state_vector_t& x) = 0;

  /**
   * @brief Saves the controller at a given time to an array structure for ROS transmission
   * @param[in] time query time
   * @param[out] flatArray The array that is to be filled, i.e., the compressed controller
   */
  virtual void flatten(scalar_t time, scalar_array_t& flatArray) const = 0;

  /**
   * @brief Restores and initializes the controller from a flattened array
   * @param[in] timeArray array of times
   * @param[in] flatArray2 The array the represents the compressed controller
   */
  virtual void unFlatten(const scalar_array_t& timeArray, const std::vector<scalar_array_t const*>& flatArray2) = 0;

  /**
   * @brief Prints the type of controller
   * @return ControllerType: what type of controller this is
   */
  virtual ControllerType getType() const = 0;

  /**
   * @brief clears and reverts back to an empty controller.
   * Therefore, if empty() method is called, it will return true.
   */
  virtual void clear() = 0;

  /**
   * @brief Fills all the data containers with zeros. Does not change size, does not change time array.
   */
  virtual void setZero() = 0;

  /**
   * Returns whether the class contains any information.
   *
   * @return true if it contains no information, false otherwise.
   */
  virtual bool empty() const = 0;

};

}  // namespace ocs2
