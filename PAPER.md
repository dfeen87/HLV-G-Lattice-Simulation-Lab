# A Reproducible Computational Testbed for the Helix–Light–Vortex (HLV) G-Lattice

**6D-to-3D quasicrystalline construction, Laplacian recovery, spectral testing, null models, and vortex stability**

Marcel Krüger$^{*1}$ and Don Michael Feeney Jr.$^2$

$^1$ Independent Researcher, Meiningen, Germany  
$^2$ Independent Researcher, Pennsylvania, USA

*Draft: May 2026*

> $^*$Corresponding author: marcelkrueger092@gmail.com

---

## Abstract

The Helix–Light–Vortex (HLV) framework is a conservative effective-field research program in which a quasicrystalline G-lattice is treated as a candidate geometric substrate to be tested rather than assumed. In its present formulation, HLV combines a six-dimensional cut-and-project construction with a triadic phase–memory temporal structure entering low-energy dynamics through controlled effective-field deformations. A central weakness of the program at its present stage is not the absence of formal ingredients, but the lack of a reproducible numerical testbed capable of evaluating whether its core geometric objects behave as viable discretizations of continuum field theory. This paper addresses that gap by formulating a computational framework for constructing a finite 6D-to-3D quasicrystalline G-lattice, building its neighbor graph, defining a weighted graph Laplacian, testing continuum recovery, comparing against matched null models, and simulating topological vortex configurations on the resulting background.

The simulation layer is deliberately framed as a falsification-oriented testbed rather than as evidence that physical spacetime is quasicrystalline. The key tests are: (i) whether the graph Laplacian approximates the continuum Laplacian for smooth probe functions; (ii) whether the low-energy spectral sector is stable under sampling radius, window deformation, and neighbor-rule variation; (iii) whether quasicrystal-specific signatures survive comparison against cubic, random, jittered, periodic-approximant, and phase-shuffled null lattices; and (iv) whether vortex winding, energy localization, and defect-assisted nucleation can be reproduced on the G-lattice without inserting the expected result by construction. The manuscript specifies algorithms, metrics, acceptance criteria, failure modes, and repository structure for an open implementation. No claim is made that HLV is proven, that the Standard Model is derived, or that the simulations establish fundamental spacetime microstructure. The purpose is narrower: to convert the HLV G-lattice sector into a transparent, reproducible, and falsifiable computational object suitable for subsequent effective-field and analog-simulation studies.

**Keywords:** Helix–Light–Vortex framework; quasicrystalline G-lattice; cut-and-project geometry; graph Laplacian; spectral analysis; continuum recovery; null models; vortex stability; effective field theory; falsifiability; reproducible simulation.

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

In this sense, the present manuscript is not an attempt to validate HLV by assertion, but to expose one of its central geometric assumptions to the same numerical stress tests used for other computational field-theory discretizations.

### 1.1 Reviewer-oriented scope

A likely reviewer objection is that quasicrystals, graph Laplacians, vortices, and topological defects are already known. This is correct. Novelty is not claimed for these ingredients individually. The contribution is the conservative numerical integration of these ingredients into the HLV-specific chain:

$$\mathbb{Z}^6 \longrightarrow G_\varphi \subset \mathbb{R}^3 \longrightarrow \Delta_G \longrightarrow \text{continuum recovery / spectral tests / vortex stability / null models.} \tag{1}$$

The paper is therefore best read as a reproducibility and falsification study of the HLV G-lattice sector, not as a final unification proof.

---

## 2. Relation to Prior HLV Work

The present manuscript is a computational companion to the compact HLV core formulation and mathematical foundation [1]. Earlier HLV work introduced: (i) the triadic spiral-time variable $\Psi(t) = (t,\, \varphi(t),\, \chi(t))$; (ii) a real kinetic prefactor $A(t) = 1 + \epsilon(t)$; (iii) a quasicrystalline G-lattice as an effective substrate; and (iv) recovery limits in which standard QFT and GR are restored. The mathematical foundation also formulates a G-lattice Laplacian and states the continuum requirement $\Delta_G f \to \nabla^2 f$ in the appropriate limit. The present paper turns this formal requirement into a reproducible numerical protocol.

A related application of the triadic spiral-time operator and the $\Delta\Phi$ instability functional was developed in an information-theoretic neurodynamic context [2]. That work is cited here only as background for the operator notation and the broader HLV program. It is not used as evidence for the G-lattice, quasicrystalline spacetime, or any of the spectral claims tested in the present manuscript.

The present work also connects to the HLV vortex-sector manuscript, where integer angular momentum and effective topological charge are modeled through vortex configurations on a quasicrystalline background. In that context, the central field ansatz is the standard topological vortex

$$\Psi(r,\theta) = f(r)\,e^{in\theta}, \quad n \in \mathbb{Z}, \tag{2}$$

with canonical angular momentum $L_z = n\hbar$. The present paper does not derive half-integer fermion spin and does not attempt a Standard Model particle derivation. Instead, it asks the narrower numerical question of whether such vortex configurations can be implemented, relaxed, and tested on the proposed G-lattice.

> **Non-claim 1** *(No proof from simulation alone).* Even successful G-lattice simulations would not prove HLV as a fundamental theory. They would only establish that the proposed geometric substrate is a reproducible and mathematically usable effective object.

---

## 3. Theoretical Background

### 3.1 Cut-and-project geometry

For the modern mathematical framework of aperiodic order, including Delone sets, Meyer sets, model sets, and cut-and-project schemes, we refer to the standard monograph by Baake and Grimm [3].

Let $\Lambda^6 = \mathbb{Z}^6 \subset \mathbb{R}^6$ be a six-dimensional integer lattice. Assume a decomposition

