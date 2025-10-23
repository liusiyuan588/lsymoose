// Simple MOOSE application main — calls the framework main with ExampleApp.
#include "ExampleApp.h"
#include "MooseMain.h"

int main(int argc, char * argv[])
{
  return Moose::main<ExampleApp>(argc, argv);
}
