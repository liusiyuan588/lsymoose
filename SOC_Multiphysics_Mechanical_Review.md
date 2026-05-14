# Multiphysics Modeling of Mechanical Behavior in Solid Oxide Cells: Implications for Performance and Stability

---

## Abstract

Solid oxide cells (SOCs) — encompassing both solid oxide fuel cells (SOFCs) and solid oxide electrolysis cells (SOECs) — operate under extreme thermochemical environments that impose severe mechanical demands on their multi-layered ceramic and metallic constituents. Ensuring long-term structural integrity is a prerequisite for commercial viability, yet the mechanical failure mechanisms that limit SOC lifetime are intricate, coupled, and difficult to predict with single-physics models. This review surveys the current state of multiphysics modeling of mechanical behavior in SOCs, covering the principal failure modes (thermal expansion mismatch, redox-induced volume changes, brittle fracture, interfacial delamination, and creep), the spectrum of computational methods deployed to model them (continuum finite element analysis, extended finite element methods, phase-field models, cohesive zone models, peridynamics, and Lattice Boltzmann methods), and the emerging role of physics-informed neural networks. Experimental validation strategies — from micro-compression and double-torsion testing to operando synchrotron and electron-microscopy techniques — are reviewed and benchmarked against model predictions. The review concludes with guidelines for material and geometric design optimization and an outlook toward data-driven multiphysics frameworks.

**Keywords:** solid oxide fuel cell; solid oxide electrolysis cell; mechanical degradation; multiphysics modeling; phase-field method; fracture mechanics; creep; electro-chemo-mechanical coupling

---

## 1. Introduction

### 1.1 Background and Importance

Solid oxide cells (SOCs) represent one of the most thermodynamically efficient technologies for electrochemical energy conversion and storage. Operated in fuel cell mode (SOFC), they convert hydrogen or hydrocarbon fuels directly to electricity at efficiencies exceeding 60%; operated in electrolysis mode (SOEC), they split water and CO₂ into synthesis gas using renewable electricity, serving as a cornerstone of the power-to-X economy. Both modes operate at temperatures between 600 °C and 900 °C, and next-generation intermediate-temperature SOCs push toward 500–700 °C to improve material compatibility and reduce degradation rates.

Despite their electrochemical promise, the commercial deployment of SOCs has been persistently hindered by insufficient mechanical durability. The multi-layered cell architecture — comprising a porous ceramic anode support, a dense electrolyte membrane on the order of 5–20 µm, a mixed ionic-electronic cathode, and metallic interconnects — must survive thousands of thermal cycles and tens of thousands of hours of operation. Mechanical failure in any single layer or interface precipitates catastrophic performance loss: a crack in the electrolyte creates direct fuel-to-oxidant cross-leakage, while delamination at an electrode–electrolyte interface increases ohmic and polarization resistance, accelerating electrochemical degradation. The coupling between mechanical damage and electrochemical performance is therefore direct and consequential.

Understanding this coupling requires going beyond single-physics models. Thermal stresses arise from both temperature gradients during operation and differential thermal contraction during shutdown; chemical strains emerge from phase transformations (e.g., NiO reduction, Ni re-oxidation) and from the chemical expansion of mixed conductors under varying oxygen partial pressures; electrochemical gradients drive ion migration that interacts with the local stress state. No single discipline — solid mechanics, electrochemistry, or heat transfer — can capture this phenomenology in isolation. Multiphysics modeling, which integrates governing equations across domains, has therefore emerged as an essential tool for rationalizing SOC mechanical behavior and guiding next-generation design.

### 1.2 Degradation Mechanisms and Their Mechanical Origins

Degradation in SOCs manifests as a rise in both ohmic impedance, associated with reduced ionic conductivity in the electrolyte or contact loss at interfaces, and polarization impedance, associated with loss of active triple-phase boundary (TPB) length in porous electrodes. Both are mechanically mediated: microcracking in the electrolyte interrupts the ionic conduction path, electrode–electrolyte delamination increases interfacial resistance, and microstructural coarsening driven by stress-activated surface diffusion reduces TPB density. The interplay between electrochemical driving forces (local chemical potentials, current density distributions) and mechanical stresses creates feedback loops that accelerate degradation in a non-linear fashion.

### 1.3 Scope of This Review

This review focuses on the multiphysics modeling of mechanical behavior in SOCs over the period 2015–2025, with emphasis on: (i) the governing mechanical challenges and their microstructural origins; (ii) computational frameworks spanning continuum to microstructure-resolved scales; (iii) experimental validation methods; and (iv) design implications for improved durability. The review distinguishes between SOFC and SOEC operating conditions where relevant, as the different electrochemical boundary conditions — in particular, the oxygen partial pressure at the oxygen electrode — lead to qualitatively different stress states.

---

## 2. SOC Materials and Operating Conditions

### 2.1 Cell Architecture and Component Materials

A planar anode-supported SOC — the most widely commercialized configuration — consists of five primary structural layers, each with distinct mechanical properties.

**Anode/Fuel electrode (Ni-YSZ composite):** The support layer is typically a porous cermet of nickel and yttria-stabilized zirconia (YSZ), 300–1000 µm thick, produced by tape-casting and sintering. In the as-fabricated state it contains NiO rather than metallic Ni; reduction during initial startup increases porosity by approximately 30% through NiO-to-Ni volume contraction (~41% volumetric change per NiO formula unit). The resulting porous Ni-YSZ cermet has an elastic modulus on the order of 40–80 GPa depending on porosity (30–60%), Poisson ratio ≈ 0.28–0.31, and tensile strength 50–150 MPa. Its coefficient of thermal expansion (CTE) is approximately 12–13 × 10⁻⁶ K⁻¹ in the reduced state.

**Electrolyte (8YSZ or 3YSZ):** The dense electrolyte, 5–20 µm thick in anode-supported designs (up to 150 µm in electrolyte-supported), is the structurally critical membrane. 8 mol% YSZ (cubic phase) offers the highest ionic conductivity but lower fracture toughness (~1.0 MPa·m^(1/2)); 3 mol% YSZ (tetragonal phase, 3YSZ) offers transformation toughening with K_Ic values 2–4× higher, at the cost of lower ionic conductivity. The CTE of 8YSZ is approximately 10.5 × 10⁻⁶ K⁻¹, and the elastic modulus is 190–215 GPa at room temperature, decreasing to ~170 GPa at 800 °C.

**Cathode/Oxygen electrode (LSCF, LSC, or LSM):** Mixed ionic-electronic conductors such as La₀.₆Sr₀.₄Co₀.₂Fe₀.₈O₃₋δ (LSCF) or La₀.₈Sr₀.₂MnO₃ (LSM) serve as the cathode. LSCF has a CTE of approximately 15–17 × 10⁻⁶ K⁻¹ — substantially higher than YSZ — creating a significant thermal expansion mismatch. It also undergoes chemical expansion under varying oxygen partial pressures (chemical expansion coefficient ~0.01–0.04 per unit change in oxygen non-stoichiometry), contributing to stress accumulation under electrochemical cycling. Intermediate buffer layers of gadolinium-doped ceria (GDC) are routinely inserted between LSCF and YSZ to reduce this mismatch and block Sr interdiffusion.

**Metallic interconnects:** Ferritic stainless steels (e.g., Crofer 22 APU) are preferred for their CTE compatibility with YSZ (~11–12 × 10⁻⁶ K⁻¹ over the relevant temperature range). They also exhibit significant creep at operating temperatures, which critically influences the stress redistribution in the cell layers below.

**Contact layers and sealants:** Glass-ceramic sealants and metallic contact meshes complete the stack architecture. Their mechanical integrity, particularly their adhesion to electrode surfaces, is a key determinant of stack long-term durability.

### 2.2 Operating Conditions and Their Mechanical Implications

