# ex03_coupling_app — MOOSE example reimplementation

This folder contains a small scaffold of the `ex03_coupling` MOOSE example (Example 3: Coupling).

Purpose
- Provide a ready-to-inspect copy of the example files so you can build the example inside a MOOSE development environment.

Files added
- `src/main.C` — example app main wrapper
- `src/kernels/ExampleConvection.C` — kernel implementation that couples another variable into the convective term
- `include/kernels/ExampleConvection.h` — kernel header
- `ex03.i` — MOOSE input file used to run the example
- `Makefile` — small Makefile wrapper that delegates to the MOOSE framework (expects `FRAMEWORK_DIR` / `MOOSE_DIR` to be set)

Requirements
- A working MOOSE development environment (MOOSE framework, PETSc, compilers). This scaffold does not include the framework — it integrates with it when building.

Quick build (from this folder in a shell with MOOSE available):

```powershell
# Set environment variables to point to your MOOSE repo and framework
$env:MOOSE_DIR = "C:\path\to\moose"
$env:FRAMEWORK_DIR = "${env:MOOSE_DIR}\/framework"

# Then run make
make
```

If you don't have MOOSE installed or prefer a lightweight demo, I can also produce a pure-Python pedagogical version that reproduces the coupling behaviour without MOOSE—tell me if you'd like that instead.
