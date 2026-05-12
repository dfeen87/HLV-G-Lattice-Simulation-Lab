# Theoretical Foundations of the HLV G-Lattice

This document summarizes the core theoretical concepts and mathematical definitions that underpin the HLV G‑Lattice Simulation Lab. The simulation layer is a falsification‑oriented testbed designed to evaluate whether the proposed quasicrystalline G‑lattice behaves as a viable discretization of continuum field theory. The computational pipeline evaluates the sequence:

$$\mathbb{Z}^{6}\longrightarrow G_{\varphi}\subset\mathbb{R}^{3}\longrightarrow \Delta_{G}$$

and then subjects the resulting discrete operator to continuum recovery, spectral, null‑model, and vortex stability tests.

## Notation

* **$\Lambda_{6}$** — parent lattice, $\Lambda_{6}=\mathbb{Z}^{6}$.  
* **$E_{\parallel}, E_{\perp}$** — physical and internal 3D subspaces with $\mathbb{R}^{6}=E_{\parallel}\oplus E_{\perp}$.  
* **$\pi_{\parallel},\pi_{\perp}$** — orthogonal projections onto $E_{\parallel},E_{\perp}$.  
* **$W_{\varphi}$** — compact acceptance window in $E_{\perp}$.  
* **$G_{\varphi}$** — projected physical point set $G_{\varphi}=\{\pi_{\parallel}(x):x\in\mathbb{Z}^{6},\ \pi_{\perp}(x)\in W_{\varphi}\}$.  
* **$G=(V,E)$** — finite graph built from $G_{\varphi}$.  
* **$\Delta_{G}$** — weighted graph Laplacian acting on scalar functions on $V$.  
* **$h$** — effective spacing (median nearest‑neighbor distance on interior nodes).  
* **$\mathcal{E}_{\Delta}(h)$** — discrete Laplacian error metric used for continuum recovery.

## 1. Cut‑and‑Project Geometry

The HLV substrate is constructed by projecting the six‑dimensional integer lattice $\Lambda_{6}=\mathbb{Z}^{6}$ into a three‑dimensional physical subspace using projections $\pi_{\parallel}$ and $\pi_{\perp}$. The finite numerical object is:

$$G_{\varphi}=\{\pi_{\parallel}(x)\;:\;x\in\mathbb{Z}^{6},\ \pi_{\perp}(x)\in W_{\varphi}\}$$

where $W_{\varphi}\subset E_{\perp}$ is a compact acceptance window. Practical implementations must fix projection matrices and window parameters and version them in the repository to ensure exact reproducibility.

**Assumptions**
* Projection subspaces are irrationally oriented to avoid periodic artifacts.  
* Acceptance windows are compact and regular (test at least three window shapes).  
* Boundary nodes are excluded from primary diagnostics; interior domain is used for metrics.

## 2. Weighted Graph Laplacian and Continuum Recovery

From $G_{\varphi}$ construct a finite graph $G=(V,E)$ using predeclared neighbor rules (k‑NN, radius, parent‑edge). For a scalar $f:V\to\mathbb{R}$ define the weighted Laplacian:

$$(\Delta_{G} f)_i=\sum_{j\in N(i)} w_{ij}\,(f_j-f_i)$$

with symmetric weights $w_{ij}>0$ chosen to satisfy a discrete second‑moment condition approximating local isotropy.

**Continuum Recovery Requirement**
The discrete operator must approximate the continuum Laplacian for smooth probes:

$$\Delta_{G} f \longrightarrow \nabla^{2} f$$

Numerically evaluate the error scaling $\mathcal{E}_{\Delta}(h)$ as $h\to 0$.  
**Acceptance Criterion**: $\mathcal{E}_{\Delta}(h)$ must decrease under refinement and be comparable to or better than matched random geometric graph nulls for low‑frequency probes.

## 3. Spectral Stability and Null Models

Solve the eigenproblem $\Delta_{G} u_n=\lambda_n u_n$ and analyze the low‑energy spectral sector. The low modes must be stable under variations in sampling radius $R_6$, window thickness, and neighbor rules.

**Null Models**
Benchmark all signatures against:
* Cubic lattice (regular grid)  
* Random geometric graph  
* Jittered cubic lattice  
* Phase‑shuffled G‑lattice  
* Periodic approximant

**Acceptance Criterion**: spectral signatures (low‑mode structure, anisotropy measures) are considered HLV‑specific only if they persist across sampling/window/neighbour variations and are not reproduced by null models with matched node count and degree distribution.

## 4. Topological Vortex Simulations and Defect Nucleation

Define a discrete complex scalar field $\Psi_i=\rho_i e^{i\theta_i}$ on nodes and evolve under an energy functional with a Mexican‑hat potential. Initialize vortices via angular phase winding and relax using gradient descent.

**Discrete Winding Number**
For a closed loop $C=(i_1,\dots,i_m)$ compute:

$$N_C=\frac{1}{2\pi}\sum_{l=1}^{m} \mathrm{wrap}_{(-\pi,\pi]}(\theta_{i_{l+1}}-\theta_{i_l})$$

**Acceptance Criterion**: a vortex is stable if $N_C$ remains within a small tolerance of an integer during relaxation and across perturbations.

**Defect‑Assisted Nucleation**
Introduce local shifts $W\to W+\delta W(x)$ to create projection‑mismatch edges. Measure vortex energy localization via $\mathcal{L}_{\mathrm{defect}}$ and compare to randomized controls. Defect‑nucleation is supported only if $\mathcal{L}_{\mathrm{defect}}$ is significantly larger than controls and robust under sensitivity tests.

## 5. Reproducibility and Repository Requirements

