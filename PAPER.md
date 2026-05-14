# A Reproducible Computational Testbed for the Helix–Light–Vortex (HLV) G-Lattice

**6D-to-3D quasicrystalline construction, Laplacian recovery, spectral testing, null models, and vortex stability**

**Marcel Krüger**¹ · **Don Michael Feeney Jr.**²

¹ Independent Researcher, Meiningen, Germany  
² Independent Researcher, Pennsylvania, USA

*Draft: May 2026*

---

## Abstract

The Helix–Light–Vortex (HLV) framework is a conservative effective-field research program in which a quasicrystalline G-lattice is treated as a candidate geometric substrate to be tested rather than assumed. In its present formulation, HLV combines a six-dimensional cut-and-project construction with a triadic phase–memory temporal structure entering low-energy dynamics through controlled effective-field deformations. A central weakness of the program at its present stage is not the absence of formal ingredients, but the lack of a reproducible numerical testbed capable of evaluating whether its core geometric objects behave as viable discretizations of continuum field theory.

This paper addresses that gap by formulating a computational framework for constructing a finite 6D-to-3D quasicrystalline G-lattice, building its neighbor graph, defining a weighted graph Laplacian, testing continuum recovery, comparing against matched null models, and simulating topological vortex configurations on the resulting background.

The simulation layer is deliberately framed as a **falsification-oriented testbed** rather than as evidence that physical spacetime is quasicrystalline. The key tests are:

1. Whether the graph Laplacian approximates the continuum Laplacian for smooth probe functions
2. Whether the low-energy spectral sector is stable under sampling radius, window deformation, and neighbor-rule variation
3. Whether quasicrystal-specific signatures survive comparison against cubic, random, jittered, periodic-approximant, and phase-shuffled null lattices
4. Whether vortex winding, energy localization, and defect-assisted nucleation can be reproduced on the G-lattice without inserting the expected result by construction

No claim is made that HLV is proven, that the Standard Model is derived, or that the simulations establish fundamental spacetime microstructure.

**Keywords:** Helix–Light–Vortex framework · quasicrystalline G-lattice · cut-and-project geometry · graph Laplacian · spectral analysis · continuum recovery · null models · vortex stability · effective field theory · falsifiability · reproducible simulation

---

## Contents

