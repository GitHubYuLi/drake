#pragma once

#include <memory>

#include "drake/common/drake_copyable.h"
#include "drake/systems/framework/leaf_system.h"

namespace drake {
namespace automotive {

/// IdmPlanner -- an IDM (Intelligent Driver Model) planner.
///
/// IDM: Intelligent Driver Model:
///    https://en.wikipedia.org/wiki/Intelligent_driver_model
///
/// Instantiated templates for the following kinds of T's are provided:
/// - double
/// - drake::TaylorVarXd
/// - drake::symbolic::Expression
///
/// They are already available to link against in the containing library.
///
/// @ingroup automotive_systems
///
/// Inputs:
///   0: @p x_ego ego car position (scalar) [m]
///   1: @p v_ego ego car velocity (scalar) [m/s]
///   2: @p x_agent agent car position (scalar) [m]
///   3: @p v_agent agent car velocity (scalar) [m/s]
/// Outputs:
///   0: @p vdot_ego linear acceleration of the ego car (scalar) [m/s^2].
template <typename T>
class IdmPlanner : public systems::LeafSystem<T> {
 public:
  DRAKE_NO_COPY_NO_MOVE_NO_ASSIGN(IdmPlanner)

  /// @p v_ref desired velocity of the ego car in units of m/s.
  explicit IdmPlanner(const T& v_ref);
  ~IdmPlanner() override;

  /// Returns the port to the ego car input subvector.
  const systems::InputPortDescriptor<T>& get_ego_port() const;

  /// Returns the port to the agent car input subvector.
  const systems::InputPortDescriptor<T>& get_agent_port() const;

  // System<T> overrides.
  // The output of this system is an algebraic relation of its inputs.
  bool has_any_direct_feedthrough() const override { return true; }

  std::unique_ptr<systems::Parameters<T>> AllocateParameters() const override;

  void SetDefaultParameters(const systems::LeafContext<T>& context,
                            systems::Parameters<T>* params) const override;

 private:
  void DoCalcOutput(const systems::Context<T>& context,
                    systems::SystemOutput<T>* output) const override;

  const T v_ref_;  // Desired vehicle velocity.
};

}  // namespace automotive
}  // namespace drake