$$\mathbb{R}^6 = E_\parallel \oplus E_\perp, \quad E_\parallel \simeq \mathbb{R}^3, \quad E_\perp \simeq \mathbb{R}^3, \tag{3}$$

with projections $\pi_\parallel : \mathbb{R}^6 \to E_\parallel$ and $\pi_\perp : \mathbb{R}^6 \to E_\perp$. Given a compact acceptance window $W_\varphi \subset E_\perp$, define the physical point set

$$G_\varphi = \left\{ \pi_\parallel(x) : x \in \mathbb{Z}^6,\; \pi_\perp(x) \in W_\varphi \right\}. \tag{4}$$

This higher-dimensional projection viewpoint also connects naturally to the topological classification of quasiperiodic systems [4]. Beyond their role as aperiodic geometric substrates, quasicrystals can support nontrivial topological states and quantum many-body topological structures despite the absence of conventional translational symmetry [5, 6]. This provides motivation for the spectral and vortex-stability tests used here, while not implying that the HLV G-lattice is a physical spacetime substrate.

This is the finite numerical object to be constructed. In the ideal mathematical setting, such constructions yield model sets with long-range order and nonperiodicity when the projection subspaces are irrationally oriented and the window satisfies standard regularity assumptions. The algebraic and quasiperiodic structures underlying this viewpoint have a classical mathematical foundation in Meyer's work [7]. De Bruijn's algebraic theory of Penrose non-periodic tilings provides a central example [8]. This projection-based perspective is also directly aligned with the work of Kramer and Neri [9] and Duneau and Katz [10].

### 3.2 Triadic time enters only as a controlled deformation

The HLV time variable is written as

$$\Psi(t) = (t,\, \varphi(t),\, \chi(t)), \tag{5}$$

or as hypercomplex bookkeeping

$$\psi(t) = t + i\varphi(t) + j\chi(t), \quad i^2 = j^2 = -1, \quad ij = -ji. \tag{6}$$

For the present numerical paper, only the real kinetic prefactor is used:

$$A(t) = 1 + \epsilon(t), \quad |\epsilon(t)| \ll 1, \quad A(t) > 0. \tag{7}$$

This restriction is deliberate. The G-lattice simulation does not require an ontological claim about time. It only requires that any time-dependent deformation remains a positive perturbation of the standard kinetic sector.

### 3.3 Weighted graph Laplacian

Let $G = (V, E)$ be the finite graph obtained from $G_\varphi$. For a scalar function $f : V \to \mathbb{R}$, define

$$(\Delta_G f)_i = \sum_{j \in N(i)} w_{ij}\,(f_j - f_i), \tag{8}$$

where $N(i)$ is the neighbor set of node $i$ and $w_{ij} > 0$ are symmetric weights. The weights are chosen to satisfy a discrete second-moment condition as closely as possible:

$$\sum_{j \in N(i)} w_{ij}\,(x_j - x_i)(x_j - x_i)^T \approx c_i I_3. \tag{9}$$

This condition prevents the Laplacian from becoming an arbitrary graph operator and provides the numerical target for continuum recovery. The spectral analysis of the weighted neighbor graph follows the standard viewpoint of spectral graph theory [11].

### 3.4 Continuum recovery requirement

For smooth probe functions $f$ sampled on $G_\varphi$, the essential requirement is

$$\Delta_G f \longrightarrow \nabla^2 f \tag{10}$$

in a controlled limit of increasing sampling density and decreasing effective spacing. In numerical form, this becomes an error-scaling test rather than a theorem:

$$E_\Delta(h) = \frac{\|\Delta_G f - \nabla^2 f\|_{2,V_h}}{\|\nabla^2 f\|_{2,V_h} + \eta}, \tag{11}$$

where $h$ is an effective spacing scale and $\eta > 0$ prevents division by zero.

---

## 4. Graphical Overview

This section provides a schematic overview of the numerical construction used in the present protocol.

```
┌──────────────────────────────────────────────────────────────────────┐
│                    6D parent lattice  ℤ⁶                             │
│                    π∥  ↙            ↘  π⊥                           │
│          E∥ ≃ ℝ³                        E⊥ ≃ ℝ³                     │
│              ↓                               ↓                       │
│        G-lattice Gφ  ◄──────────  acceptance window W               │
│              ↓             selection                                 │
│   neighbor graph + ΔG  →  recovery + spectra  →  vortex tests       │
└──────────────────────────────────────────────────────────────────────┘
```

**Figure 1:** Computational pipeline. The 6D parent lattice is projected into physical and internal spaces. The acceptance window selects a finite 3D G-lattice. A neighbor graph and weighted Laplacian are constructed, followed by continuum-recovery tests, spectral tests, null-model comparisons, and vortex-stability simulations.

The pipeline is complemented by a broader schematic: a six-dimensional hypercubic parent lattice $\mathbb{Z}^6$ is projected into an effective physical sector $E_\parallel$, while an internal sector $E_\perp$ and an acceptance window $W$ determine which projected nodes are retained:

$$G = \{\pi_\parallel(p) \mid p \in \mathbb{Z}^6,\; \pi_\perp(p) \in W\}.$$

The network exhibits weighted quasiperiodic connectivity, phase-like internal offsets, and possible local dodecagonal/icosahedral motifs.

**Figure 2:** *(Schematic visual analogy of the HLV G-lattice construction — see companion repository for rendered figures.)* The figure illustrates weighted quasiperiodic connectivity, phase-like coordinates, and local dodecagonal domains. It is not presented as a numerically generated physical spacetime lattice.

---

## 5. Numerical Construction of the G-Lattice

### 5.1 Finite sampling