* Store projection matrices, random seeds, and all parameters in machine‑readable metadata.  
* Provide scripts to regenerate null models and to reproduce figures from raw outputs.  
* Pre‑register analysis order and acceptance logic to avoid post‑hoc selection.

Absolutely, Don — here’s your references section **cleanly formatted in Markdown**, preserving your numbering, spacing, and citation markers while making it look professional and publication‑ready.

---

## 6. References**

1. Y. Meyer, *Algebraic Numbers and Harmonic Analysis*, North-Holland, Amsterdam (1972).  
   <sub>[cite: 401]</sub>

2. N. G. de Bruijn, *Algebraic theory of Penrose's non-periodic tilings of the plane*, Indagationes Mathematicae **43**, 39–52 (1981).  
   <sub>[cite: 402]</sub>

3. P. Kramer and R. Neri, *On periodic and non-periodic space fillings of Em obtained by projection*, Acta Crystallographica A **40**, 580–587 (1984).  
   <sub>[cite: 403]</sub>

4. M. Duneau and A. Katz, *Quasiperiodic patterns*, Physical Review Letters **54**, 2688–2691 (1985).  
   <sub>[cite: 404]</sub>

5. M. Baake and U. Grimm, *Aperiodic Order. Vol. 1: A Mathematical Invitation*, Cambridge University Press (2013).  
   <sub>[cite: 405]</sub>

6. M. Senechal, *Quasicrystals and Geometry*, Cambridge University Press (1995).  
   <sub>[cite: 406]</sub>

7. C. Janot, *Quasicrystals: A Primer*, Oxford University Press (1994).  
   <sub>[cite: 407]</sub>

8. P. Kuchment, *Floquet theory for partial differential equations*, Operator Theory: Advances and Applications **60**, Birkhäuser (1993).  
   <sub>[cite: 408]</sub>

9. F. R. K. Chung, *Spectral Graph Theory*, American Mathematical Society (1997).  
   <sub>[cite: 409]</sub>

10. M. Belkin and P. Niyogi, *Convergence of Laplacian eigenmaps*, Advances in Neural Information Processing Systems **19**, 129–136 (2007).  
    <sub>[cite: 410]</sub>

11. R. R. Coifman and S. Lafon, *Diffusion maps*, Applied and Computational Harmonic Analysis **21**, 5–30 (2006).  
    <sub>[cite: 411]</sub>

12. M. E. Peskin and D. V. Schroeder, *An Introduction to Quantum Field Theory*, Westview Press (1995).  
    <sub>[cite: 412]</sub>

13. S. Weinberg, *The Quantum Theory of Fields, Vol. I*, Cambridge University Press (1995).  
    <sub>[cite: 413]</sub>

14. K. G. Wilson, *Confinement of quarks*, Physical Review D **10**, 2445–2459 (1974).  
    <sub>[cite: 414]</sub>

15. T. H. R. Skyrme, *A nonlinear field theory*, Proceedings of the Royal Society A **260**, 127–138 (1961).  
    <sub>[cite: 415]</sub>

16. H. B. Nielsen and P. Olesen, *Vortex-line models for dual strings*, Nuclear Physics B **61**, 45–61 (1973).  
    <sub>[cite: 416]</sub>

17. R. Jackiw and C. Rebbi, *Solitons with fermion number 1/2*, Physical Review D **13**, 3398–3409 (1976).  
    <sub>[cite: 417]</sub>

18. A. M. Polyakov, *Compact gauge fields and the infrared catastrophe*, Physics Letters B **59**, 82–84 (1975).  
    <sub>[cite: 418]</sub>

19. M. Z. Hasan and C. L. Kane, *Colloquium: Topological insulators*, Reviews of Modern Physics **82**, 3045–3067 (2010).  
    <sub>[cite: 419]</sub>

20. X.-G. Wen, *Colloquium: Zoo of quantum-topological phases of matter*, Reviews of Modern Physics **89**, 041004 (2017).  
    <sub>[cite: 420]</sub>

21. D. Varjas, A. Lau, K. Pöyhönen, A. R. Akhmerov, D. I. Pikulin, and I. C. Fulga, *Topological phases without crystalline counterparts*, Physical Review Letters **123**, 196401 (2019).  
    <sub>[cite: 421]</sub>

22. D.-T. Tran, A. Dauphin, N. Goldman, and P. Gaspard, *Topological Hofstadter insulators in a two-dimensional quasicrystal*, Physical Review B **91**, 085125 (2015).  
    <sub>[cite: 422]</sub>

23. C. W. Duncan, S. Manna, and A. E. B. Nielsen, *Topological models in rotationally symmetric quasicrystals*, Physical Review B **101**, 115413 (2020).  
    <sub>[cite: 423]</sub>

24. H. Edelsbrunner, D. Letscher, and A. Zomorodian, *Topological persistence and simplification*, Discrete & Computational Geometry **28**, 511–533 (2002).  
    <sub>[cite: 424]</sub>

25. G. Carlsson, *Topology and data*, Bulletin of the American Mathematical Society **46**, 255–308 (2009).  
    <sub>[cite: 425]</sub>

26. M. Krüger, *A Compact Core Formulation of the Helix-Light-Vortex Framework*, preprint (2026).  
    <sub>[cite: 429]</sub>

27. M. Krüger, *A Mathematical Unification of the Helix-Light-Vortex Framework*, preprint (2026).  
    <sub>[cite: 430]</sub>

28. M. Krüger, *Topological Vortex Solutions in a Quasicrystalline Background*, preprint (2026).  
    <sub>[cite: 431]</sub>
[cite_start][29] M. Krüger and D. M. Feeney Jr., A Minimal Control-Theoretic Framework for the Triadic Phase Operator $\Delta\Phi$, preprint (2026). [cite: 432]