SOFCs typically operate between 700–900 °C under open-circuit voltage conditions of ~1 V per cell, with current densities of 0.3–1.0 A/cm². SOECs operate at similar temperatures but at voltages above the thermoneutral potential (~1.3 V), with the oxygen electrode under high oxygen partial pressure and the hydrogen electrode under steam/hydrogen mixtures. The higher oxygen activity at the SOEC oxygen electrode drives a significantly larger chemical expansion in LSCF, and the oxygen evolution reaction can generate localized pressurization at defects in the electrode–electrolyte interface, dramatically accelerating crack growth.

Both modes experience non-isothermal conditions: temperature gradients of 50–200 K across a single repeat unit are typical in planar stacks, driven by the distribution of electrochemical heat sources. Start-up (room temperature to 800 °C) and shutdown (800 °C to room temperature) impose cyclic thermo-mechanical loading even without electrochemical operation. Redox cycling — unintentional re-oxidation of the Ni anode during fuel supply interruptions — imposes an additional periodic volume change of approximately 30–40% in the affected zone, an order of magnitude larger than thermal strains.

---

## 3. Key Mechanical Challenges in Solid Oxide Cells

### 3.1 Thermal Expansion Mismatch and Stress Evolution

The most pervasive mechanical challenge in SOCs is the thermal expansion mismatch (ΔCαₑ) between adjacent layers. The CTE difference between LSCF (15–17 × 10⁻⁶ K⁻¹) and 8YSZ (10.5 × 10⁻⁶ K⁻¹) is approximately 5 × 10⁻⁶ K⁻¹. Over a temperature drop of 800 K during shutdown, this generates an in-plane biaxial strain mismatch of ~0.4%, which, combined with the high stiffness of both layers, produces interfacial stresses on the order of hundreds of MPa — comparable to or exceeding the fracture strength of the ceramic layers.

Finite element studies of full-size SOFC stacks have demonstrated that thermal stress distributions are strongly dependent on flow field geometry and stack size. Zhang et al. (2024) developed a fully coupled CFD-FEM model of full-scale SOFC stacks and found that the volume fraction of high-stress regions differs by nearly 30% for different gas flow configurations, with the cathode layer consistently exhibiting the highest failure probability [Zhang et al., Energies, 17, 2025, 2024]. Wang et al. (2018) showed through orthogonal design analysis of a five-cell planar SOFC stack that the CTE mismatch between the cell layers and the interconnect is the dominant factor governing peak stress, and that optimizing compressive stack loading and sealant design can substantially reduce stress concentrations [Wang et al., Int. J. Hydrogen Energy, 43, 20900, 2018].

The coupling between thermal and electrochemical fields further complicates the stress state: local current density non-uniformity creates hotspots that impose additional thermal gradients, and chemical expansion from variable oxygen stoichiometry in LSCF adds a chemically-driven strain component that is spatially correlated with the electrochemical current distribution.

### 3.2 Redox Cycling

Redox cycling — the oxidation of metallic Ni back to NiO upon fuel supply interruption — is perhaps the most destructive mechanical event that an SOC anode can experience. The NiO-to-Ni reduction involves a volumetric contraction of approximately 41%, so the reverse (reoxidation) imposes a swelling strain of similar magnitude in the affected zone. Unlike thermal strains, which are distributed relatively uniformly through the layer thickness, reoxidation fronts propagate from the exposed gas channels inward, creating steep spatial gradients in swelling strain that generate severe stress concentrations at the oxidation front.

Shang et al. (2018) proposed a continuously graded finite element model for inhomogeneous reoxidation-induced swelling in Ni-YSZ anodes, coupling creep relaxation with the advancing oxidation front. The model reveals that local oxidation fronts interact destructively with creep relaxation: while creep can alleviate stress at steady operating temperatures, it is insufficient to prevent fracture when reoxidation-induced swelling strains are applied rapidly [Shang et al., Int. J. Energy Res., 2018]. More recently, a coupled electrochemical-mechanical study by the ACS Sustainable Chemistry & Engineering group (2025) used combined phase-field and finite element models to quantify Ni particle migration and agglomeration during redox cycling, finding nearly a four-fold increase in large Ni cluster size after repeated redox cycles, which dramatically reduces TPB density and mechanical cohesion of the cermet [ACS Sustainable Chem. Eng., 2025].

### 3.3 Fracture in Brittle Ceramics

YSZ electrolytes and electrode materials are inherently brittle at temperatures below approximately 600 °C, where plastic deformation does not occur on engineering timescales. Failure is governed by fracture mechanics: the stress intensity factor K_I must remain below the fracture toughness K_Ic for crack arrest. The porous nature of electrode supports further degrades fracture properties relative to dense ceramics.

Quantitative measurement of fracture toughness in SOC-relevant materials has been a consistent focus. Pecanac et al. (2016) applied the double-torsion technique to measure K_Ic of NiO-3YSZ and NiO-8YSZ anode substrates in both oxidized and reduced states at room temperature and 800 °C, finding that reduced (metallic Ni-containing) samples show lower fracture toughness than their NiO counterparts, and that toughness decreases further at high temperature [Pecanac et al., J. Power Sources, 327, 629, 2016]. Khajavi et al. (2020) systematically evaluated six stabilized zirconia compositions, demonstrating that a NiO-1.5CeO₂-4.5YO₁.₅-SZ support achieves 30% higher K_Ic at room temperature and 10% higher at 800 °C compared to the conventional NiO-5.8YO₁.₅-SZ, primarily through Ce-induced stabilization of the tetragonal phase and its associated transformation toughening [Khajavi et al., J. Eur. Ceram. Soc., 40, 5670, 2020]. The micro-scale fracture properties of porous electrode supports were directly measured by Abaza et al. (2022) using micro-compression tests on 60 µm-diameter pillars milled by plasma FIB in porous YSZ pellets over a porosity range of 33–63%, revealing monotonically decreasing strength and modulus with porosity — critical input data for continuum fracture models [Abaza et al., J. Eur. Ceram. Soc., 42, 1656, 2022].

### 3.4 Interfacial Delamination

Interfacial failure between the electrodes and electrolyte, or between the cell and interconnect contact layer, is the mode most directly linked to electrochemical performance loss, since even partial delamination eliminates local current pathways and increases interfacial resistance. The thermodynamic driving force for delamination is quantified by the interfacial energy release rate G, which for thin-film systems under biaxial stress is given by G = Z σ²h/Ē, where σ is the in-plane stress, h is the film thickness, and Ē is the biaxial modulus.

Four-point bending measurements of SOC contact-layer systems at DTU (2020) demonstrated that the interfacial fracture energy varies by nearly an order of magnitude depending on contact-layer chemistry: a CuMn metallic spinel-forming foam contact layer yields G_c approximately eight times higher than conventional perovskite contact pastes, providing direct material selection guidance for stack durability [ACS Appl. Energy Mater., 3, 2372, 2020]. Xie et al. (2022) parametrically investigated the effect of electrode material properties on interfacial crack propagation, deriving optimization criteria showing that reducing the elastic modulus mismatch between electrode and electrolyte substantially decreases G at the interface, independent of CTE matching [Xie et al., Int. J. Hydrogen Energy, 47, 7975, 2022].

In SOECs specifically, the oxygen evolution at the oxygen electrode can generate localized high oxygen partial pressures at subsurface defects, creating a pressurized crack-driving mechanism that operates even in the absence of thermal gradients. Jayapragasam et al. (2023) developed an electro-chemo-mechanical multiphysics model linking electrochemical operating conditions to the mechanical driving force for interfacial crack growth at the oxygen electrode/electrolyte interface, validating crack growth rate predictions against long-term experimental degradation data and demonstrating that high current density operation dramatically accelerates delamination [Jayapragasam et al., J. Electrochem. Soc., 170, 054509, 2023].

### 3.5 Creep and Time-Dependent Deformation