The infinite lattice $\mathbb{Z}^6$ is truncated by a radius $R_6$:

$$\Lambda^6(R_6) = \{n \in \mathbb{Z}^6 : \|n\|_\infty \leq R_6\}. \tag{12}$$

For each $n \in \Lambda^6(R_6)$, compute

$$x_n = \pi_\parallel(n), \quad y_n = \pi_\perp(n). \tag{13}$$

The finite G-lattice is then

$$G_R = \{x_n : y_n \in W\}. \tag{14}$$

Boundary effects are controlled by evaluating observables only on an interior subset $G_R^{\text{int}}$, excluding nodes within a distance $d_{\text{edge}}$ of the finite-sample boundary.

### 5.2 Projection matrices

A practical implementation may use orthonormal projection matrices $P_\parallel, P_\perp \in \mathbb{R}^{3 \times 6}$ satisfying

$$P_\parallel P_\parallel^T = I_3, \quad P_\perp P_\perp^T = I_3, \quad P_\parallel P_\perp^T = 0. \tag{15}$$

The irrational orientation should be fixed once and version-controlled.

> **Protocol 1** *(G-lattice generation).* The repository must implement the following deterministic procedure:
> 1. Fix $R_6$, projection matrices, and acceptance window parameters.
> 2. Enumerate $\Lambda^6(R_6)$.
> 3. Compute $x_n = P_\parallel n$, $y_n = P_\perp n$.
> 4. Keep nodes satisfying $y_n \in W$.
> 5. Deduplicate physical points within tolerance $\tau_{\text{dup}}$.
> 6. Export node coordinates, parent indices, internal coordinates, and metadata.

### 5.3 Acceptance window choices

The primary window is a compact approximately icosahedral/dodecahedral window. For robustness, the simulation must repeat all core results under at least three windows:

$$W \in \{W_{\text{ball}},\; W_{\text{dodeca}},\; W_{\text{ellipsoid}}\}. \tag{16}$$

If a signature appears only under a highly tuned window and vanishes for nearby windows, it must not be claimed as a robust HLV effect.

---

## 6. Neighbor Graph and Laplacian Construction

### 6.1 Neighbor rules

At least three rules are pre-declared:

1. **$k$-nearest neighbors:** connect each node to its $k$ nearest physical neighbors.
2. **Radius graph:** connect nodes with $\|x_i - x_j\| \leq r_c$.
3. **Parent-edge projection:** connect projected nodes whose parent indices differ by a basis vector or selected short vector in $\mathbb{Z}^6$.

The parent-edge rule is most faithful to the cut-and-project construction. The other rules are included as sensitivity checks.

### 6.2 Laplacian normalization

For a graph with weights $w_{ij}$, define the matrix

$$L_{ij} = \begin{cases} -w_{ij}, & i \neq j,\; j \in N(i), \\ \displaystyle\sum_{\ell \in N(i)} w_{i\ell}, & i = j, \\ 0, & \text{otherwise.} \end{cases} \tag{17}$$

Then $\Delta_G = -L$ under the convention in Eq. (8). Both combinatorial and normalized Laplacians should be reported, but continuum recovery should be tested primarily with the weighted non-normalized Laplacian.

> **Criterion 1** *(Laplacian admissibility).* The G-lattice Laplacian is considered admissible only if all three conditions hold:
> 1. $w_{ij} = w_{ji} > 0$ and the graph is connected on the interior domain.
> 2. The second-moment anisotropy score
> $$A_i = \frac{\|M_i - (\text{tr}\,M_i/3)\,I_3\|_F}{\|M_i\|_F}, \quad M_i = \sum_{j \in N(i)} w_{ij}(x_j - x_i)(x_j - x_i)^T, \tag{18}$$
> remains bounded and decreases under coarse-graining.
> 3. Smooth-probe Laplacian errors decrease with increasing sampling density.

---

## 7. Continuum-Recovery Tests

### 7.1 Probe functions

The following probe functions are pre-declared:

$$f_1(x,y,z) = x^2 + y^2 + z^2, \quad \nabla^2 f_1 = 6, \tag{19}$$

$$f_2(x,y,z) = \sin(kx), \quad \nabla^2 f_2 = -k^2 \sin(kx), \tag{20}$$

$$f_3(x,y,z) = \exp\!\left[-\alpha(x^2+y^2+z^2)\right], \quad \nabla^2 f_3 = (4\alpha^2 r^2 - 6\alpha)\,e^{-\alpha r^2}. \tag{21}$$

These functions test polynomial, oscillatory, and localized smooth behavior.

### 7.2 Error scaling

For each probe $f_m$, compute $E_\Delta^{(m)}(h)$ from Eq. (11). The effective spacing $h$ may be estimated by the median nearest-neighbor distance on the interior graph.

> **Criterion 2** *(Recovery pass condition).* A minimal recovery pass requires:
> $$E_\Delta(h) \downarrow \text{ as } h \downarrow, \tag{22}$$
> and the G-lattice error must be comparable to or better than the matched random geometric graph for low-frequency probes. If the error does not decrease with refinement, the numerical G-lattice sector fails the recovery test.

The corresponding preliminary recovery diagnostics are reported in Section 14.3.

---

## 8. Spectral Tests

### 8.1 Eigenvalue problem

Compute the eigenvalues of the positive graph Laplacian:

$$L u_n = \lambda_n u_n, \quad 0 = \lambda_0 \leq \lambda_1 \leq \lambda_2 \leq \cdots \tag{23}$$

Rigorous convergence results for graph Laplacian spectra on point clouds provide a useful technical benchmark [12]. The low-energy part of the spectrum should behave stably under changes in $R_6$, window thickness, and neighbor rule.

