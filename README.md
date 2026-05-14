# HLV G-Lattice Simulation Lab

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](./LICENSE)
![C++](https://img.shields.io/badge/C%2B%2B-17-00599C?logo=c%2B%2B&logoColor=white)
![Status](https://img.shields.io/badge/Status-Research%20Prototype-6f42c1)

**A falsification-oriented computational testbed for the Helix-Light-Vortex (HLV) framework.**

This repository implements a reproducible pipeline that maps higher-dimensional cut-and-project geometry into numerical simulation workflows. It focuses on constructing a 6D→3D quasicrystalline G-lattice and testing continuum recovery, spectral behavior, and vortex dynamics against null baselines.

**Authors:** Marcel Krüger & Don Michael Feeney Jr.

---

## Repository Scope

The simulation layer is designed to test whether the HLV G-lattice can behave as a mathematically controlled discretization of continuum field dynamics.

The core computational sequence is:

$$\mathbb{Z}^{6}\longrightarrow G_{\varphi}\subset\mathbb{R}^{3}\longrightarrow\Delta_{G}$$

1. **G-Lattice Generation** — project 6D parent-lattice samples into physical 3D space.
2. **Laplacian Construction** — build neighbor connectivity and weighted graph Laplacians.
3. **Continuum Recovery** — evaluate convergence behavior $\Delta_{G}f\longrightarrow\nabla^{2}f$.
4. **Spectral Stability** — assess low-energy eigenvalue structure and robustness.
5. **Vortex Simulation** — test winding preservation and localization behavior.

---

## Release Roadmap

- **v0.1** — repository skeleton: README, LICENSE, CITATION.cff, folder layout, requirements.
- **v0.2** — deterministic G-lattice generation: 6D sampling, projection matrices, acceptance windows, metadata export.
- **v0.3** — neighbor graph and weighted Laplacian.
- **v0.4** — continuum recovery tests with probe functions, scaling metrics, CSV outputs, and plots.
- **v0.5** — spectral tests and null-model comparisons.
- **v0.6** — vortex simulations and winding-number tests.
- **v1.0** — paper-ready release with locked parameters and reproducible figures/tables.

---

## Repository Structure

```text
HLV-G-Lattice-Simulation-Lab/
├── README.md
├── LICENSE
├── CITATION.cff
├── PAPER.md
├── THEORY.md
├── requirements.txt
├── CMakeLists.txt
├── setup.py
├── pyproject.toml
├── src/                                 # Native C++ entrypoints and headers
│   ├── cpp_core/                        # Core C++ simulation and pybind layer
│   ├── external/
│   ├── hlv_engine.cpp
│   └── main.cpp
├── notebooks/                           # Reproducible analysis notebooks
│   ├── 01_generate_g_lattice.ipynb
│   ├── 02_laplacian_recovery.ipynb
│   ├── 03_spectrum_analysis.ipynb
│   ├── 04_vortex_simulation.ipynb
│   └── 05_null_model_comparison.ipynb
├── data/                                # Generated datasets/artifacts
├── figures/                             # Generated figures for reports/papers
└── site/                                # Static documentation/visualization site
    ├── index.html
    ├── styles.css
    ├── app.js
    ├── assets/
    └── docs/
```

---

## Reproducibility

- **Deterministic execution:** seeded and script-driven workflows for repeatability.
- **Transparent outputs:** notebook and export structure supports independent verification.
- **License:** released under the [MIT License](./LICENSE) for open academic and industrial reuse.

> Reproducibility Disclaimer: Notebook-generated figures are intended for pipeline validation. You may notice minor visual or statistical differences compared to the manuscript-grade figures due to the use of lower-fidelity KDTree connectivity and automated rendering settings. The underlying physics and numerical targets remain identical.
>
> Note: The /figures and /data/exports directories are preserved via .gitkeep; all artifacts are generated dynamically by the notebooks.
