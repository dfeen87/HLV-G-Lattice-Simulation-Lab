# HLV G-Lattice Simulation Lab

**A falsification-oriented computational testbed for the Helix-Light-Vortex (HLV) framework.** 

This repository translates higher-dimensional cut-and-project geometries into reproducible Python simulations. It provides the numerical construction of a 6D-to-3D quasicrystalline G-lattice and evaluates continuum recovery, spectral stability, and topological vortex dynamics against strict null models.

**Authors:** Marcel Krüger & Don Michael Feeney Jr.

---

## Repository Objectives

The primary purpose of this simulation layer is **not** to prove fundamental spacetime microstructure, but to evaluate whether the HLV G-lattice behaves as a viable, mathematically controlled discretization of continuum field theory.

The computational pipeline evaluates the sequence:

$$\mathbb{Z}^{6}\longrightarrow G_{\varphi}\subset\mathbb{R}^{3}\longrightarrow\Delta_{G}$$

1. **G-Lattice Generation:** Projection of a 6D parent lattice into physical 3D space.
2. **Laplacian Construction:** Building a neighbor graph and a weighted graph Laplacian ($\Delta_{G}$).
3. **Continuum Recovery:** Error-scaling tests evaluating $\Delta_{G}f\longrightarrow\nabla^{2}f$.
4. **Spectral Stability:** Eigenvalue analysis to confirm the stability of the low-energy spectral sector.
5. **Vortex Simulation:** Testing topological vortex winding preservation and energy localization.

---

## Release Roadmap

* **v0.1** — repository skeleton: README, LICENSE, CITATION.cff, folder structure, requirements, roadmap.
* **v0.2** — deterministic G-lattice generation: 6D sampling, projection matrices, acceptance windows, metadata export.
* **v0.3** — neighbor graph and weighted Laplacian.
* **v0.4** — continuum recovery tests with probe functions, error scaling, CSV outputs, and plots.
* **v0.5** — spectral tests and null models.
* **v0.6** — vortex simulations and winding-number tests.
* **v1.0** — paper-ready release with locked parameters, reproducible figures/tables, and ideally a Zenodo DOI.

---

## 📂 Project Structure

```text
HLV-G-Lattice-Simulation-Lab/
│
├── README.md                           # Master project documentation
├── LICENSE                             # MIT License
├── requirements.txt                    # Core dependencies
├── .gitignore                          # Exclusions for large datasets and caches
├── THEORY.md                           # Extract the core theoretical concepts
│
├── hlv_g_lattice/                      # Core Computational Package
│   ├── __init__.py
│   ├── lattice6d/                      # 6D parent generation & projection matrices
│   │   ├── __init__.py
│   │   ├── generate_z6.py
│   │   ├── acceptance_window.py
│   │   └── cut_and_project.py
│   │
│   ├── lattice3d/                      # 3D G-Lattice structures & graph mathematics
│   │   ├── __init__.py
│   │   ├── point_cloud.py
│   │   ├── neighbor_graph.py
│   │   └── laplacian.py
│   │
│   ├── tests/                          # Automated falsification & recovery tests
│   │   ├── __init__.py
│   │   ├── laplacian_recovery_test.py
│   │   ├── spectrum_test.py
│   │   └── vortex_stability_test.py
│   │
│   ├── simulations/                    # Vortex dynamics & null model baselines
│   │   ├── __init__.py
│   │   ├── vortex_field.py
│   │   ├── defect_analysis.py
│   │   └── null_models.py
│   │
│   └── utils/                          # Shared geometry and export helpers
│       ├── __init__.py
│       ├── geometry.py
│       ├── plotting.py
│       └── export.py
│
├── notebooks/                          # Interactive, reviewer-facing execution
│   ├── 01_generate_g_lattice.ipynb
│   ├── 02_laplacian_recovery.ipynb
│   ├── 03_spectrum_analysis.ipynb
│   ├── 04_vortex_simulation.ipynb
│   └── 05_null_model_comparison.ipynb
│
├── data/                               # Serialized outputs (Excluded from version control)
│   ├── samples/
│   ├── spectra/
│   ├── vortex/
│   └── exports/
│
├── figures/                            # Deterministically generated plots and charts
│   ├── lattice_visuals/
│   ├── spectra/
│   ├── vortex/
│   └── paper/
│
└── site/                               # Front-end documentation and visualization portal
    ├── index.html
    ├── styles.css
    ├── app.js
    ├── assets/
    │   ├── logo.svg
    │   ├── preview_lattice.png
    │   └── preview_spectrum.png
    └── docs/
        └── hlv_g_lattice_overview.html

```

---

## Reproducibility & Analytics

* **Deterministic Execution:** All random seeds are fixed, and figures are regenerated strictly from scripts.
* **Repository Analytics:** To accurately gauge institutional and academic engagement with the HLV framework, repository analytics monitor unique clones.
* **License:** This code is released under the MIT License to facilitate unhindered access and adaptation for both institutional researchers and independent startups.