### 8.2 Spectral density and anisotropy

Define the empirical spectral density

$$\rho(\lambda) = \frac{1}{N}\sum_n \delta_\sigma(\lambda - \lambda_n), \tag{24}$$

where $\delta_\sigma$ is a Gaussian smoothing kernel.

Penrose photonic quasicrystals have been shown to support chiral topological edge states characterized by real-space topological invariants, despite the absence of conventional translational symmetry and Bloch-band topology [15, 16]. In the present work, this analogy is used only to motivate spectral-robustness and boundary-mode tests on the HLV G-lattice.

> **Criterion 3** *(Spectral robustness).* A G-lattice spectral signature is considered robust only if it persists across: (i) sampling radius variation; (ii) small window deformations; (iii) at least two neighbor rules; and (iv) comparison against null lattices with matched node count and degree distribution.

---

## 9. Null Models

Null models are essential. Without them, any apparent structure in a quasicrystal simulation could be mistaken for evidence when it is merely a generic property of graphs.

**Table 1:** Pre-declared null models and what they test.

| Null model | Construction | Purpose |
|---|---|---|
| Cubic lattice | Regular 3D grid with matched node density | Tests whether effects are ordinary discretization artifacts |
| Random geometric graph | Random points with radius/kNN graph | Tests generic graph connectivity artifacts |
| Jittered cubic lattice | Cubic nodes plus small random displacements | Tests sensitivity to disorder without quasiperiodicity |
| Phase-shuffled G-lattice | Preserve coordinates, randomize internal labels or phases | Tests whether phase/topology signatures require HLV structure |
| Periodic approximant | Rational approximation to projection slope | Tests dependence on true aperiodicity |

> A result is not HLV-specific unless it survives comparison to these nulls.

---

## 10. Vortex Simulation on the G-Lattice

Recent experiments have demonstrated coherent manipulation and quantum non-demolition readout of superconducting vortex states in granular aluminium microwave resonators [17]. This provides an important condensed-matter analogue showing that discrete or granular media can support coherent, quantized vortex degrees of freedom, motivating the numerical study below.

### 10.1 Discrete complex field

Let $\Psi_i = \rho_i e^{i\theta_i}$ be a complex scalar field on graph nodes. Use the energy functional

$$E[\Psi] = \frac{1}{2}\sum_{(i,j)\in E} w_{ij}|\Psi_i - \Psi_j|^2 + \sum_i V(|\Psi_i|), \tag{25}$$

with Mexican-hat potential

$$V(\rho) = \frac{\lambda}{4}(\rho^2 - \rho_0^2)^2. \tag{26}$$

Initialize a vortex around axis $\hat{n}$ and center $x_0$ by

$$\theta_i = n\,\operatorname{atan2}\!\left((x_i - x_0)\cdot e_2,\;(x_i - x_0)\cdot e_1\right), \quad n \in \mathbb{Z}, \tag{27}$$

where $e_1, e_2$ span the plane perpendicular to $\hat{n}$. Relax $\rho_i$ and optionally $\theta_i$ under gradient descent while monitoring winding preservation.

### 10.2 Discrete winding number

For a closed graph loop $C = (i_1, i_2, \ldots, i_m, i_1)$, define

$$N_C = \frac{1}{2\pi}\sum_{\ell=1}^{m} \operatorname{wrap}_{(-\pi,\pi]}(\theta_{i_{\ell+1}} - \theta_{i_\ell}). \tag{28}$$

A vortex is numerically stable only if $N_C$ remains close to an integer under relaxation and perturbation.

> **Non-claim 2** *(No fermion spin derivation).* The vortex simulation tests integer winding sectors $n \in \mathbb{Z}$ and canonical angular momentum analogues. It does not derive half-integer fermion spin or the Standard Model spinor spectrum.

> **Non-claim 3** *(No QED derivation).* The circulation current associated with the vortex phase is an effective topological analogue. It is not a derivation of physical electric charge or quantum electrodynamics.

---

## 11. Projection-Mismatch Defects and Vortex Nucleation

A distinctive HLV-sector claim is that projection-mismatch defects in the cut-and-project geometry can act as nucleation sites for vortex excitations. To distinguish robust projection-mismatch defects from short-lived numerical artifacts, the defect analysis can be augmented by persistence-based topological diagnostics [20].

### 11.1 Defect construction

Introduce a local shift of the internal acceptance window:

$$W \to W + \delta W(x), \tag{29}$$

where $\delta W(x)$ changes across a plane or narrow interface. This creates a projection-mismatch edge. The simulation compares vortex energy localization near this interface against homogeneous-window controls.

```
        projection-mismatch edge
               |
      ─ ─ ─ ─ │ ─ ─ ─ ─
              core
           ┌───────┐
     Jvort │   ●   │ Jμ
           └───────┘
```

**Figure 3:** Schematic projection-mismatch defect test. The simulation must determine whether vortex energy density and phase gradients statistically localize near projection-mismatch edges more strongly than in matched homogeneous and randomized controls.

### 11.2 Defect-nucleation metric

Define the distance from node $i$ to the defect interface as $d_i$. Let $e_i$ be the local vortex energy density. A simple localization statistic is

$$\mathcal{L}_{\text{defect}} = \frac{\displaystyle\sum_i e_i \exp\!\left(-d_i^2 / 2\sigma_d^2\right)}{\displaystyle\sum_i e_i}. \tag{30}$$

Compare $\mathcal{L}_{\text{defect}}$ against randomized defect locations and null lattices.

> **Criterion 4** *(Defect-nucleation pass condition).* Defect-assisted nucleation is supported only if $\mathcal{L}_{\text{defect}}$ is significantly higher than matched randomized controls and remains robust across window perturbations, neighbor rules, and vortex initializations.