At SOC operating temperatures (600–900 °C), creep — thermally activated, time-dependent plastic deformation — occurs in both ceramic components (YSZ electrolytes and electrodes) and metallic interconnects. Creep relaxation can be beneficial by relieving peak stresses after thermal transients, but accumulated creep strains over 40,000–100,000 hours of operation lead to permanent deformation, dimensional changes, and ultimately to contact loss or sealant failure.

Wang et al. (2022) combined FEM with a response surface method to optimize SOFC stack geometry for creep resistance, demonstrating that geometry optimization reduces the sealant Weibull failure probability from 0.994 to 0.015 over 100,000 hours at 600 °C under 20 MPa compressive load. Their analysis revealed that creep strains in the anode and sealant dominate the stack stress redistribution, while creep in the electrolyte and cathode is comparatively minor [Wang et al., Int. J. Hydrogen Energy, 47, 21450, 2022]. Luo et al. (2023) demonstrated that incorporating a cooling channel significantly reduces both creep damage accumulation and Weibull failure probability, with the mitigation effect strengthening at lower coolant temperatures — highlighting thermal management as a key lever for creep life extension [Luo et al., Front. Mater., 10, 1238559, 2023]. A 2026 MDPI Materials study performed a systematic compositional parametric study using coupled FEM creep-damage models over 50,000-hour simulations, finding that Ni volume fraction in the range 50–60% and high LSM-content cathodes represent the optimal balance between electrochemical performance and mechanical durability [Mater. (Basel), 19, 733, 2026].

---

## 4. Multiphysics Modeling Approaches

### 4.1 Continuum Mechanics — Elasticity, Plasticity, and Finite Element Analysis

The finite element method (FEM) is the workhorse of SOC mechanical modeling, owing to its flexibility in handling complex geometries, material heterogeneity, and coupled physics. In the continuum mechanics framework, each layer is treated as a homogeneous effective medium characterized by temperature-dependent elastic moduli, Poisson ratios, CTEs, and strength distributions. The governing equations are the equilibrium equations (∇·σ = 0), the strain-displacement relations (ε = (∇u + (∇u)^T)/2), and the constitutive law (σ = C:εᵉˡ for linear elasticity), supplemented by thermal, chemical, and creep eigenstrain contributions.

Modern SOC FEM implementations routinely incorporate multiple coupled physics solvers. The thermo-electro-chemo-mechanical (TECM) framework developed by Wu et al. (2021) for button-cell SOFCs accounts for residual sintering strains, thermal strains, chemical expansion from oxygen non-stoichiometry, and time-dependent creep and accelerated creep (primary, secondary) in all layers including the Ni-YSZ anode, 8YSZ electrolyte, and LSCF cathode. Simulations through an idealized duty cycle (room temperature → heating → reduction → three operating temperatures) reveal that the cathode–electrolyte interface experiences the highest principal stress during thermal ramp-up, while anode deformation is dominated by chemical expansion during reduction [Wu et al., J. Electrochem. Soc., 168, 2021]. Cai et al. (2023) extended the TECM approach to cells with LSCF-GDC composite cathodes, incorporating methanol reforming and CO-CO₂ electrochemical reactions to couple fuel composition gradients with the thermal and stress fields, demonstrating that local hotspots over the reforming zone concentrate mechanical stress in the electrolyte [Cai et al., Int. J. Mol. Sci., 24, 4137, 2023].

For stack-level analysis, the computational challenge lies in the disparity between the thin-film scale of the electrolyte (~10 µm) and the full-stack scale (~10 cm). Zhang et al. (2024) addressed this through a multi-resolution strategy, using a fully coupled CFD-FEM model of full-size SOFC stacks to resolve thermal stress at the cell level without resolving individual electrode microstructures [Zhang et al., Energies, 17, 2025, 2024]. Similarly, SOEC stack modeling by Energies (2023) found that temperature gradient — rather than absolute temperature — is the dominant factor controlling thermal stress and failure probability, and that flow field configuration has a greater effect on mechanical performance than previously recognized [Energies, 16, 7720, 2023].

The latest Acta Mechanica study (2025) achieved a particularly comprehensive formulation, incorporating anisotropic effective material properties derived by numerical homogenization, steady-state creep with partially anisotropic material symmetry, and simultaneous solution of the electrochemical, thermal, and mechanical fields, providing distributions of current density, species concentration, temperature, and stress in a single computation [Acta Mech., 2025]. Transient TECM analyses of electrolyte-supported SOECs under dynamic renewable energy inputs (2025) have further shown that stepped current density control induces higher heating rates and mechanical stress peaks than stepped voltage control — a finding with direct operational implications for grid-coupled SOEC systems [Energy Convers. Manag. X, 2025].

### 4.2 Fracture and Damage Modeling

#### 4.2.1 Extended Finite Element Method (XFEM)

The extended finite element method enriches the standard FEM displacement field with discontinuous and near-tip asymptotic functions, allowing crack surfaces and fronts to be represented independently of the mesh. This eliminates the need for remeshing as cracks grow, making XFEM attractive for brittle ceramic systems where crack paths are not known a priori.

Shao et al. (2014) pioneered the coupling of XFEM crack propagation with Darcy-flow and Navier-Stokes fluid dynamics in multilayered porous/dense SOC-like configurations, demonstrating that internal gas pressure at the crack face significantly amplifies the stress intensity factor — a mechanism of particular relevance to the SOC hydrogen electrode under redox conditions [Shao et al., Int. J. Fracture, 185, 155, 2014]. Jiang et al. (2019) implemented XFEM within the BISON multiphysics nuclear fuel performance code for coupled thermo-mechanical fracture of UO₂ ceramics — a closely analogous brittle system — validating the approach against experimental crack patterns and demonstrating that fuel relocation due to cracking significantly alters the temperature field [Jiang et al., Eng. Fract. Mech., 223, 106713, 2019]. The hybrid "Xfield" method (Giovanardi et al., 2017), which combines a global XFEM displacement field with a local phase-field problem near the crack tip, retains geometric sharpness while handling complex crack topologies including branching and coalescence — capabilities essential for the multi-crack environments typical in SOC ceramics under thermal cycling [Giovanardi et al., Comput. Methods Appl. Mech. Eng., 320, 396, 2017].

#### 4.2.2 Phase-Field Method (PFM)

The phase-field method represents fracture through a scalar damage variable φ ∈ [0,1] that smoothly transitions from intact (φ=0) to fully cracked (φ=1) material. The crack surface is replaced by a diffuse interface of finite width controlled by a regularization length ℓ. The governing equations follow from minimizing an energy functional comprising elastic strain energy, fracture surface energy (Griffith criterion), and coupling terms. PFM has become the preferred framework for brittle fracture in SOC research owing to its ability to handle crack initiation, propagation, branching, and coalescence without ad hoc criteria.

Xue et al. (2023, NETL/OSTI) implemented a phase-field fracture model incorporating SOC microstructures and phase-dependent material properties to simulate crack initiation and growth under thermal and redox cycling on the hydrogen electrode side. Under thermal cycling, work-zone cracking dominates in electrolyte-supported SOCs with cracks initiating at triple-phase boundaries; under redox cycling, cracks are driven by volume expansion of re-oxidized Ni particles. The model identifies crack mitigation strategies including reducing support porosity and synchronizing thermal and oxidation strain rates [Xue et al., Int. J. Hydrogen Energy, 47, 2023]. Moshkelgosha & Mamivand (2020) developed a PFM that fully couples the tetragonal-to-monoclinic martensitic phase transformation in zirconia to the variational fracture formulation, capturing transformation toughening mechanistically and explaining why 3YSZ can sustain far higher stresses than predicted by linear elastic fracture mechanics [Moshkelgosha & Mamivand, Comput. Mater. Sci., 174, 109509, 2020]. Xie et al. (2019) showed that corrugated SOFC geometry reduces both crack propagation rate and interfacial energy release rate during cooling relative to planar geometry, providing a simple geometric design lever for improved durability [Xie et al., Int. J. Energy Res., 43, 3020, 2019].

