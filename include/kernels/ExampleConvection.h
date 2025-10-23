// ExampleConvection.h — kernel header for the coupling example
// Adapted from idaholab/moose `ex03_coupling`

#pragma once

#include "Kernel.h"

class ExampleConvection : public Kernel
{
public:
  ExampleConvection(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

private:
  const VariableGradient & _grad_some_variable;
};