---

## 12. Planned Repository Structure

The public companion repository is hosted at [https://github.com/dfeen87/HLV-G-Lattice-Simulation-Lab](https://github.com/dfeen87/HLV-G-Lattice-Simulation-Lab).

```
HLV-G-Lattice-Simulation-Lab/
├── README.md
├── LICENSE
├── CITATION.cff
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
├── site/
│   ├── index.html
│   ├── styles.css
│   ├── app.js
│   └── assets/
└── docs/
```

### 12.1 Minimum reproducibility requirements

1. All random seeds must be fixed and listed.
2. Projection matrices and acceptance-window parameters must be stored in machine-readable form.
3. Numerical parameters must be exported to metadata files.
4. Figures must be reproducible from the C++ engine outputs and associated notebooks.
5. Null models must be generated by the same computational pipeline wherever possible.
6. Result tables should be exported in a machine-readable format such as CSV or JSON.

---

## 13. Pre-Registered Analysis Plan

**Table 2:** Pre-registered simulation modules and acceptance logic.

| Module | Primary metric | Failure condition |
|---|---|---|
| G-lattice construction | Node count, density, degree distribution, boundary fraction | Construction unstable under small window/projection perturbations |
| Laplacian recovery | Error scaling $E_\Delta(h)$ | Error does not decrease under refinement or is worse than random nulls |
| Spectral test | Low eigenvalue stability, spectral density, anisotropy score | Low spectrum dominated by boundary artifacts or null-equivalent signatures |
| Vortex stability | Winding preservation, energy localization, core profile | Winding not preserved or vortex collapses under relaxation |
| Defect nucleation | Localization statistic $\mathcal{L}_{\text{defect}}$ | True defects not distinguishable from randomized interfaces |

---

## 14. Computational Results

All numerical values are interpreted as finite-graph diagnostics and are not taken as evidence for physical spacetime microstructure.

### 14.1 Result 1: G-lattice statistics

The first baseline construction run verifies that the repository can generate a finite projected G-lattice from fixed metadata. The run shown in Table 3 uses a fixed seed, the `standard_icosahedral_tau` projection matrix, and a spherical acceptance window. The run samples 85,766,121 six-dimensional parent points and retains 76,027 projected nodes, corresponding to an acceptance fraction of $8.86445 \times 10^{-4}$.

**Table 3:** G-lattice construction metadata for the baseline v0.2.0 point-cloud run.

| Metadata field | Baseline value |
|---|---|
| Run ID | `run_001_v02_export` |
| Release tag | `v0.2.0` |
| Master seed | 42 |
| Projection matrix | `standard_icosahedral_tau` |
| Window type | ball |
| Window parameters | {radius: 1.0} |
| Sampling radius $R_6$ | 10.0 |
| Generated parent points | 85,766,121 |
| Accepted nodes | 76,027 |
| Accepted fraction | $8.86445 \times 10^{-4}$ |
| Median nearest-neighbor distance | deferred to graph/Laplacian release |
| Mean degree | deferred to graph/Laplacian release |
| Degree variance | deferred to graph/Laplacian release |
| Interior node count | deferred to graph/Laplacian release |
| Engine | C++/Python hybrid |
| Platform | macOS ARM64 |
| Compiler | AppleClang |
| Timestamp | 2026-05-10T19:00:00Z |

**Large-scale construction benchmark.** A large-scale benchmark sampled 8,303,765,625 six-dimensional parent points and retained 985,083 accepted projected nodes in 22.9613 seconds, corresponding to an acceptance fraction of approximately $1.19 \times 10^{-4}$ and a throughput of approximately $3.62 \times 10^8$ parent-point evaluations per second.

**Table 4:** Large-scale G-lattice construction benchmark.

| Quantity | Value |
|---|---|
| Accepted projected nodes | 985,083 |
| Parent points sampled | 8,303,765,625 |
| Runtime | 22.9613 s |
| Acceptance fraction | $\approx 1.19 \times 10^{-4}$ |
| Throughput | $\approx 3.62 \times 10^8$ parent checks/s |
| Hardware | Apple M3 Max, 48 GB RAM |
| Graph/Laplacian status | pending |
| Spectral/null-model status | pending |
| Interpretation | construction scalability only |

**Figure 4** *(see repository):* Scaling behavior of the G-lattice construction pipeline. The blue curve shows the number of 6D parent points sampled vs. search radius $R_6$ (scaling $\sim O(R_6^6)$); the red curve shows the resulting accepted 3D nodes. The largest run reaches 985,083 accepted nodes from 8,303,765,625 sampled parent points.

**Figure 5** *(see repository):* Baseline 3D projection of the finite HLV G-lattice generated from 85,766,121 sampled parent points using $R_6 = 10.0$, fixed seed 42, the `standard_icosahedral_tau` projection matrix, and a spherical acceptance window of radius 1.0. The baseline run retains 76,027 accepted projected nodes.

### 14.2 Result 2: Graph-Laplacian construction and connectivity

The v0.3.0 release extends the baseline point-cloud construction to a graph-level Laplacian pipeline. For the $R_6 = 10$ baseline lattice, a $k$-nearest-neighbor graph with $k = 15$ was constructed and converted into a sparse weighted Laplacian. The resulting graph contains 76,027 nodes and 1,140,405 connections. The second Laplacian eigenvalue is positive, $\lambda_2 = 0.017966$, indicating that the constructed finite graph is connected.

**Table 5:** Graph-level Laplacian construction benchmark.

| Quantity | Value |
|---|---|
| Release tag | `v0.3.0` |
| Accepted nodes | 76,027 |
| Neighbor rule | $k$-nearest neighbors, $k = 15$ |
| Graph connections | 1,140,405 |
| Laplacian matrix size | $76{,}027 \times 76{,}027$ |
| Total graph/Laplacian pipeline time | 0.4840 s |
| Algebraic connectivity $\lambda_2$ | 0.017966 |
| Interpretation | connected finite graph; not continuum recovery |

### 14.3 Result 3: Preliminary Laplacian recovery

The v0.4.0 recovery test evaluates the weighted graph Laplacian on pre-declared smooth probe functions.

For the **quadratic probe** $f_1(x,y,z) = x^2 + y^2 + z^2$, $\nabla^2 f_1 = 6$: the baseline G-lattice is expected to reproduce a constant continuum Laplacian. The diagnostic shows a spatially distributed graph-Laplacian response and comparison against the analytic target value.

For the **oscillatory probe** $f_2(x,y,z) = \sin(kx)$, $\nabla^2 f_2 = -k^2\sin(kx)$: the discrete Laplacian response reproduces the expected oscillatory structure qualitatively, but with visible node-level scatter around the continuum target.

**Figure 6** *(see repository):* Preliminary Laplacian-recovery diagnostics. Upper panel: node-wise response for the quadratic probe vs. constant analytic target. Lower panel: response for the oscillatory probe, capturing the expected wave-front structure with visible node-level scatter. These plots support preliminary graph-Laplacian consistency checks but do not by themselves establish full continuum recovery.

These results are interpreted as preliminary Laplacian-recovery diagnostics. A complete recovery claim requires raw numerical error statistics, the remaining Gaussian probe, refinement scaling of $E_\Delta(h)$, and comparison against cubic, random geometric, and jittered-cubic null lattices.

### 14.4 Result 4: Preliminary spectral behavior

The baseline graph permits preliminary spectral diagnostics. The low-lying Laplacian spectrum contains a near-zero ground mode and a positive algebraic connectivity. The participation ratios of the first low-energy modes are not near the single-node localization limit, suggesting that these modes are distributed over extended portions of the graph. A cumulative eigenvalue-density fit gives an estimated spectral dimension of approximately $d_s \approx 2.49$. A simple propagation test yields an approximately linear mean-squared-displacement profile with an effective diffusion coefficient $D \approx 1.1243$.

**Table 6:** Preliminary spectral diagnostics of the baseline G-lattice Laplacian.

| Diagnostic | Value |
|---|---|
| Smallest nonzero eigenvalue $\lambda_2$ | 0.017966 |
| Low-mode participation ratio range | $\approx 0.31 - 0.52$ |
| Estimated spectral dimension $d_s$ | $\approx 2.49$ |
| MSD diffusion coefficient $D$ | $\approx 1.1243$ |
| Null-model comparison | preliminary |
| Window/neighbor-rule robustness | pending |
| Interpretation | preliminary finite-graph spectral diagnostic |

A preliminary null-model comparison was also performed:

**Table 7:** Preliminary spectral-dimension comparison against null models and estimator variants.

| Graph model / estimator | Estimated $d_s$ | Interpretation |
|---|---|---|
| HLV G-lattice, eigenvalue-density estimator | 2.5234 | Aperiodic projected graph diagnostic |
| HLV G-lattice, heat-kernel estimator | 2.4530 | Independent estimator; fit-window dependent |
| Cubic lattice | 3.0701 | Close to expected 3D scaling |
| Random graph | 2.7985 | Control value; ensemble variation expected |

The cubic-lattice value is close to the expected three-dimensional scaling, providing a useful sanity check. The HLV G-lattice value differs from both controls in this preliminary run, but this is not yet interpreted as an HLV-specific physical signature.

A separate high-resolution heat-kernel return-probability estimator using 5,000 modes produced a preliminary scaling value of $d_s \approx 2.4530$, broadly consistent with the eigenvalue-density estimate.

**Figure 7** *(see repository):* Preliminary spectral-density comparison between the HLV G-lattice, an ordered cubic-lattice control, and a random-graph control.

**Figure 8** *(see repository):* Cumulative eigenvalue-density diagnostic. The scaling relation $N(\lambda) \sim \lambda^{d_s/2}$ yields an effective finite-graph spectral dimension of approximately $d_s \approx 2.49$.

**Figure 9** *(see repository):* High-resolution heat-kernel return-probability diagnostic using 5,000 modes. The log–log scaling fit yields $d_s \approx 2.4530$.

### 14.5 Result 5: Vortex stability

The v0.5.0 vortex benchmark initializes an integer $n = 1$ vortex phase field on the baseline finite HLV G-lattice and relaxes the corresponding discrete complex scalar field under the graph energy functional defined in Eq. (25).

The HLV G-lattice energy decreases and approaches a stable plateau during relaxation. The energy-density map remains localized around the vortex core, while the radial core profile $\rho(r)$ is suppressed near the center and approaches its asymptotic bulk value away from the core. The final phase distribution preserves the expected $2\pi$ angular winding.

**Table 8:** Winding-number preservation after vortex relaxation.

| Graph / manifold | $N_C$ after relaxation |
|---|---|
| HLV G-lattice | 1.000000 |
| Cubic baseline | 1.000000 |
| Random graph | 1.000000 |

The discrete winding number after relaxation is $N_C = 1.000000$, matching the target winding $n = 1$. Matched cubic and random graph controls also preserve $N_C = 1.000000$. Therefore, the present benchmark demonstrates that the HLV G-lattice can support stable integer vortex sectors under relaxation, but it does not establish an HLV-specific vortex signature.

**Figure 10** *(see repository):* Vortex-stability benchmark for the $n = 1$ sector. Top left: energy relaxation vs. iterations for HLV G-lattice, cubic, and random graph controls. Top right: localized vortex energy density. Bottom left: radial vortex core profile $\rho(r)$. Bottom right: final phase distribution after relaxation.

### 14.6 Result 6: Refined defect-localization diagnostics

The refined v0.6.1 defect-localization test introduces a prescribed geometric mismatch plane at $X = 0$ and evaluates whether the relaxed vortex-energy density exhibits enhanced localization near the corresponding defect interface.

For the refined v0.6.1 run, the observed defect-localization score is $\mathcal{L}_{\text{defect}} \approx 0.117031$. Comparison against $n = 150$ randomized-interface controls places this value in the upper tail of the null distribution, with $Z \approx 2.24$ and $p \approx 0.013$. This provides preliminary statistical evidence that the prescribed mismatch interface enhances vortex-energy localization relative to randomized interface placements.

**Figure 11** *(see repository):* Statistical defect-localization diagnostic. Left: randomized-interface null distribution vs. observed mismatch-interface localization score ($Z \approx 2.24$, $p \approx 0.013$). Right: post-relaxation local vortex-energy density showing enhanced localization near the prescribed mismatch interface.

As an additional specificity check, the post-relaxation vortex-energy localization pattern of the HLV G-lattice is compared against matched cubic and random graph controls. The HLV case exhibits structured localization on an aperiodic projected support. The cubic baseline supports regular-grid energy localization, whereas the random graph control lacks a comparable coherent geometric localization pattern.

As an additional limitation control, the vortex-energy localization scores for a homogeneous reference and a defective-interface configuration are nearly identical: $\mathcal{L}_{\text{hom}} \approx 0.1174$ and $\mathcal{L}_{\text{def}} \approx 0.1170$, with a differential localization $\Delta \mathcal{L} \approx -3.88 \times 10^{-4}$. This indicates that the current localization score is dominated by generic vortex-core localization rather than by the imposed defect interface alone.

**Figure 12** *(see repository):* Specificity check — HLV G-lattice (left), cubic baseline (middle), random graph (right).

**Figure 13** *(see repository):* Control test for defect-specific localization. Localization scores are nearly identical ($\Delta \mathcal{L} \approx -3.88 \times 10^{-4}$), indicating the current metric is mainly sensitive to generic vortex-core localization.

---

## 15. Discussion

The proposed simulation program is intentionally strict. Three interpretive outcomes are possible:

1. **Failure:** The G-lattice may fail basic numerical consistency: poor Laplacian recovery, unstable spectra, disconnected or highly implementation-dependent neighbor graphs, or excessive sensitivity to arbitrary choices of window, sampling radius, and neighbor rule. This would seriously weaken the G-lattice sector as a candidate effective geometric substrate.

2. **Valid but non-distinctive:** The G-lattice may behave as a valid quasicrystalline numerical substrate but show no distinctive advantage over matched null lattices. HLV would retain a possible effective discretization, but not a uniquely motivated one.

3. **Robust signatures:** The G-lattice may show robust continuum recovery, stable low-energy spectra, and vortex/defect signatures not reproduced by matched nulls. This would not prove HLV as fundamental physics, but would provide a strong computational foundation for subsequent effective-field simulations.

### 15.1 Reviewer-risk analysis

**Table 9:** Likely reviewer objections and built-in safeguards.

| Reviewer concern | Safeguard in this manuscript |
|---|---|
| "Quasicrystals are already known." | Novelty is not claimed for quasicrystals alone; the contribution is the HLV-specific reproducible testbed. |
| "Neighbor choices are arbitrary." | Three pre-declared neighbor rules and sensitivity analysis are required. |
| "The Laplacian may not recover continuum physics." | Smooth-probe recovery is a primary kill test. |
| "Observed signatures may be generic graph artifacts." | Cubic, random, jittered, shuffled, and periodic-approximant nulls are mandatory. |
| "Vortices are inserted by hand." | Stability, winding preservation, and defect localization are tested after relaxation and against controls. |
| "Simulation does not prove spacetime ontology." | Explicitly accepted; the paper claims only numerical viability of the G-lattice sector. |

---

## 16. Conclusion

This paper formulates a rigorous and reproducible simulation program for the HLV G-lattice sector. The central goal is not to claim that HLV is correct, but to expose one of its core geometric assumptions to numerical stress tests. A viable G-lattice must be constructible, stable under implementation choices, capable of approximating continuum differential operators, spectrally robust, distinguishable from matched null models, and capable of hosting topological vortex configurations without inserting the desired conclusion by construction.

If these tests fail, the G-lattice sector of HLV must be revised or rejected. If they succeed, HLV gains a stronger computational foundation: not proof of fundamental spacetime microstructure, but a reproducible effective geometry suitable for more detailed field-theoretic and analog-simulation studies.

The next step is concrete: complete the open implementation, lock all parameters, generate the figures and result tables, and allow the HLV G-lattice to be tested by the same standards used for other computational models in theoretical and mathematical physics.

---

## Funding

This research received no specific grant from any funding agency in the public, commercial, or not-for-profit sectors.

## Data Availability

All simulation data will be made available through the companion GitHub repository:  
[https://github.com/dfeen87/HLV-G-Lattice-Simulation-Lab](https://github.com/dfeen87/HLV-G-Lattice-Simulation-Lab)

## Code Availability

[https://github.com/dfeen87/HLV-G-Lattice-Simulation-Lab](https://github.com/dfeen87/HLV-G-Lattice-Simulation-Lab)

## Conflict of Interest

The authors declare that they have no known competing financial interests or personal relationships that could have appeared to influence the work reported in this manuscript.

## Ethical Statement

This research is theoretical and computational. It does not involve human participants, animals, clinical data, or biological materials.

## Author Contributions

Marcel Krüger conceived the HLV G-lattice simulation concept, formulated the theoretical framework, defined the recovery and falsification criteria, and drafted the manuscript. Don Michael Feeney Jr. contributed to the computational implementation, repository architecture, reproducibility layer, numerical simulations, null-model generation, figure production, and technical validation of the simulation pipeline. Both authors reviewed and approved the submitted manuscript.

## AI Assistance Statement

During preparation of this draft, AI-based writing assistance was used for language polishing, LaTeX structuring, and organization of manuscript sections. The scientific content, theoretical assumptions, simulation plan, interpretation, and final responsibility remain with the authors.

---

## References

[1] M. Krüger, *A Compact Core Formulation of the Helix–Light–Vortex Framework*, Zenodo (2026). doi:10.5281/zenodo.20071241.

[2] M. Krüger, D. M. Feeney Jr., and M. T. Wende, "Information-Theoretic Modeling of Neural Coherence via Triadic Spiral-Time Dynamics: A Framework for Neurodynamic Collapse," *Medinformatics* (2026). doi:10.47852/bonviewMEDIN62029043.

[3] M. Baake and U. Grimm, *Aperiodic Order. Vol. 1: A Mathematical Invitation*, Cambridge University Press, Cambridge (2013). ISBN: 978-0-521-86991-1.

[4] O. Zilberberg, "Topology in quasicrystals [Invited]," *Optical Materials Express* **11**(4), 1143–1157 (2021). doi:10.1364/OME.416552.

[5] D. V. Else, S.-J. Huang, A. Prem, and A. Gromov, "Quantum many-body topology of quasicrystals," *Physical Review X* **11**, 041051 (2021). doi:10.1103/PhysRevX.11.041051.

[6] J. Fan and H. Huang, "Topological states in quasicrystals," *Frontiers of Physics* **17**, 13203 (2022). doi:10.1007/s11467-021-1100-y.

[7] Y. Meyer, *Algebraic Numbers and Harmonic Analysis*, North-Holland Mathematical Library, Vol. 2, North-Holland Publishing Company, Amsterdam (1972).

[8] N. G. de Bruijn, "Algebraic theory of Penrose's non-periodic tilings of the plane. I," *Indagationes Mathematicae (Proceedings)* **84**(1), 39–52 (1981). doi:10.1016/1385-7258(81)90016-0.

[9] P. Kramer and R. Neri, "On periodic and non-periodic space fillings of $E^m$ obtained by projection," *Acta Crystallographica Section A* **40**(5), 580–587 (1984). doi:10.1107/S0108767384001203.

[10] M. Duneau and A. Katz, "Quasiperiodic patterns," *Physical Review Letters* **54**(25), 2688–2691 (1985). doi:10.1103/PhysRevLett.54.2688.

[11] F. R. K. Chung, *Spectral Graph Theory*, CBMS Regional Conference Series in Mathematics, Vol. 92, American Mathematical Society, Providence, RI (1997). ISBN: 978-0-8218-0315-8.

[12] S. Armstrong and R. Venkatraman, "Optimal convergence rates for the spectrum of the graph Laplacian on Poisson point clouds," arXiv:2312.08149 (2023).

[13] H. M. Price, Y. D. Chong, A. Khanikaev, et al., "Roadmap on topological photonics," *Journal of Physics: Photonics* **4**, 032501 (2022). doi:10.1088/2515-7647/ac4ee4.

[14] G.-J. Tang, X.-T. He, F.-L. Shi, J.-W. Liu, X.-D. Chen, and J.-W. Dong, "Topological photonic crystals: physics, designs, and applications," *Laser & Photonics Reviews* **16**, 2100300 (2022). doi:10.1002/lpor.202100300.

[15] Y. Zhang, Z. Lan, L. Hu, Y. Shu, X. Yuan, P. Guo, X. Peng, W. Chen, and J. Li, "Chiral photonic topological states in Penrose quasicrystals," *Optics Letters* **48**, 2229–2232 (2023). doi:10.1364/OL.486612.

[16] X. Yang, Z. Wang, H. Gao, L. Yang, Y. Meng, X. Xi, P. P. Shum, and Z. Gao, "Observation of photonic chiral edge states in Penrose quasicrystals," *Optical Materials Express* **14**, 1590–1595 (2024). doi:10.1364/OME.524390.

[17] A. Nambisan et al., "Quantum coherent manipulation and readout of superconducting vortex states," *Nature* **653**, 63–67 (2026). doi:10.1038/s41586-026-10441-7.

[18] M. E. Peskin and D. V. Schroeder, *An Introduction to Quantum Field Theory*, Addison-Wesley, Reading, MA (1995).

[19] H. B. Nielsen and P. Olesen, "Vortex-line models for dual strings," *Nuclear Physics B* **61**, 45–61 (1973). doi:10.1016/0550-3213(73)90350-7.

[20] H. Edelsbrunner, D. Letscher, and A. Zomorodian, "Topological persistence and simplification," *Discrete & Computational Geometry* **28**(4), 511–533 (2002). doi:10.1007/s00454-002-2885-2.

[21] M. Krüger and D. M. Feeney Jr., *HLV-G-Lattice-Simulation-Lab: A falsification-oriented computational testbed for the Helix–Light–Vortex framework*, GitHub repository (2026). [https://github.com/dfeen87/HLV-G-Lattice-Simulation-Lab](https://github.com/dfeen87/HLV-G-Lattice-Simulation-Lab).