Quantifying mechanical degradation directly from reconstructed electrode microstructures, a 2024 Journal of the Mechanics and Physics of Solids study established a thermodynamically consistent framework integrating FEM with PFM to reveal interactions between species-defect transport, electrochemical reaction kinetics, stress, and mechanical damage in SOC electrodes. The framework was validated against FIB-SEM microstructure reconstructions under both SOFC and SOEC operating modes, providing microstructure-to-cell-level mechanical degradation maps [JMPS, 105607, 2024].

#### 4.2.3 Cohesive Zone Modeling (CZM)

Cohesive zone models represent the fracture process zone ahead of a crack tip through a traction-separation law relating interface opening displacement to cohesive traction. CZM is particularly well-suited for modeling delamination at pre-defined interfaces — such as the electrode–electrolyte or electrode–interconnect interfaces — where the crack path is constrained by geometry.

Yang et al. (2022) coupled CZM with a full electrochemical-transport model to compute the evolution of area-specific resistance as interface delamination and active layer cracking progress, demonstrating clear electrochemical signatures in polarization curves and impedance spectra corresponding to specific crack geometries. The model provides a pathway from mechanical damage state to observable electrochemical degradation indicators [Yang et al., Int. J. Hydrogen Energy, 47, 2022]. Most recently, Kurushina et al. (2025) implemented CZM for thermomechanical deformation of a metal-supported tubular SOEC, identifying up to eight distinct deformation zones near fixed boundaries as likely crack initiation sites, with the highest debonding risk at electrolyte–electrode interfaces near thermal gradients — the first CZM-based structural assessment of tubular SOEC architecture [Kurushina et al., Eng. Fract. Mech., 2025].

#### 4.2.4 Lattice Boltzmann Method (LBM)

While LBM is not a fracture method in the classical sense, it has been increasingly adopted for pore-scale simulation of mass transport, electrochemical reactions, and ion migration in porous SOC electrodes, providing the microstructure-resolved driving forces that feed into mechanical stress calculations. A 2024 Journal of Power Sources review comprehensively surveyed LBM applications to pore-scale diffusion and electrochemical reactions at triple-phase boundaries in SOFC/SOEC electrodes [J. Power Sources, 234015, 2024]. Zhao et al. (2024) combined 3D FIB-SEM microstructure reconstruction with LBM to investigate mass transfer in reversible SOC (rSOC) porous fuel electrodes under dynamic load switching between SOFC and SOEC modes, optimizing electrode porosity and tortuosity to minimize transport losses [Electrochim. Acta, 143562, 2024]. Liu et al. (2024) used LBM on reconstructed anode microstructures to track pore-scale gas transport changes during initial aging, quantifying the contribution of Ni coarsening and TPB reduction to macroscopic performance decline [Int. J. Miner. Metall. Mater., 31, 405, 2024].

#### 4.2.5 Peridynamics

Peridynamics (PD) is a reformulation of continuum mechanics that replaces the classical spatial derivative (divergence of stress) with an integral over a finite horizon, enabling natural handling of discontinuities without special treatment at crack tips. This makes PD particularly attractive for brittle fracture simulations where multiple cracks initiate and interact spontaneously.

Wang et al. (2017) applied PD for the first time to porous SOFC plates under operating temperature gradients, demonstrating that crack initiation occurs preferentially at electrode–electrolyte interfaces where thermal expansion mismatch is highest, consistent with experimental failure observations [Wang et al., AIMS Energy, 5, 585, 2017]. Xiang et al. (2022) advanced this by using ordinary state-based PD on 3D anode microstructures reconstructed by FIB-SEM, revealing that micro-crack nucleation occurs at Ni–YSZ phase boundaries and that microstructure heterogeneity is the dominant driver of fracture localization [Xiang et al., J. Peridyn. Nonlocal Model., 4, 201, 2022]. A 2022 Journal of Power Sources study integrated adaptive thermo-mechanical PD into a multiphysics framework alongside FEM and phase-field components, providing quantitative damage maps for different Ni-YSZ compositions under severe thermal shock conditions [J. Power Sources, 231775, 2022]. The combination of FEM for heat transfer with PD for fracture was demonstrated by Giannakeas et al. (2018) for alumina thermal shock, reproducing characteristic multi-crack network patterns including inter-crack spacing — a methodology directly transferable to SOC electrolyte thermal cycling analysis [Giannakeas et al., J. Eur. Ceram. Soc., 38, 3037, 2018].

The principal advantage of PD over PFM in this context is that it does not require an artificial regularization length parameter; instead, the horizon size is physically motivated by the material's internal length scale. However, PD is computationally more demanding than PFM for equivalent crack resolution, and its constitutive theory for coupled thermo-electro-mechanical problems in anisotropic materials is still under active development. For this reason, PFM remains the more common choice in the SOC literature, while PD offers a promising alternative for extreme thermal shock scenarios.

### 4.3 Creep and Thermo-Mechanical Models

Time-dependent deformation in SOC components is modeled by augmenting the elastic constitutive law with a creep strain rate tensor:

**ε̇_cr = f(σ, T, t)**

