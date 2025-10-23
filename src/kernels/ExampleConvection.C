// ExampleConvection.C — kernel implementation for ex03_coupling
// Adapted from idaholab/moose example

#include "ExampleConvection.h"

// Register the object with MOOSE using the application name used by the
// example. If you use a different application name, update the registration
// string accordingly.
registerMooseObject("ExampleApp", ExampleConvection);

InputParameters
ExampleConvection::validParams()
{
  InputParameters params = Kernel::validParams();

  // Allow the input file to specify a coupled variable that will supply a
  // gradient used as the velocity in our convective term.
  params.addRequiredCoupledVar("some_variable", "The gradient of this variable will be used as the velocity vector.");

  return params;
}

ExampleConvection::ExampleConvection(const InputParameters & parameters)
  : Kernel(parameters),
    _grad_some_variable(coupledGradient("some_variable"))
{
}

Real
ExampleConvection::computeQpResidual()
{
  // Residual: test * (grad(some_variable) * grad(u))
  return _test[_i][_qp] * (_grad_some_variable[_qp] * _grad_u[_qp]);
}

Real
ExampleConvection::computeQpJacobian()
{
  return _test[_i][_qp] * (_grad_some_variable[_qp] * _grad_phi[_j][_qp]);
}