1. [Introduction](#1-introduction)
2. [Relation to Prior HLV Work](#2-relation-to-prior-hlv-work)
3. [Theoretical Background](#3-theoretical-background)
4. [Graphical Overview](#4-graphical-overview)
5. [Numerical Construction of the G-Lattice](#5-numerical-construction-of-the-g-lattice)
6. [Neighbor Graph and Laplacian Construction](#6-neighbor-graph-and-laplacian-construction)
7. [Continuum-Recovery Tests](#7-continuum-recovery-tests)
8. [Spectral Tests](#8-spectral-tests)
9. [Null Models](#9-null-models)
10. [Vortex Simulation on the G-Lattice](#10-vortex-simulation-on-the-g-lattice)
11. [Projection-Mismatch Defects and Vortex Nucleation](#11-projection-mismatch-defects-and-vortex-nucleation)
12. [Planned Repository Structure](#12-planned-repository-structure)
13. [Pre-Registered Analysis Plan](#13-pre-registered-analysis-plan)
14. [Computational Results](#14-computational-results)
15. [Discussion](#15-discussion)
16. [Conclusion](#16-conclusion)

---

## 1. Introduction

Discrete and emergent-geometry approaches to field theory are scientifically useful only if their basic geometric objects can be stated precisely, implemented reproducibly, and tested against continuum recovery limits. The Helix–Light–Vortex (HLV) framework is developed in this spirit. It combines a higher-dimensional cut-and-project geometry with a triadic phase–memory time structure and controlled effective-field deformations. Its compact formulation is intentionally conservative: HLV is not treated here as a completed fundamental theory, but as an effective geometric research program whose core sectors must either recover known physics in appropriate limits or fail under explicit numerical tests.

The present paper addresses the most concrete part of this program: the proposed quasicrystalline G-lattice. The mathematical construction is direct. A six-dimensional integer lattice is projected into a three-dimensional physical sector using a complementary internal space and an acceptance window. The resulting point set is expected to behave as a Delone–Meyer-type quasicrystalline structure with long-range aperiodic order. Scalar, spinor, or gauge fields may then be sampled on this graph, and a graph Laplacian may serve as a discrete approximation to the continuum Laplacian in a suitable recovery limit.

This paper does not attempt to prove that physical spacetime is quasicrystalline. Instead, it asks a narrower and falsifiable question:

> *Can the HLV 6D-to-3D G-lattice be constructed as a reproducible numerical object whose Laplacian, spectrum, null-model behavior, and vortex dynamics satisfy the minimum requirements of an effective field-theory substrate?*

This is a necessary but not sufficient condition for the broader HLV program. If the G-lattice cannot be generated robustly, if its Laplacian does not recover the continuum Laplacian for smooth probe functions, or if its apparent signatures are reproduced by generic null lattices, then the G-lattice sector is weakened or falsified. Conversely, if the construction survives controlled numerical tests, it becomes a legitimate computational scaffold for more detailed HLV effective-field and analog-simulation studies.

### 1.1 Reviewer-Oriented Scope

A likely reviewer objection is that quasicrystals, graph Laplacians, vortices, and topological defects are already known. This is correct. Novelty is not claimed for these ingredients individually. The contribution is the conservative numerical integration of these ingredients into the HLV-specific chain:

```
ℤ⁶  ──→  G_φ ⊂ ℝ³  ──→  Δ_G  ──→  continuum recovery / spectral tests / vortex stability / null models
```

The paper is therefore best read as a **reproducibility and falsification study** of the HLV G-lattice sector, not as a final unification proof.

---

## 2. Relation to Prior HLV Work

The present manuscript is a computational companion to the compact HLV core formulation and mathematical foundation [1]. Earlier HLV work introduced:

- The triadic spiral-time variable **Ψ**(t) = (t, φ(t), χ(t))
- A real kinetic prefactor A(t) = 1 + ε(t)
- A quasicrystalline G-lattice as an effective substrate
- Recovery limits in which standard QFT and GR are restored

The mathematical foundation also formulates a G-lattice Laplacian and states the continuum requirement Δ_G f → ∇²f in the appropriate limit. The present paper turns this formal requirement into a reproducible numerical protocol.

A related application of the triadic spiral-time operator and the ΔΦ instability functional was developed in an information-theoretic neurodynamic context [2]. That work is cited here only as background for the operator notation and the broader HLV program. It is not used as evidence for the G-lattice, quasicrystalline spacetime, or any of the spectral claims tested in the present manuscript.

The present work also connects to the HLV vortex-sector manuscript, where integer angular momentum and effective topological charge are modeled through vortex configurations on a quasicrystalline background. In that context, the central field ansatz is the standard topological vortex:

$$Ψ(r, θ) = f(r)\,e^{inθ}, \quad n ∈ ℤ,$$

with canonical angular momentum L_z = nℏ. The present paper does not derive half-integer fermion spin and does not attempt a Standard Model particle derivation.

> **Non-claim 1** *(No proof from simulation alone).* Even successful G-lattice simulations would not prove HLV as a fundamental theory. They would only establish that the proposed geometric substrate is a reproducible and mathematically usable effective object.

---

## 3. Theoretical Background

### 3.1 Cut-and-Project Geometry

For the modern mathematical framework of aperiodic order, including Delone sets, Meyer sets, model sets, and cut-and-project schemes, we refer to the standard monograph by Baake and Grimm [3].

Let **Λ**₆ = ℤ⁶ ⊂ ℝ⁶ be a six-dimensional integer lattice. Assume a decomposition:

$$ℝ^6 = E_∥ ⊕ E_⊥, \quad E_∥ ≅ ℝ^3, \quad E_⊥ ≅ ℝ^3,$$

with projections π_∥ : ℝ⁶ → E_∥ and π_⊥ : ℝ⁶ → E_⊥. Given a compact acceptance window W_φ ⊂ E_⊥, define the physical point set:

$$G_φ = \bigl\{\, π_∥(x) : x ∈ ℤ^6,\; π_⊥(x) ∈ W_φ \,\bigr\}$$

This is the finite numerical object to be constructed. In the ideal mathematical setting, such constructions yield model sets with long-range order and nonperiodicity when the projection subspaces are irrationally oriented and the window satisfies standard regularity assumptions.

### 3.2 Triadic Time Enters Only as a Controlled Deformation

The HLV time variable is written as:

$$Ψ(t) = (t,\; φ(t),\; χ(t)),$$

or as hypercomplex bookkeeping:

$$ψ(t) = t + i\,φ(t) + j\,χ(t), \quad i^2 = j^2 = -1, \quad ij = -ji.$$

For the present numerical paper, only the real kinetic prefactor is used:

$$A(t) = 1 + ε(t), \quad |ε(t)| ≪ 1, \quad A(t) > 0.$$

This restriction is deliberate. The G-lattice simulation does not require an ontological claim about time. It only requires that any time-dependent deformation remains a positive perturbation of the standard kinetic sector.

### 3.3 Weighted Graph Laplacian

Let G = (V, E) be the finite graph obtained from G_φ. For a scalar function f : V → ℝ, define:

$$(Δ_G f)_i = \sum_{j ∈ \mathcal{N}(i)} w_{ij}(f_j - f_i),$$

where 𝒩(i) is the neighbor set of node i and w_{ij} > 0 are symmetric weights. The weights are chosen to satisfy a discrete second-moment condition as closely as possible:

$$\sum_{j ∈ \mathcal{N}(i)} w_{ij}(x_j - x_i)(x_j - x_i)^T ≈ c_i\, I_3.$$

This condition prevents the Laplacian from becoming an arbitrary graph operator and provides the numerical target for continuum recovery.

### 3.4 Continuum Recovery Requirement

For smooth probe functions f sampled on G_φ, the essential requirement is:

$$Δ_G f \;⟶\; ∇^2 f$$

in a controlled limit of increasing sampling density and decreasing effective spacing. In numerical form, this becomes an error-scaling test:

$$E_Δ(h) = \frac{\|Δ_G f - ∇^2 f\|_{2,V_h}}{\|∇^2 f\|_{2,V_h} + η},$$

where h is an effective spacing scale and η > 0 prevents division by zero.

---

## 4. Graphical Overview

### Figure 1 — Computational Pipeline

```
╔══════════════════════════════════════════════════════════════════╗
║            6D parent lattice  ℤ⁶                                ║
╚══════════════════╤═══════════════════════════╤═══════════════════╝
                   │ π_∥                       │ π_⊥
                   ▼                           ▼
          ┌────────────────┐         ┌──────────────────┐
          │  E_∥ ≅ ℝ³      │         │  E_⊥ ≅ ℝ³        │
          └───────┬────────┘         └────────┬─────────┘
                  │                           │
                  │         selection         │
                  │ ◄─────────────────────────┤
                  │                    acceptance window W
                  ▼
          ┌────────────────┐
          │  G-lattice G_φ │
          └───────┬────────┘
                  │
                  ▼
    ┌─────────────────────────┐
    │  neighbor graph + Δ_G   │
    └──────────┬──────────────┘
               │
       ┌───────┴────────┐
       ▼                ▼
 ┌───────────┐   ┌─────────────┐
 │ recovery  │   │ vortex      │
 │ + spectra │   │ tests       │
 └───────────┘   └─────────────┘
```

*The 6D parent lattice is projected into physical and internal spaces. The acceptance window selects a finite 3D G-lattice. A neighbor graph and weighted Laplacian are constructed, followed by continuum-recovery tests, spectral tests, null-model comparisons, and vortex-stability simulations.*

---

### Figure 2 — Schematic HLV G-Lattice Analogy

```
  6D hypercubic parent lattice  ──cut-and-project──▶  3D schematic HLV G-lattice
  G = { π_∥(p) | p ∈ ℤ⁶, π_⊥(p) ∈ W }

  ℤ⁶ parent lattice                  Projected quasiperiodic network
  ┌──────────────┐                   ╭─────────────────────────────────╮
  │ · · · · · · │  window W          │  ◎──◉     ◉                     │
  │ · · · · · · │ ┌────────┐        │ ╱    ╲   ╱ ╲                    │  ← weighted
  │ · · ·[W]· · │─│ accept │──▶     │◉      ◉─◉   ◉──◎               │    connectivity
  │ · · · · · · │ └────────┘        │ ╲    ╱   ╲ ╱                    │
  │ · · · · · · │                   │  ◎──◉     ◉                     │
  └──────────────┘                  │     ╲   ╱                        │
   internal E_⊥  physical E_∥       │      ◉─◎      dodecagonal        │
                                    │             local order  ⬡        │
  Legend                            ╰─────────────────────────────────╯
  ◎  Projected host nodes                         phason-like
  ◉  Phase-shifted boundary nodes              geometric frustration
  ───  Variable connectivity
  ╱╲   Hierarchical connectivity          phase-like offset: ░▒▓█▓▒░
```

*Schematic visual analogy of the HLV G-lattice construction. A six-dimensional hypercubic parent lattice ℤ⁶ is projected into an effective physical sector E_∥, while an internal sector E_⊥ and an acceptance window W determine which projected nodes are retained. The network illustration indicates weighted quasiperiodic connectivity, phase-like internal offsets, and possible local dodecagonal/icosahedral motifs. The figure is schematic and is not presented as a numerically generated physical spacetime lattice or as evidence for HLV.*

---

## 5. Numerical Construction of the G-Lattice

### 5.1 Finite Sampling

The infinite lattice ℤ⁶ is truncated by a radius R₆:

$$Λ_6(R_6) = \{n ∈ ℤ^6 : \|n\|_∞ ≤ R_6\}.$$

For each n ∈ Λ₆(R₆), compute:

$$x_n = π_∥(n), \quad y_n = π_⊥(n).$$

The finite G-lattice is then:

$$G_R = \{x_n : y_n ∈ W\}.$$

Boundary effects are controlled by evaluating observables only on an interior subset G^int_R, excluding nodes within a distance d_edge of the finite-sample boundary.

### 5.2 Projection Matrices

A practical implementation may use orthonormal projection matrices P_∥, P_⊥ ∈ ℝ^{3×6} satisfying:

$$P_∥ P_∥^T = I_3, \quad P_⊥ P_⊥^T = I_3, \quad P_∥ P_⊥^T = 0.$$

The irrational orientation should be fixed once and version-controlled.

> **Protocol 1** *(G-lattice generation).* The repository must implement the following deterministic procedure:
> 1. Fix R₆, projection matrices, and acceptance window parameters
> 2. Enumerate Λ₆(R₆)
> 3. Compute x_n = P_∥ n, y_n = P_⊥ n
> 4. Keep nodes satisfying y_n ∈ W
> 5. Deduplicate physical points within tolerance τ_dup
> 6. Export node coordinates, parent indices, internal coordinates, and metadata

### 5.3 Acceptance Window Choices

The primary window is a compact approximately icosahedral/dodecahedral window. For robustness, the simulation must repeat all core results under at least three windows:

$$W ∈ \{W_{\text{ball}},\; W_{\text{dodeca}},\; W_{\text{ellipsoid}}\}.$$

If a signature appears only under a highly tuned window and vanishes for nearby windows, it must not be claimed as a robust HLV effect.

---

## 6. Neighbor Graph and Laplacian Construction

### 6.1 Neighbor Rules

At least three rules are pre-declared:

1. **k-nearest neighbors:** connect each node to its k nearest physical neighbors
2. **Radius graph:** connect nodes with ‖x_i − x_j‖ ≤ r_c
3. **Parent-edge projection:** connect projected nodes whose parent indices differ by a basis vector or selected short vector in ℤ⁶

The parent-edge rule is most faithful to the cut-and-project construction. The other rules are included as sensitivity checks.

### 6.2 Laplacian Normalization

For a graph with weights w_{ij}, define the matrix:

$$L_{ij} = \begin{cases} -w_{ij}, & i ≠ j,\; j ∈ \mathcal{N}(i) \\ \displaystyle\sum_{ℓ ∈ \mathcal{N}(i)} w_{iℓ}, & i = j \\ 0, & \text{otherwise} \end{cases}$$

Then Δ_G = −L. Both combinatorial and normalized Laplacians should be reported, but continuum recovery should be tested primarily with the weighted non-normalized Laplacian.

> **Criterion 1** *(Laplacian admissibility).* The G-lattice Laplacian is considered admissible only if all three conditions hold:
> 1. w_{ij} = w_{ji} > 0 and the graph is connected on the interior domain
> 2. The second-moment anisotropy score $A_i = \dfrac{\|M_i - \frac{\text{tr}\,M_i}{3}I_3\|_F}{\|M_i\|_F}$, where $M_i = \sum_{j ∈ \mathcal{N}(i)} w_{ij}(x_j - x_i)(x_j - x_i)^T$, remains bounded and decreases under coarse-graining
> 3. Smooth-probe Laplacian errors decrease with increasing sampling density

---

## 7. Continuum-Recovery Tests

### 7.1 Probe Functions

The following probe functions are pre-declared:

| Probe | Expression | Analytic ∇²f |
|-------|-----------|--------------|
| f₁ | x² + y² + z² | 6 |
| f₂ | sin(kx) | −k² sin(kx) |
| f₃ | exp[−α(x² + y² + z²)] | (4α²r² − 6α) e^{−αr²} |

These functions test polynomial, oscillatory, and localized smooth behavior.

### 7.2 Error Scaling

For each probe f_m, compute E^{(m)}_Δ(h). The effective spacing h may be estimated by the median nearest-neighbor distance on the interior graph.

> **Criterion 2** *(Recovery pass condition).* A minimal recovery pass requires:
> $$E_Δ(h) \downarrow \text{ as } h \downarrow,$$
> and the G-lattice error must be comparable to or better than the matched random geometric graph for low-frequency probes. If the error does not decrease with refinement, the numerical G-lattice sector **fails** the recovery test.

---

## 8. Spectral Tests

### 8.1 Eigenvalue Problem

Compute the eigenvalues of the positive graph Laplacian:

$$L u_n = λ_n u_n, \quad 0 = λ_0 ≤ λ_1 ≤ λ_2 ≤ \cdots$$

The low-energy part of the spectrum should behave stably under changes in R₆, window thickness, and neighbor rule. The aim is not to reproduce a continuum spectrum exactly, but to determine whether the G-lattice has a coherent low-energy spectral sector.

### 8.2 Spectral Density and Anisotropy

Define the empirical spectral density:

$$ρ(λ) = \frac{1}{N} \sum_n δ_σ(λ - λ_n),$$

where δ_σ is a Gaussian smoothing kernel.

> **Criterion 3** *(Spectral robustness).* A G-lattice spectral signature is considered robust only if it persists across:
> 1. Sampling radius variation
> 2. Small window deformations
> 3. At least two neighbor rules
> 4. Comparison against null lattices with matched node count and degree distribution

---

## 9. Null Models

Null models are essential. Without them, any apparent structure in a quasicrystal simulation could be mistaken for evidence when it is merely a generic property of graphs.

| Null Model | Construction | Purpose |
|-----------|--------------|---------|
| **Cubic lattice** | Regular 3D grid with matched node density | Tests whether effects are ordinary discretization artifacts |
| **Random geometric graph** | Random points with radius/kNN graph | Tests generic graph connectivity artifacts |
| **Jittered cubic lattice** | Cubic nodes plus small random displacements | Tests sensitivity to disorder without quasiperiodicity |
| **Phase-shuffled G-lattice** | Preserve coordinates, randomize internal labels or phases | Tests whether phase/topology signatures require HLV structure |
| **Periodic approximant** | Rational approximation to projection slope | Tests dependence on true aperiodicity |

> **A result is not HLV-specific unless it survives comparison to these nulls.**

---

## 10. Vortex Simulation on the G-Lattice

### 10.1 Discrete Complex Field

Let Ψ_i = ρ_i e^{iθ_i} be a complex scalar field on graph nodes. Use the energy functional:

$$E[Ψ] = \frac{1}{2} \sum_{(i,j) ∈ E} w_{ij} |Ψ_i - Ψ_j|^2 + \sum_i V(|Ψ_i|),$$

with Mexican-hat potential:

$$V(ρ) = \frac{λ}{4}(ρ^2 - ρ_0^2)^2.$$

```
     V(ρ)
      │
      │    ╭─╮        ╭─╮
      │   ╱   ╲      ╱   ╲
      │──╱─────╲────╱─────╲──▶ ρ
      │         ╲  ╱
      │          ╲╱
      │        ─ ρ₀        ← symmetry-breaking minimum
      │
  Mexican-hat (wine-bottle) potential  V(ρ) = λ/4 · (ρ² − ρ₀²)²
```

Initialize a vortex around axis n̂ and center x₀ by:

$$θ_i = n\; \text{atan2}\bigl((x_i - x_0)·e_2,\;(x_i - x_0)·e_1\bigr), \quad n ∈ ℤ,$$

where e₁, e₂ span the plane perpendicular to n̂. Relax ρ_i and optionally θ_i under gradient descent while monitoring winding preservation.

### 10.2 Discrete Winding Number

For a closed graph loop C = (i₁, i₂, …, i_m, i₁), define:

$$N_C = \frac{1}{2π} \sum_{ℓ=1}^{m} \text{wrap}_{(-π,π]}(θ_{i_{ℓ+1}} - θ_{i_ℓ}).$$

A vortex is numerically stable only if N_C remains close to an integer under relaxation and perturbation.

```
  n = +1 vortex phase field          n = −1 anti-vortex
  ─────────────────────              ─────────────────────
          ↑                                   ↓
       ↖  │  ↗                            ↙  │  ↘
    ←  ─ (●) ─  →                   →  ─ (●) ─  ←
       ↙  │  ↘                            ↖  │  ↗
          ↓                                   ↑
     Phase winds +2π                  Phase winds −2π
     around core                      around core
```

> **Non-claim 2** *(No fermion spin derivation).* The vortex simulation tests integer winding sectors n ∈ ℤ and canonical angular momentum analogues. It does not derive half-integer fermion spin or the Standard Model spinor spectrum.

> **Non-claim 3** *(No QED derivation).* The circulation current associated with the vortex phase is an effective topological analogue. It is not a derivation of physical electric charge or quantum electrodynamics.

---

## 11. Projection-Mismatch Defects and Vortex Nucleation

A distinctive HLV-sector claim is that projection-mismatch defects in the cut-and-project geometry can act as nucleation sites for vortex excitations. This must be tested rather than assumed.

### 11.1 Defect Construction

Introduce a local shift of the internal acceptance window:

$$W \;→\; W + δW(x),$$

where δW(x) changes across a plane or narrow interface.

```
  Projection-Mismatch Defect (schematic)
  ═══════════════════════════════════════════════════════

  Region A (W)              │  Region B (W + δW)
  ──────────────────────────┼───────────────────────────
   · · · · ·               │         · · · · ·
   · ◎ ◉ ◎ ·               │         · ◉ ◎ ◉ ·
   · ◉   ◎ ·    ← mismatch │ edge →  · ◎   ◉ ·
   · ◎ ◉ ◎ ·               │         · ◉ ◎ ◎ ·
   · · · · ·               │         · · · · ·

         ↑ vortex energy   J_vort   localizes here ↑
                              │
                       ╔══════╧══════╗
                       ║  core  (●)  ║
                       ║   J_µ ↺     ║
                       ╚═════════════╝
  The simulation must determine whether vortex energy density
  and phase gradients statistically localize near mismatch
  edges more strongly than in matched controls.
```

### 11.2 Defect-Nucleation Metric

Define the distance from node i to the defect interface as d_i. Let e_i be the local vortex energy density. A simple localization statistic is:

$$\mathcal{L}_{\text{defect}} = \frac{\displaystyle\sum_i e_i \exp(-d_i^2 / 2σ_d^2)}{\displaystyle\sum_i e_i}.$$

Compare 𝓛_defect against randomized defect locations and null lattices.

> **Criterion 4** *(Defect-nucleation pass condition).* Defect-assisted nucleation is supported only if 𝓛_defect is significantly higher than matched randomized controls and remains robust across window perturbations, neighbor rules, and vortex initializations.

---

## 12. Planned Repository Structure

The companion GitHub repository is hosted at:

> **https://github.com/dfeen87/HLV-G-Lattice-Simulation-Lab**

```
HLV-G-Lattice-Simulation-Lab/
├── README.md
├── LICENSE
├── CITATION.cff
├── PAPER.md
├── THEORY.md
├── requirements.txt
├── CMakeLists.txt
├── src/
│   ├── cpp_core/
│   │   ├── AcceptanceWindow.hpp
│   │   ├── GLatticeGenerator.hpp
│   │   ├── SimulationContext.hpp
│   │   ├── NeighborGraph.hpp
│   │   └── bindings.cpp
│   ├── external/
│   │   └── nanoflann.hpp
│   ├── hlv_engine.cpp
│   └── main.cpp
├── notebooks/
│   ├── 01_generate_g_lattice.ipynb
│   ├── 02_laplacian_recovery.ipynb
│   ├── 03_spectrum_analysis.ipynb
│   ├── 04_vortex_simulation.ipynb
│   └── 05_null_model_comparison.ipynb
├── data/
├── figures/
└── site/
    ├── index.html
    ├── styles.css
    ├── app.js
    └── assets/
    └── docs/
```

The implementation is primarily organized around a **native C++ HLV engine**. Jupyter notebooks are used as reproducible analysis, execution, and plotting layers for the numerical outputs generated by the engine.

### 12.1 Minimum Reproducibility Requirements

1. All random seeds must be fixed and listed
2. Projection matrices and acceptance-window parameters must be stored in machine-readable form
3. Numerical parameters must be exported to metadata files
4. Figures must be reproducible from the C++ engine outputs and associated notebooks, not only manually assembled
5. Null models must be generated by the same computational pipeline wherever possible
6. Result tables should be exported in a machine-readable format such as CSV or JSON

---

## 13. Pre-Registered Analysis Plan

To prevent post-hoc interpretation, the analysis order is fixed before simulation results are inserted.

| Module | Primary Metric | Failure Condition |
|--------|----------------|-------------------|
| **G-lattice construction** | Node count, density, degree distribution, boundary fraction | Construction unstable under small window/projection perturbations |
| **Laplacian recovery** | Error scaling E_Δ(h) | Error does not decrease under refinement or is worse than random nulls |
| **Spectral test** | Low eigenvalue stability, spectral density, anisotropy score | Low spectrum dominated by boundary artifacts or null-equivalent signatures |
| **Vortex stability** | Winding preservation, energy localization, core profile | Winding not preserved or vortex collapses under relaxation |
| **Defect nucleation** | Localization statistic 𝓛_defect | True defects not distinguishable from randomized interfaces |

---

## 14. Computational Results

*All numerical values are interpreted as finite-graph diagnostics and are not taken as evidence for physical spacetime microstructure.*

### 14.1 Result 1: G-Lattice Statistics

The first baseline construction run verifies that the repository can generate a finite projected G-lattice from fixed metadata. The run shown below uses a fixed seed, the `standard_icosahedral_tau` projection matrix, and a spherical acceptance window. The run samples **85,766,121** six-dimensional parent points and retains **76,027** projected nodes, corresponding to an acceptance fraction of 8.86 × 10⁻⁴.

**Table 3 — G-lattice construction metadata (baseline v0.2.0)**

| Metadata Field | Baseline Value |
|----------------|----------------|
| Run ID | `run_001_v02_export` |
| Release tag | `v0.2.0` |
| Master seed | 42 |
| Projection matrix | `standard_icosahedral_tau` |
| Window type | ball |
| Window parameters | {radius: 1.0} |
| Sampling radius R₆ | 10.0 |
| Generated parent points | 85,766,121 |
| Accepted nodes | 76,027 |
| Accepted fraction | 8.86 × 10⁻⁴ |
| Engine | C++/Python hybrid |
| Platform | macOS ARM64 |
| Compiler | AppleClang |
| Timestamp | 2026-05-10T19:00:00Z |

**Large-scale construction benchmark.** In addition to the baseline run, a large-scale benchmark was performed to test numerical scalability:

**Table 4 — Large-scale G-lattice construction benchmark**

| Quantity | Value |
|----------|-------|
| Accepted projected nodes | 985,083 |
| Parent points sampled | 8,303,765,625 |
| Runtime | 22.9613 s |
| Acceptance fraction | ≈ 1.19 × 10⁻⁴ |
| Throughput | ≈ 3.62 × 10⁸ parent checks/s |
| Hardware | Apple M3 Max, 48 GB RAM |
| Graph/Laplacian status | pending |
| Spectral/null-model status | pending |
| Interpretation | construction scalability only |

**Figure 4 — Scaling Behavior of the G-Lattice Construction Pipeline**

```
  log(N)
  10¹⁰ ┤                                                    ▪ ← 8.3 × 10⁹
       │                                               ▪
  10⁹  ┤                                       ▪
       │  ─ ─ ─ ─ ─ 6D parent points ~ O(R₆⁶) ─ ─ ─ ─ ─ ─ ─
       │                               ▪
  10⁸  ┤       ▪ ─ ▪
       │
       └──┬─────┬─────┬─────┬─────┬─────┬──▶  R₆
         10    12    14    16    18    20    22

  Accepted 3D nodes (×10⁶)
   1.0 ┤                                                    ●  ← 985 k
       │                                               ●
   0.6 ┤                                       ●
       │                               ●
   0.2 ┤       ●─────●
       └──┬─────┬─────┬─────┬─────┬─────┬──▶  R₆
         10    12    14    16    18    20    22

  ▪  6D parent points sampled   ●  3D accepted nodes
  Near-10⁶-node construction benchmark achieved at R₆ = 22
```

*This figure reports construction scalability only and does not constitute evidence for continuum recovery, spectral robustness, vortex stability, or physical spacetime microstructure.*

---

### 14.2 Result 2: Graph-Laplacian Construction and Connectivity

The v0.3.0 release extends the baseline point-cloud construction to a graph-level Laplacian pipeline. For the R₆ = 10 baseline lattice, a k-nearest-neighbor graph with k = 15 was constructed and converted into a sparse weighted Laplacian.

**Table 5 — Graph-level Laplacian construction benchmark**

| Quantity | Value |
|----------|-------|
| Release tag | `v0.3.0` |
| Accepted nodes | 76,027 |
| Neighbor rule | k-nearest neighbors, k = 15 |
| Graph connections | 1,140,405 |
| Laplacian matrix size | 76,027 × 76,027 |
| Total graph/Laplacian pipeline time | 0.4840 s |
| Algebraic connectivity λ₂ | 0.017966 |
| Interpretation | connected finite graph; not continuum recovery |

The second Laplacian eigenvalue is positive, **λ₂ = 0.017966**, indicating that the constructed finite graph is connected. These results verify graph construction and spectral connectivity of the baseline lattice.

---

### 14.3 Result 3: Preliminary Laplacian Recovery

The v0.4.0 recovery test evaluates the weighted graph Laplacian on pre-declared smooth probe functions.

**Figure 6a — Quadratic probe f₁ = x² + y² + z², analytic target ∇²f₁ = 6**

```
  Δ_G f₁                          Recovery Convergence
                                   (histogram of node values)
  6.10 ┤  · · · ·                     │
       │ · · · · ·                800 ┤         ┌─┐
  6.05 ┤ · · ·(3D)· ·                 │         │ │
       │  · · · · ·              600 ┤       ┌──┤ ├──┐
  6.00 ┤───── target ─────            │       │  │ │  │
       │  · · · · ·              400 ┤    ┌──┤  │ │  ├──┐
  5.95 ┤ · · · · ·                    │    │  │  │ │  │  │
       │  · · · · ·              200 ┤ ┌──┤  │  │ │  │  ├──┐
  5.90 ┤                              │    │  │  │ │  │  │  │
       └────────────────────          └─┬──┬──┬──┬─┬──┬──┬──┬─▶
                                      −60 −40 −20  0  20  40
                                         Computed value at node i
                            ╌╌╌╌╌ Target ∇²f₁ = 6.0
```

**Figure 6b — Oscillatory probe f₂ = sin(kx), analytic target ∇²f₂ = −k²sin(kx)**

```
  Δ_G f₂ (1D slice)
   10 ┤           ●   ●                ●
      │       ●       ●            ●
    5 ┤   ●                   ●
      │                                       ●
    0 ┼────────────────────────────────────────────▶  x
      │●                            ●
   −5 ┤   ●                   ●
      │       ●           ●
  −10 ┤
      │
      · · · discrete nodes     ── continuum target −k²sin(kx)
      visible node-level scatter around the analytic wave envelope
```

*These plots support preliminary graph-Laplacian consistency checks but do not by themselves establish full continuum recovery.*

---

### 14.4 Result 4: Preliminary Spectral Behavior

**Table 6 — Preliminary spectral diagnostics**

| Diagnostic | Value |
|-----------|-------|
| Smallest nonzero eigenvalue λ₂ | 0.017966 |
| Low-mode participation ratio range | ≈ 0.31 − 0.52 |
| Estimated spectral dimension d_s | ≈ 2.49 |
| MSD diffusion coefficient D | ≈ 1.1243 |
| Null-model comparison | preliminary |
| Window/neighbor-rule robustness | pending |

**Table 7 — Spectral-dimension comparison against null models**

| Graph / Estimator | Estimated d_s | Interpretation |
|-------------------|--------------|----------------|
| HLV G-lattice, eigenvalue-density | 2.5234 | Aperiodic projected graph diagnostic |
| HLV G-lattice, heat-kernel | 2.4530 | Independent estimator; fit-window dependent |
| Cubic lattice | 3.0701 | Close to expected 3D scaling |
| Random graph | 2.7985 | Control value; ensemble variation expected |

**Figure 7 — Spectral Density Comparison: ρ(λ)**

```
  ρ(λ)  "Kill Test": Spectral Density ρ(λ)
  0.7 ┤
      │       ░░░ HLV G-Lattice (Aperiodic)
  0.6 ┤       ▓▓▓ Cubic Baseline (Ordered)
      │  ██  ░░░ Random Control (Chaotic)
  0.5 ┤  ██  ▓▓▓██
      │  ██  ▓▓▓██
  0.4 ┤ ░██░ ▓▓▓██
      │ ░██░▓▓▓███
  0.3 ┤░░██░▓▓▓███
      │░░██░▓███
  0.2 ┤░███░▓▓          ░░░░░░░░░░░
      │░███░           ░░░░░░░░░░░░
  0.1 ┤░███░▓ ▓▓   ░░░░░░░ ░░░░░░░░░░░░
      │░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
  0.0 ┤
      └──┬──┬──┬──┬──┬──┬────▶  λ (Energy Level)
         0  2  4  6  8  10  12

  The HLV distribution differs visibly from both null models.
  Cubic lattice d_s ≈ 3.07 (close to expected 3D value ✓).
```

**Figure 8 — Cumulative Eigenvalue Density: N(λ) ~ λ^{d_s/2}**

```
  log N(λ)                                         ● ●
     10¹ ┤                                   ●  ●
          │                             ●  ●
          │                        ● ●   ╌╌╌╌ power-law fit
          │              N(λ)  ●●         d_s ≈ 2.49
          │            ●●
     10⁰ ┤          ●●
          │        ●●
          │      ●
          │    ●
          └──────────┬──────────────────▶  log λ
                   10⁻¹                 10⁰

  Scaling: N(λ) ~ λ^{d_s/2},  d_s ≈ 2.49
```

**Figure 9 — Heat-Kernel Return Probability (5,000 Modes)**

```
  log P(t)   High-Resolution Heat Kernel (5,000 Modes)
    10³ ┤ ●●●●●
        │      ●●●●
    10² ┤          ●●●●           ╌╌ Scaling fit d_s ≈ 2.4530
        │               ●●●
    10¹ ┤                  ●●●●
        │                      ●●●●●●●●
        └──────┬─────────┬────────────────▶  log t
             10⁻²      10⁻¹       10⁰      10¹
                      Diffusion Time t

  ● HLV 5K-Mode Data    ╌╌ Scaling Fit (d_s = 2.4530)
  Consistent with eigenvalue-density estimate d_s ≈ 2.49.
```

---

### 14.5 Result 5: Vortex Stability

The v0.5.0 vortex benchmark initializes an integer n = 1 vortex phase field on the baseline finite HLV G-lattice.

**Figure 10 — Vortex Stability Benchmarks**

```
  ┌─────────────────────────────┐  ┌─────────────────────────────┐
  │ Energy Relaxation: E[Ψ]     │  │ HLV Energy Density Map      │
  │                             │  │     y                        │
  │ 10³┤─── HLV G-Lattice      │  │  6  ┤                        │
  │    │╲   ─ ─ Cubic           │  │  4  ┤     ░░░░░░             │
  │    │ ╲  ······ Random       │  │  2  ┤   ░░▒▒▒▒▒░░            │
  │    │  ╲                     │  │  0  ┤  ░▒▒▓██▓▒▒░            │
  │    │   ╲─╌ ─╌               │  │ −2  ┤   ░░▒▒▒▒▒░░            │
  │    │     ─────────          │  │ −4  ┤     ░░░░░░             │
  │    └──────────────▶ iter    │  │     └──────────────▶ x       │
  └─────────────────────────────┘  └─────────────────────────────┘
  ┌─────────────────────────────┐  ┌─────────────────────────────┐
  │ Vortex Core Profile ρ(r)   │  │ Final Phase Distribution     │
  │ 1.2┤         ········· ρ₀  │  │  6  ┤  🟥🟧🟨🟩🟦🟪         │
  │ 1.0┤               ·····   │  │  4  ┤🟥  🟧  🟨  🟩  🟦🟪    │
  │ 0.8┤         ·····         │  │  2  ┤🟧    🟨    🟩    🟦    │
  │ 0.6┤     ····              │  │  0  ┤🟨      🟩      🟦      │
  │ 0.4┤  ···                  │  │ −2  ┤🟩    🟦    🟪    🟥    │
  │ 0.2┤ ·                     │  │ −4  ┤🟦  🟪  🟥  🟧  🟨🟩    │
  │ 0.0┤·                      │  │     └──────────────▶ x       │
  │    └────────────────▶ r    │  │  Phase winds 2π: θ ∈ [0, 2π) │
  └─────────────────────────────┘  └─────────────────────────────┘
```

**Table 8 — Winding-number preservation after vortex relaxation**

| Graph / Manifold | N_C after relaxation |
|-----------------|----------------------|
| HLV G-lattice | 1.000000 |
| Cubic baseline | 1.000000 |
| Random graph | 1.000000 |

*The integer winding is preserved on the HLV G-lattice and on matched null controls; therefore this result is interpreted as compatibility with integer vortex sectors, not as an HLV-specific signature.*

---

### 14.6 Result 6: Refined Defect-Localization Diagnostics

The refined v0.6.1 defect-localization test introduces a prescribed geometric mismatch plane at X = 0 and evaluates whether the relaxed vortex-energy density exhibits enhanced localization near the corresponding defect interface.

**Key result:** The observed defect-localization score is:

$$\mathcal{L}_{\text{defect}} ≈ 0.117031, \quad Z ≈ 2.24, \quad p ≈ 0.013 \quad (n = 150\text{ controls})$$

**Figure 11 — Statistical Defect-Localization Diagnostic**

```
  Randomized Null Distribution (n=150)      Sharpened Vortex Localization Map
  ┌──────────────────────────────────┐      ┌──────────────────────────────────┐
  │  Density                         │      │  y         Mismatch Edge          │
  │                 ╭───╮            │      │  6 ┤   ↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓           │
  │ 25 ┤           │   │            │      │  4 ┤ ░░░░░░░░░░░░░░░░             │
  │    │        ╭──╯   ╰──╮         │      │  2 ┤ ░░▒▒▒▒▒▒▒▒▒▒░░              │
  │ 15 ┤     ╭──╯         ╰──╮      │      │  0 ┤░░▒▒▓▓██▓▓▒▒░░               │
  │    │  ╭──╯               ╰──╮   │      │ −2 ┤ ░░▒▒▒▒▒▒▒▒▒▒░░              │
  │  5 ┤──╯                    ╰─┐  │      │ −4 ┤   ░░░░░░░░░░░░              │
  │    └──┬───┬───┬───┬───┬───┬──┤  │      │    └────────────────────▶ x       │
  │      .00 .02 .04 .06 .08 .10 │  │      │      enhanced near X=0 edge       │
  │                         ┊    │  │      └──────────────────────────────────┘
  │         L_defect ≈ 0.117 ╍╍╍╍╍  │
  └──────────────────────────────┘
     ╌╌╌  Normal fit     ─── True Defect (Z ≈ 2.24, p ≈ 0.013)
```

**Figure 12 — Specificity Check (v0.6.1)**

```
  HLV G-Lattice              Cubic Baseline              Random Graph
  ┌──────────────┐           ┌──────────────┐           ┌──────────────┐
  │ · ·░░░· · · │           │ · · · · · · │           │  · ·· · ·   │
  │ ·░▒▒▒▒░· · │           │ · ·▒▒▒· · │           │ · ·  ·  ·   │
  │░▒▒▓██▓▒▒░  │           │ ·▒▒██▒▒· │           │ · · · · · · │
  │ ·░▒▒▒▒░· · │           │ · ·▒▒▒· · │           │  ·  · ·  ·  │
  │ · ·░░░· · · │           │ · · · · · · │           │ ·  · · ·  · │
  └──────────────┘           └──────────────┘           └──────────────┘
  Structured aperiodic        Regular-grid                Incoherent —
  localization ✓              localization ✓              no pattern ✗
  (not a random artifact)     (not HLV-only)
```

**Limitation control — homogeneous vs. defective interface:**

$$\mathcal{L}_{\text{hom}} ≈ 0.1174, \quad \mathcal{L}_{\text{def}} ≈ 0.1170, \quad ΔL ≈ -3.88 × 10^{-4}$$

This near-zero differential response indicates that the current localization metric is mainly sensitive to **generic vortex-core localization** rather than to defect-specific causal pinning. The result is interpreted as a limitation of the present localization metric.

---

## 15. Discussion

The proposed simulation program is intentionally strict. Three interpretive outcomes are possible:

1. **Failure:** The G-lattice fails basic numerical consistency — poor Laplacian recovery, unstable spectra, disconnected or highly implementation-dependent neighbor graphs, or excessive sensitivity to arbitrary choices of window, sampling radius, and neighbor rule.

2. **Null parity:** The G-lattice behaves as a valid quasicrystalline numerical substrate but shows no distinctive advantage over matched null lattices. HLV would retain a possible effective discretization, but not a uniquely motivated one.

3. **Success:** The G-lattice shows robust continuum recovery, stable low-energy spectra, and vortex/defect signatures not reproduced by matched nulls. This would not prove HLV as fundamental physics, but it would provide a strong computational foundation for subsequent effective-field simulations and analog-laboratory proposals.

### 15.1 Reviewer-Risk Analysis

| Reviewer Concern | Safeguard in this Manuscript |
|-----------------|------------------------------|
| "Quasicrystals are already known." | Novelty is not claimed for quasicrystals alone; the contribution is the HLV-specific reproducible testbed. |
| "Neighbor choices are arbitrary." | Three pre-declared neighbor rules and sensitivity analysis are required. |
| "The Laplacian may not recover continuum physics." | Smooth-probe recovery is a primary kill test. |
| "Observed signatures may be generic graph artifacts." | Cubic, random, jittered, shuffled, and periodic-approximant nulls are mandatory. |
| "Vortices are inserted by hand." | Stability, winding preservation, and defect localization are tested after relaxation and against controls. |
| "Simulation does not prove spacetime ontology." | Explicitly accepted; the paper claims only numerical viability of the G-lattice sector. |

---

## 16. Conclusion

This paper formulates a rigorous and reproducible simulation program for the HLV G-lattice sector. The central goal is not to claim that HLV is correct, but to expose one of its core geometric assumptions to numerical stress tests. A viable G-lattice must be:

- Constructible and stable under implementation choices
- Capable of approximating continuum differential operators
- Spectrally robust
- Distinguishable from matched null models
- Capable of hosting topological vortex configurations without inserting the desired conclusion by construction

If these tests fail, the G-lattice sector of HLV must be revised or rejected. If they succeed, HLV gains a stronger computational foundation: not proof of fundamental spacetime microstructure, but a reproducible effective geometry suitable for more detailed field-theoretic and analog-simulation studies.

The next step is concrete: complete the open implementation, lock all parameters, generate the figures and result tables, and allow the HLV G-lattice to be tested by the same standards used for other computational models in theoretical and mathematical physics.

---

## Funding

This research received no specific grant from any funding agency in the public, commercial, or not-for-profit sectors.

## Data Availability

All simulation data will be made available through the companion GitHub repository:  
**https://github.com/dfeen87/HLV-G-Lattice-Simulation-Lab**

## Code Availability

The companion implementation is publicly hosted at:  
**https://github.com/dfeen87/HLV-G-Lattice-Simulation-Lab**

## Conflict of Interest

The authors declare no known competing financial interests or personal relationships.

## Ethical Statement

This research is theoretical and computational. It does not involve human participants, animals, clinical data, or biological materials.

## Author Contributions

**Marcel Krüger** conceived the HLV G-lattice simulation concept, formulated the theoretical framework, defined the recovery and falsification criteria, and drafted the manuscript. **Don Michael Feeney Jr.** contributed to the computational implementation, repository architecture, reproducibility layer, numerical simulations, null-model generation, figure production, and technical validation of the simulation pipeline. Both authors reviewed and approved the submitted manuscript.

## AI Assistance Statement

During preparation of this draft, AI-based writing assistance was used for language polishing, LaTeX structuring, and organization of manuscript sections. The scientific content, theoretical assumptions, simulation plan, interpretation, and final responsibility remain with the authors.

---

## References

[1] M. Krüger, *A Compact Core Formulation of the Helix–Light–Vortex Framework*, Zenodo (2026). doi:10.5281/zenodo.20071241.

[2] M. Krüger, D. M. Feeney Jr., and M. T. Wende, "Information-Theoretic Modeling of Neural Coherence via Triadic Spiral-Time Dynamics: A Framework for Neurodynamic Collapse," *Medinformatics* (2026). doi:10.47852/bonviewMEDIN62029043.

[3] M. Baake and U. Grimm, *Aperiodic Order. Vol. 1: A Mathematical Invitation*, Cambridge University Press, Cambridge (2013). ISBN: 978-0-521-86991-1.

[4] O. Zilberberg, "Topology in quasicrystals [Invited]," *Optical Materials Express* 11(4), 1143–1157 (2021). doi:10.1364/OME.416552.

[5] D. V. Else, S.-J. Huang, A. Prem, and A. Gromov, "Quantum many-body topology of quasicrystals," *Physical Review X* 11, 041051 (2021). doi:10.1103/PhysRevX.11.041051.

[6] J. Fan and H. Huang, "Topological states in quasicrystals," *Frontiers of Physics* 17, 13203 (2022). doi:10.1007/s11467-021-1100-y.

[7] Y. Meyer, *Algebraic Numbers and Harmonic Analysis*, North-Holland Mathematical Library, Vol. 2 (1972).

[8] N. G. de Bruijn, "Algebraic theory of Penrose's non-periodic tilings of the plane. I," *Indagationes Mathematicae* (Proceedings) 84(1), 39–52 (1981). doi:10.1016/1385-7258(81)90016-0.

[9] P. Kramer and R. Neri, "On periodic and non-periodic space fillings of E_m obtained by projection," *Acta Crystallographica Section A* 40(5), 580–587 (1984). doi:10.1107/S0108767384001203.

[10] M. Duneau and A. Katz, "Quasiperiodic patterns," *Physical Review Letters* 54(25), 2688–2691 (1985). doi:10.1103/PhysRevLett.54.2688.

[11] F. R. K. Chung, *Spectral Graph Theory*, CBMS Regional Conference Series, Vol. 92, American Mathematical Society (1997). ISBN: 978-0-8218-0315-8.

[12] S. Armstrong and R. Venkatraman, "Optimal convergence rates for the spectrum of the graph Laplacian on Poisson point clouds," arXiv:2312.08149 (2023).

[13] H. M. Price, Y. D. Chong, A. Khanikaev, et al., "Roadmap on topological photonics," *Journal of Physics: Photonics* 4, 032501 (2022). doi:10.1088/2515-7647/ac4ee4.

[14] G.-J. Tang, X.-T. He, F.-L. Shi, et al., "Topological photonic crystals: physics, designs, and applications," *Laser & Photonics Reviews* 16, 2100300 (2022). doi:10.1002/lpor.202100300.

[15] Y. Zhang, Z. Lan, L. Hu, et al., "Chiral photonic topological states in Penrose quasicrystals," *Optics Letters* 48, 2229–2232 (2023). doi:10.1364/OL.486612.

[16] X. Yang, Z. Wang, H. Gao, et al., "Observation of photonic chiral edge states in Penrose quasicrystals," *Optical Materials Express* 14, 1590–1595 (2024). doi:10.1364/OME.524390.

[17] A. Nambisan, S. Günzler, D. Rieger, et al., "Quantum coherent manipulation and readout of superconducting vortex states," *Nature* 653, 63–67 (2026). doi:10.1038/s41586-026-10441-7.

[18] M. E. Peskin and D. V. Schroeder, *An Introduction to Quantum Field Theory*, Addison-Wesley (1995).

[19] H. B. Nielsen and P. Olesen, "Vortex-line models for dual strings," *Nuclear Physics B* 61, 45–61 (1973). doi:10.1016/0550-3213(73)90350-7.

[20] H. Edelsbrunner, D. Letscher, and A. Zomorodian, "Topological persistence and simplification," *Discrete & Computational Geometry* 28(4), 511–533 (2002). doi:10.1007/s00454-002-2885-2.

[21] M. Krüger and D. M. Feeney Jr., *HLV-G-Lattice-Simulation-Lab: A falsification-oriented computational testbed for the Helix–Light–Vortex framework*, GitHub (2026). https://github.com/dfeen87/HLV-G-Lattice-Simulation-Lab.