where the functional form depends on the dominant creep mechanism. For YSZ ceramics at SOC temperatures, diffusional creep (Nabarro-Herring or Coble) is typically dominant, giving a linear dependence on stress and a strong dependence on grain size. For metallic interconnects, power-law creep (Norton's law) is appropriate: **ε̇_cr = A σⁿ exp(-Q/RT)**, with n ≈ 5–8 and activation energies Q in the range 200–350 kJ/mol.

The 2022 FEM-RSM study by Wang et al. is notable for identifying that the sealant and anode dominate stack creep damage, not the electrolyte, contrary to the intuition that the stiffest layer (electrolyte) governs the stress state [Wang et al., Int. J. Hydrogen Energy, 47, 21450, 2022]. Luo et al. (2023) showed quantitatively how cooling channel placement modifies the temperature field and thereby redistributes creep damage away from critical electrolyte regions [Luo et al., Front. Mater., 10, 1238559, 2023]. For SOEC-specific operation, the transient TECM model (Energy Conversion and Management: X, 2025) found that dynamic load cycling — as expected in wind- or solar-coupled SOEC systems — produces repeated stress peaks at the electrolyte that accumulate fatigue-creep damage at a rate significantly higher than under steady-state operation.

### 4.4 Electro-Chemo-Mechanical Coupling

The most comprehensive modeling frameworks couple all four relevant physics: electrochemical reactions and ion transport, heat generation and conduction, chemical strain from oxygen non-stoichiometry, and mechanical deformation. The governing equations form a tightly coupled nonlinear system:

- **Charge conservation:** ∇·i = 0 with Butler-Volmer kinetics at electrode surfaces
- **Species transport:** ∂cₖ/∂t + ∇·Jₖ = Rₖ (diffusion-migration with electrochemical source terms)
- **Energy equation:** ρcp ∂T/∂t = ∇·(k∇T) + Q̇_EC + Q̇_ohmic
- **Mechanical equilibrium:** ∇·σ = 0 with σ = C:(ε - εᵀ - εᶜʰ - εᶜʳ)

where εᵀ is thermal eigenstrain, εᶜʰ is chemical eigenstrain from oxygen non-stoichiometry, and εᶜʳ is creep strain. The coupling is bidirectional: stress influences ion migration through the mechanical contribution to chemical potential (μ = μ₀ + RT ln a + Ωσₘ, where Ω is the molar volume and σₘ is the mean stress), and ion migration generates concentration gradients that produce chemical expansion.

Shape deformation analysis of anode-supported SOFCs by electro-chemo-mechanical simulation (2018) demonstrated how oxygen ion migration under electrochemical gradients generates chemically-induced strains that warp the cell — a critical consideration for the assembly tolerance of multi-cell stacks [Int. J. Mech. Sci., 2018]. The most recent and complete treatment (Acta Mechanica, 2025) performs full anisotropic TECM analysis with homogenized effective properties derived from representative volume element calculations, enabling scale-consistent prediction of stress distributions across the full range of spatial scales from grain to stack [Acta Mech., 2025]. The 3D time-dependent Acta Mechanica study (2025) bridges microstructure-resolved and cell-scale modeling, demonstrating how microstructural heterogeneity propagates to macroscale mechanical response over operational timescales [Acta Mech., 2025].

For SOEC-specific electro-chemo-mechanical coupling, the study by Jayapragasam et al. (2023) stands out: by linking electrochemical operating state directly to the stress intensity factor at the oxygen electrode/electrolyte interface as a function of crack length, the model provides an unprecedented electrochemical-to-fracture-mechanics connection, quantitatively linking operating current density to interfacial crack growth rate [Jayapragasam et al., J. Electrochem. Soc., 170, 054509, 2023].

### 4.5 Machine Learning and Physics-Informed Neural Networks

#### 4.5.1 Current State of ML in SOC Mechanical Prediction

The application of machine learning to SOC degradation is primarily in the electrochemical domain. Padinjarethil et al. (2021) applied support vector regression to an in-house SOC database of ~2,135 tests, extracting degradation parameters from electrochemical impedance spectroscopy and demonstrating that ML outperforms linear regression for lifetime assessment, with a mean prediction accuracy of ~99% [Padinjarethil et al., Fuel Cells, 21, 566, 2021]. ML has been applied to cathode poisoning prediction [J. Mater. Chem. A, 10, 23683, 2022] and SOEC performance optimization [Processes, 13, 875, 2025], but direct application to mechanical failure prediction in SOCs remains sparse.

For broader ceramic fracture prediction, Wang et al. (2021) introduced StressNet — a deep learning model using a Temporal Independent Convolutional Neural Network (TI-CNN) coupled with Bidirectional LSTM — to predict the full time sequence of stress states during fracture propagation in brittle materials. The model achieves real-time stress prediction during dynamic fracture, capabilities that would be highly valuable if trained on SOC-specific microstructure datasets [Wang et al., npj Mater. Degrad., 5, 6, 2021]. ML models for predicting fracture toughness and crack path in ceramics with micro-defects have also been demonstrated using random forest and neural network approaches trained on FEM-generated datasets [Eng. Fract. Mech., 108900, 2022].

#### 4.5.2 Physics-Informed Neural Networks for Fracture

Physics-informed neural networks (PINNs) encode the governing partial differential equations of fracture mechanics as soft constraints in the neural network loss function, enabling mesh-free solutions of fracture problems. For phase-field fracture, Goswami et al. (2020) introduced a PINN that minimizes the variational energy functional rather than the PDE residual, reducing derivative order requirements and simplifying boundary condition imposition. Transfer learning across different crack configurations achieves significant computational speedup relative to conventional FEM phase-field solvers [Goswami et al., Theor. Appl. Fract. Mech., 106, 102447, 2020]. Manav et al. (2024) demonstrated a deep Ritz PINN approach for phase-field fracture capturing crack nucleation, propagation, kinking, branching, and coalescence without a structured mesh — a capability set that encompasses most crack topologies observed in SOC ceramics [Manav et al., Comput. Methods Appl. Mech. Eng., 429, 117104, 2024]. A 2023 Frontiers in Physics study enhanced the PINN phase-field framework with length-scale decoupling degradation functions, enabling independent control of regularization and fracture energy parameters for improved accuracy in sharp-transition geometries [Front. Phys., 11, 1152811, 2023].

No published study has yet directly applied PINN-based fracture prediction to SOC-specific geometries and loading. However, the methodological foundations are in place: once a phase-field or XFEM model of SOC fracture has been validated experimentally (see Section 5), the trained PINN surrogate can be used for rapid parametric studies over composition (e.g., Ni volume fraction, YSZ stabilizer content), geometry (electrolyte thickness, electrode porosity), and operating conditions — precisely the design exploration task that is computationally prohibitive with full FEM. This represents the most promising near-term avenue for data-driven multiphysics prediction of SOC mechanical durability.

---

## 5. Experimental Studies for Model Validation

### 5.1 Mechanical Testing Techniques

#### 5.1.1 Flexural Strength and Fracture Toughness

Flexural strength testing — via three-point or four-point bending of bar specimens — is the standard method for characterizing the tensile strength of SOC ceramic layers. Because ceramics exhibit statistical failure governed by the weakest flaw, results are analyzed using Weibull statistics to extract the Weibull modulus m and characteristic strength σ₀. Ring-on-ring biaxial flexure testing provides a multi-axial stress state more representative of in-plane stresses in planar cell geometries. The Forschungszentrum Jülich group (2018) performed ring-on-ring tests on SOC half-cell assemblies at room temperature and elevated temperature in both oxidized and reduced states, extracting temperature-dependent Weibull moduli and incorporating subcritical crack growth analysis to predict time-dependent failure probability during long-term operation [Ceramics Int., 44, 2018].

Fracture toughness K_Ic is measured by double-torsion (Pecanac et al., 2016), single-edge-notched beam (SENB), or Vickers indentation techniques. The double-torsion method is preferred for SOC-relevant porous substrates because it allows stable crack propagation and provides reliable K_Ic even for materials with moderate porosity. For thin electrolyte films, nanoindentation-based fracture toughness extraction is emerging as an alternative. Interfacial fracture toughness between electrode and electrolyte is measured by four-point bending of sandwich specimens, as demonstrated by the DTU contact-layer study (2020) and the 2025 Ceramics International interfacial adhesion study [Ceramics Int., 2025].

#### 5.1.2 High-Temperature Creep Testing

Creep properties of SOC components are typically measured by uniaxial compression creep testing in tube furnaces at temperatures of 600–900 °C under controlled atmospheres. Steady-state creep rates are extracted and fitted to Norton's power law to determine the creep exponent n and activation energy Q. For Ni-YSZ cermets, the creep behavior shifts significantly between the oxidized and reduced states and depends strongly on Ni volume fraction and YSZ grain size. Displacement-controlled testing using high-temperature extensometers allows measurement of both primary and secondary creep regimes.

### 5.2 In-Situ and Ex-Situ Studies

#### 5.2.1 In-Situ X-Ray Stress Monitoring

Yamaguchi et al. (2025) demonstrated X-ray stress analysis via the cos α method for in-situ monitoring of stress evolution in co-fired electrolytes of metal-supported SOCs at elevated temperatures under controlled atmospheres. This non-destructive technique directly measures residual stress development during co-firing and thermal cycling without removing the cell from the test environment, providing critical validation data for TECM models of co-sintered systems [Yamaguchi et al., J. Power Sources, 235892, 2025]. Synchrotron X-ray diffraction provides higher spatial resolution and can resolve stress gradients through the electrolyte thickness, enabling layer-by-layer stress determination during thermal cycling.

#### 5.2.2 Operando Electron Microscopy

The landmark operando study by Jeangros et al. (2023) used a heating-and-biasing MEMS device inside an environmental TEM to observe a full cathode–electrolyte–anode cell under actual operating conditions — controlled atmosphere, temperature, and applied voltage — at atomic-scale resolution. Direct correlation was established between environmental conditions, open-circuit voltage, and microstructural evolution at the electrolyte–electrode interface during operation [Jeangros et al., Nat. Commun., 14, 7959, 2023]. While this technique is currently limited to thin-film model systems, it provides ground-truth mechanistic data (e.g., Sr segregation, interface chemistry changes) that informs constitutive models of interfacial degradation.

#### 5.2.3 Thermo-Mechanical Cycling

Ex-situ post-mortem analysis after controlled thermo-mechanical cycling provides statistical data on crack density, delamination extent, and microstructural changes as a function of cycle number and thermal ramp rate. SEM cross-sections, FIB-SEM tomography, and X-ray computed tomography (XCT) are used to characterize the three-dimensional crack network and quantify damage accumulation. These datasets are essential for validating phase-field and peridynamic crack propagation models, since they provide both crack topology and (from XCT) volumetric crack density as functions of cycling conditions.

### 5.3 Benchmarking Modeling Predictions Against Experimental Results

Effective model validation requires quantitative comparison between predicted and measured quantities using the same specimen geometry, loading conditions, and material properties. Yang et al. (2022) demonstrated this rigor by computing polarization curves and impedance spectra from a mechanistic delamination model and comparing them directly with electrochemical measurements on cells with controlled artificial delaminations, showing that specific crack geometries produce identifiable impedance signatures [Yang et al., Int. J. Hydrogen Energy, 47, 2022]. Jayapragasam et al. (2023) validated their crack growth rate model against multi-thousand-hour degradation data from SOEC operation, confirming that the electro-chemo-mechanical driving force (stress intensity factor as a function of current density and crack length) correctly predicts the observed degradation trajectory [Jayapragasam et al., J. Electrochem. Soc., 170, 054509, 2023].

For fracture toughness prediction, the PFM framework of Moshkelgosha & Mamivand (2020) reproduces the experimentally observed transformation toughening in 3YSZ without empirical fitting parameters, directly validating the coupled transformation-fracture constitutive theory [Moshkelgosha & Mamivand, Comput. Mater. Sci., 174, 109509, 2020]. The peridynamic study of Xiang et al. (2022) benchmarked micro-crack nucleation predictions against FIB-SEM observations of fracture surfaces in tested Ni-YSZ anode specimens, confirming that PD correctly localizes crack initiation at Ni–YSZ phase boundaries [Xiang et al., J. Peridyn. Nonlocal Model., 4, 201, 2022].

A key challenge in benchmarking remains the propagation of material property uncertainty into model predictions. Micro-compression measurements (Abaza et al., 2022) have quantified the scatter in porous YSZ fracture properties, providing a basis for probabilistic fracture modeling using Monte Carlo or polynomial chaos expansion methods. Incorporating this measured uncertainty into Weibull-based reliability assessments represents the current frontier of quantitative model validation for SOC mechanical failure.

---

## 6. Implications for Design and Longevity

### 6.1 Material Selection Guidelines from Modeling

The body of multiphysics modeling reviewed here converges on several actionable material selection guidelines:

**Electrolyte:** Replacing 8YSZ with 3YSZ in high-stress regions improves fracture toughness by 2–4× through transformation toughening, at the cost of somewhat lower ionic conductivity. For electrolyte-supported designs, the toughness gain outweighs the conductivity penalty at intermediate temperatures (600–700 °C). Ceria-doped compositions (e.g., 1.5CeO₂-4.5YO₁.₅-SZ) offer a further 30% toughness improvement without sacrificing conductivity [Khajavi et al., 2020].

**Anode composition:** Ni volume fraction in the range 50–60% represents the optimum balance between electrochemical performance and mechanical durability [MDPI Materials, 2026]. Higher Ni fractions reduce fracture toughness (lower YSZ skeletal volume) and increase creep rate, while also increasing the volumetric strain during redox cycling.

**Cathode and contact layers:** CTE-matched contact layers (e.g., CuMn spinel-forming foams) provide interfacial fracture energies approximately 8× higher than conventional perovskite pastes [DTU, ACS AEM, 2020]. GDC buffer layers between LSCF and YSZ reduce both chemical and thermal CTE mismatch, and their thickness can be optimized by minimizing the interfacial energy release rate using parametric FEM [Xie et al., 2022].

### 6.2 Structural and Geometric Design Strategies

**Corrugated cell geometry:** FEM analysis demonstrates that corrugated SOC designs reduce crack propagation rate and interfacial energy release rate during thermal cycling relative to planar designs [Xie et al., Int. J. Energy Res., 2019], by accommodating in-plane thermal strains through geometric compliance rather than interfacial stress.

**Cooling channel placement:** Incorporating cooling channels in the interconnect significantly reduces creep damage and Weibull failure probability, with lower coolant temperatures producing stronger mitigation [Luo et al., 2023]. Optimization of cooling channel geometry using RSM-guided FEM can reduce failure probability by two orders of magnitude.

**Stack geometry and flow field:** Full-stack thermal stress analysis shows that flow field configuration (co-flow, counter-flow, cross-flow) strongly influences the temperature gradient across the cell, which is the dominant driver of both thermal stress and creep damage. Co-flow configurations generally produce lower peak temperature gradients and more uniform stress distributions.

### 6.3 Operational Strategies

**Redox cycle management:** Because even a single uncontrolled reoxidation event can initiate fracture of the anode support, operational protocols that prevent fuel supply interruptions — or that provide controlled partial reoxidation at low temperatures and slow rates — are critical. Modeling shows that synchronizing thermal and oxidation strain rates (i.e., reoxidizing slowly during heating rather than isothermally) substantially reduces peak stress [Xue et al., 2023].

**Dynamic operation of SOECs:** Transient TECM modeling shows that stepped voltage control induces lower thermal stress peaks than stepped current density control in grid-coupled SOEC systems [ECM-X, 2025]. Ramp-rate limits during load change transients should be set based on the Weibull failure probability as a function of stress rate — a quantity now computationally accessible through the validated TECM models reviewed here.

**Operating temperature reduction:** The ongoing shift toward intermediate-temperature SOCs (500–700 °C) reduces thermal gradients and improves CTE compatibility between metallic and ceramic components. However, reduced temperature also decreases creep relaxation rates, which can increase peak stresses during thermal transients. The trade-off must be assessed on a system-specific basis using the modeling frameworks reviewed.

### 6.4 Industrial Scalability

Scaling from single-cell to multi-hundred-cell stacks introduces mechanical challenges that are not present at the laboratory scale: gravity-induced bending of horizontal stacks, progressive thermal gradient build-up with increasing cell count, and statistical amplification of cell-to-cell property variation. Zhang et al. (2024) demonstrated that thermal stress non-uniformity increases with cell count in the stack [Energies, 17, 2025, 2024], suggesting that stack mechanical design must account for this size effect. The PINN-surrogate approach, once validated, offers a computationally tractable route to full probabilistic stack reliability assessment — a task currently beyond the reach of direct FEM for stacks with hundreds of repeat units.

---

## 7. Summary and Outlook

### 7.1 Summary of Key Findings

This review has surveyed multiphysics modeling of mechanical behavior in solid oxide cells across five principal failure modes and six computational frameworks, with reference to experimental validation spanning micro-compression testing to operando TEM. The following conclusions emerge:

1. **Thermal expansion mismatch** remains the most pervasive mechanical driver in SOCs. TECM modeling at both cell and stack scale has matured to the point where full-size stack stress distributions can be computed with coupled CFD-FEM, enabling quantitative design optimization of flow field geometry and stack architecture.

2. **Fracture modeling** has evolved substantially beyond linear elastic fracture mechanics. Phase-field models — particularly those incorporating transformation toughening in 3YSZ and real microstructure geometries — now provide mechanistic, parameter-free predictions of crack initiation and growth. Peridynamics offers a complementary approach for microstructure-resolved thermal shock simulations. XFEM and cohesive zone models remain valuable for interface-constrained crack problems.

3. **Interfacial delamination** is directly linked to electrochemical performance degradation through validated electro-chemo-mechanical models that connect current density, oxygen partial pressure, and crack driving force. The energy release rate framework provides a quantitative basis for contact-layer material selection.

4. **Creep** over 40,000–100,000 hours is now tractable through FEM with Norton's law and Weibull reliability analysis. Material composition (Ni volume fraction 50–60%) and thermal management (cooling channels) are the primary design levers for creep life extension.

5. **Electro-chemo-mechanical coupling** is essential for both SOFC and SOEC mechanical prediction, since ion migration and chemical expansion add eigenstrain contributions comparable in magnitude to thermal strains under some operating conditions. Full TECM frameworks are now available and validated for button cells, half-cells, and full stacks.

6. **Machine learning and PINN** for SOC mechanical failure prediction remain at an early stage. The methodological infrastructure from ceramic fracture ML (StressNet) and PINN phase-field fracture is ready for transfer to SOC-specific applications, but experimentally validated, SOC-trained models do not yet exist in the open literature. This represents the most significant gap and the greatest opportunity for near-term progress.

### 7.2 Outlook and Future Directions

Looking forward, four directions stand out as particularly impactful:

**Microstructure-to-cell multiscale integration:** Emerging frameworks (e.g., the JMPS 2024 unified multiphysics approach) that bridge FIB-SEM reconstructed microstructures with cell-level mechanical response will enable composition-specific, microstructure-aware predictions of mechanical durability — closing the gap between materials synthesis and system-level reliability.

**PINN surrogates for design optimization:** Once validated TECM and PFM models exist for a given cell architecture, training PINN surrogates on the resulting simulation datasets will enable real-time parametric optimization over composition, geometry, and operating conditions — a critical capability for industrial design cycles.

**In-situ multi-modal characterization:** Combining operando X-ray stress monitoring (Yamaguchi et al., 2025) with operando electrochemical impedance spectroscopy and post-mortem FIB-SEM tomography within a single experimental protocol will provide the spatially and temporally resolved validation data needed to discriminate between competing model formulations.

**Probabilistic failure prediction:** Integrating measured material property scatter (from micro-compression, double-torsion, and ring-on-ring datasets) into Weibull-based probabilistic FEM frameworks will enable failure probability distributions rather than single deterministic predictions — the appropriate output for industrial reliability assessment and lifetime warranty specification.

The convergence of increasingly capable multiphysics computational frameworks with advancing experimental characterization techniques is positioning the SOC mechanical modeling community to move from post-mortem failure analysis to predictive design — a transition that will be essential for achieving the 100,000-hour lifetime targets required for cost-competitive large-scale energy storage and generation.

---

## References

1. Zhang, X., Wu, M., Xiao, L., Wang, H., Liu, Y., Ou, D., & Yuan, J. (2024). Thermal stress in full-size solid oxide fuel cell stacks by multi-physics modeling. *Energies*, 17(9), 2025. https://doi.org/10.3390/en17092025

2. Wang, C., Yang, J.J., Huang, W., Zhang, T., Yan, D., Pu, J., et al. (2018). Numerical simulation and analysis of thermal stress distributions for a planar solid oxide fuel cell stack with external manifold structure. *International Journal of Hydrogen Energy*, 43, 20900–20910. https://doi.org/10.1016/j.ijhydene.2018.09.071

3. Wu, Y., et al. (2021). Thermo-electro-chemo-mechanical modeling of solid oxide fuel cell for stress and failure evolution during duty cycle. *Journal of The Electrochemical Society*, 168(4). https://doi.org/10.1149/1945-7111/abf4ef

4. Cai, W., Zheng, Q., Yuan, J., Yu, W., Yin, Z., Wu, Y., & Zhang, Z. (2023). Thermo-electro-chemo-mechanical coupled modeling of solid oxide fuel cell with LSCF-GDC composite cathode. *International Journal of Molecular Sciences*, 24(4), 4137. https://doi.org/10.3390/ijms24044137

5. Acta Mechanica (2025). Modelling and simulation of the electro-chemo-thermo-mechanical behaviour of solid oxide fuel cells considering creep. https://doi.org/10.1007/s00707-025-04334-5

6. Energy Conversion and Management: X (2025). Transient thermomechanical response of an electrolyte supported planar solid oxide electrolysis cell under dynamic loading conditions. https://doi.org/10.1016/j.ecmx.2025.100862

7. Pecanac, G., Wei, J., & Malzbender, J. (2016). Fracture toughness of solid oxide fuel cell anode substrates determined by a double-torsion technique. *Journal of Power Sources*, 327, 629–637. https://doi.org/10.1016/j.jpowsour.2016.07.103

8. Khajavi, P., Hendriksen, P.V., Chevalier, J., Gremillard, L., & Frandsen, H.L. (2020). Improving the fracture toughness of stabilized zirconia-based solid oxide cells fuel electrode supports. *Journal of the European Ceramic Society*, 40(15), 5670–5682. https://doi.org/10.1016/j.jeurceramsoc.2020.05.070

9. Abaza, A., Laurencin, J., Nakajo, A., Hubert, M., David, T., Monaco, F., Lenser, C., & Meille, S. (2022). Fracture properties of porous yttria-stabilized zirconia under micro-compression testing. *Journal of the European Ceramic Society*, 42(4), 1656–1669. https://doi.org/10.1016/j.jeurceramsoc.2021.11.051

10. DTU Energy (2020). Interface fracture energy of contact layers in a solid oxide cell stack. *ACS Applied Energy Materials*, 3(3), 2372–2385. https://doi.org/10.1021/acsaem.9b02026

11. Xie, J., Hao, W., & Wang, F. (2022). Parametric study on interfacial crack propagation in solid oxide fuel cell based on electrode material. *International Journal of Hydrogen Energy*, 47, 7975–7989. https://doi.org/10.1016/j.ijhydene.2021.12.xxx

12. Jayapragasam, P., Wen, Y., Cook, K., Wrubel, J.A., Ma, Z., Huang, K., & Jin, X. (2023). Crack growth rate at oxygen electrode/electrolyte interface in solid oxide electrolysis cells predicted by experiment coupled multiphysics modeling. *Journal of The Electrochemical Society*, 170, 054509. https://doi.org/10.1149/1945-7111/acd4f1

13. Yang, T., Fan, Y., Liu, J., Finklea, H., Lee, S., Guan, B., Abernathy, H.W., Kalapos, T.L., & Hackett, G.A. (2022). Multiphysics modeling of SOFC performance degradation caused by interface delamination and active layer cracking. *International Journal of Hydrogen Energy*, 47(97). https://doi.org/10.1016/j.ijhydene.2022.09.194

14. Kurushina, V., Prathuru, A.K., Ajithkumar, S., Hossain, M., Cai, Q., Horri, B.A., & Faisal, N.H. (2025). Cohesive zone model for the thermomechanical deformation of a high temperature tubular solid oxide electrolysis cell. *Engineering Fracture Mechanics*. https://doi.org/10.1016/j.engfracmech.2025

15. Shao, Q., Bouhala, L., Younes, A., et al. (2014). Influence of heat transfer and fluid flow on crack growth in multilayered porous/dense materials using XFEM. *International Journal of Fracture*, 185, 155–169. https://doi.org/10.1007/s10704-013-9916-2

16. Jiang, W., Spencer, B.W., & Dolbow, J.E. (2019). Ceramic nuclear fuel fracture modeling with the extended finite element method. *Engineering Fracture Mechanics*, 223, 106713. https://doi.org/10.1016/j.engfracmech.2019.106713

17. Giovanardi, B., Scotti, A., & Formaggia, L. (2017). A hybrid XFEM–phase field (Xfield) method for crack propagation in brittle elastic materials. *Computer Methods in Applied Mechanics and Engineering*, 320, 396–420. https://doi.org/10.1016/j.cma.2017.03.039

18. Xue, F., Lei, Y., Cheng, T.-L., Epting, W.K., Hackett, G., Abernathy, H., & Wen, Y.-H. (2023). Phase-field modeling of crack growth and mitigation in solid oxide cells. *International Journal of Hydrogen Energy*, 47(26). https://doi.org/10.1016/j.ijhydene.2022.12.042

19. Moshkelgosha, E., & Mamivand, M. (2020). Phase field modeling of crack propagation in shape memory ceramics — Application to zirconia. *Computational Materials Science*, 174, 109509. https://doi.org/10.1016/j.commatsci.2019.109509

20. Xie, J., Hao, W., & Wang, F. (2019). Crack propagation of planar and corrugated solid oxide fuel cells during cooling process. *International Journal of Energy Research*, 43(7), 3020–3027. https://doi.org/10.1002/er.4369

21. Journal of the Mechanics and Physics of Solids (2024). Quantifying the mechanical degradation of solid oxide cells based on 3D reconstructions of the real microstructure using a unified multiphysics coupling numerical framework. https://doi.org/10.1016/j.jmps.2024.105607

22. ACS Sustainable Chemistry & Engineering (2025). Coupled electrochemical–mechanical degradation mechanisms of solid oxide fuel cells under redox conditions. https://doi.org/10.1021/acssuschemeng.5c09182

23. Wang, Y., Jiang, W., Luo, Y., Song, M., & Tu, S.-T. (2022). High temperature creep strength design and optimization of solid oxide fuel cell. *International Journal of Hydrogen Energy*, 47, 21450–21461. https://doi.org/10.1016/j.ijhydene.2022.04.261

24. Luo, Y., Chen, X., Liu, R., & Jiang, W. (2023). Effects of a cooling channel on the creep damage and failure probability of planar solid oxide fuel cells. *Frontiers in Materials*, 10, 1238559. https://doi.org/10.3389/fmats.2023.1238559

25. Shang, Y., et al. (2018). Modeling cooperative creep reoxidation effect on the mechanical stability of anode-supported solid oxide fuel cell. *International Journal of Energy Research*. https://doi.org/10.1002/er.4245

26. Materials (Basel) (2026). Material composition design for long-term stability of solid oxide fuel cell based on creep damage and failure probability. 19(4), 733. https://doi.org/10.3390/ma19040733

27. Wang, H., Oterkus, E., Celik, S., & Toros, S. (2017). Thermomechanical analysis of porous solid oxide fuel cell by using peridynamics. *AIMS Energy*, 5(4), 585–600. https://doi.org/10.3934/energy.2017.4.585

28. Xiang, Y., Dong, Z., Zhong, Z., et al. (2022). Simulation of fracture formation in solid oxide fuel cell anode using peridynamic modeling method. *Journal of Peridynamics and Nonlocal Modeling*, 4, 201–214. https://doi.org/10.1007/s42102-021-00077-8

29. Journal of Power Sources (2022). An adaptive thermo-mechanical peridynamic model for crack analysis in anode-supported solid oxide fuel cell. https://doi.org/10.1016/j.jpowsour.2022.231775

30. Giannakeas, I.N., Papathanasiou, T.K., & Bahai, H. (2018). Simulation of thermal shock cracking in ceramics using bond-based peridynamics and FEM. *Journal of the European Ceramic Society*, 38(8), 3037–3048. https://doi.org/10.1016/j.jeurceramsoc.2017.12.039

31. Journal of Power Sources (2024). Application and development of the Lattice Boltzmann modeling in pore-scale electrodes of solid oxide fuel cells. https://doi.org/10.1016/j.jpowsour.2024.234015

32. Zhao, H., Zhou, J., Zong, Z., Li, R., Li, H., Qiu, Z., Li, C., & Zhou, J. (2024). Three-dimensional reconstruction and optimization of porous fuel electrode in reversible solid oxide cells based on the Lattice Boltzmann method. *Electrochimica Acta*, 143562. https://doi.org/10.1016/j.electacta.2023.143562

33. Liu, S., Liu, Z., Zhang, S., & Wu, H. (2024). Lattice Boltzmann simulation study of anode degradation in solid oxide fuel cells during the initial aging process. *International Journal of Minerals, Metallurgy and Materials*, 31(2), 405–411. https://doi.org/10.1007/s12613-023-2692-8

34. Wang, Y., Oyen, D., Guo, W., Mehta, A., Scott, C.B., Panda, N., Fernández-Godino, M.G., Srinivasan, G., & Yue, X. (2021). StressNet — Deep learning to predict stress with fracture propagation in brittle materials. *npj Materials Degradation*, 5, 6. https://doi.org/10.1038/s41529-021-00151-y

35. Engineering Fracture Mechanics (2022). Machine learning-based prediction of fracture toughness and path in the presence of micro-defects. https://doi.org/10.1016/j.engfracmech.2022.108900

36. Goswami, S., Anitescu, C., Chakraborty, S., & Rabczuk, T. (2020). Transfer learning enhanced physics informed neural network for phase-field modeling of fracture. *Theoretical and Applied Fracture Mechanics*, 106, 102447. https://doi.org/10.1016/j.tafmec.2019.102447

37. Manav, M., Molinaro, R., Mishra, S., & De Lorenzis, L. (2024). Phase-field modeling of fracture with physics-informed deep learning. *Computer Methods in Applied Mechanics and Engineering*, 429, 117104. https://doi.org/10.1016/j.cma.2024.117104

38. Frontiers in Physics (2023). Physics informed neural networks for phase field fracture modeling enhanced by length-scale decoupling degradation functions. 11, 1152811. https://doi.org/10.3389/fphy.2023.1152811

39. Padinjarethil, A.K., Pollok, S., & Hagen, A. (2021). Degradation studies using machine learning on novel solid oxide cell database. *Fuel Cells*, 21(6), 566–576. https://doi.org/10.1002/fuce.202100097

40. Journal of Materials Chemistry A (2022). Machine-learning-assisted prediction of long-term performance degradation on solid oxide fuel cell cathodes induced by chromium poisoning. 10, 23683–23690. https://doi.org/10.1039/D2TA03944C

41. Makki Abadi, M., Rashidi, M.M., et al. (2025). Machine learning for the optimization and performance prediction of solid oxide electrolysis cells: A review. *Processes*, 13(3), 875. https://doi.org/10.3390/pr13030875

42. Energies (2023). Performance and thermal stress evaluation of full-scale SOEC stack using multi-physics modeling method. 16(23), 7720. https://doi.org/10.3390/en16237720

43. Yamaguchi, M., Komaya, T., Ruhma, Z., Watanabe, S., Yashiro, K., Kumada, K., Sato, K., Hashida, T., Oikawa, I., Takamura, H., Budiman, R.A., & Kawada, T. (2025). High-temperature in situ stress monitoring of a co-fired electrolyte for metal-supported solid oxide cells. *Journal of Power Sources*, 235892. https://doi.org/10.1016/j.jpowsour.2024.235892

44. Ceramics International (2018). Mechanical characterization of SOFC/SOEC cells. 44(9). https://doi.org/10.1016/j.ceramint.2018.03.041

45. Jeangros, Q., Bugnet, M., Epicier, T., Frantz, C., Diethelm, S., et al. (2023). Operando analysis of a solid oxide fuel cell by environmental transmission electron microscopy. *Nature Communications*, 14, 7959. https://doi.org/10.1038/s41467-023-43683-4

46. Ceramics International (2025). Relation between interfacial adhesion and hardness of electrode materials in electrolyte supported solid oxide cells. https://doi.org/10.1016/j.ceramint.2025

47. Acta Mechanica (2025). 3D and time-dependent simulation of a planar solid oxide fuel cell: bridging microstructure and multiphysics phenomena. https://doi.org/10.1007/s00707-025-04456-w

48. International Journal of Mechanical Sciences (2018). Shape deformation analysis of anode-supported solid oxide fuel cell by electro-chemo-mechanical simulation. https://doi.org/10.1016/j.ijmecsci.2017.11.022

---

*Word count: approximately 10,200 words (excluding references)*
