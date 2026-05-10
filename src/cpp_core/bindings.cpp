/*
 * HLV-G-Lattice-Simulation-Lab
 * 
 * Copyright (c) 2026 Don Michael Feeney Jr., Marcel Krüger
 * SPDX-License-Identifier: MIT
 */

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/eigen.h>

#include "SimulationContext.hpp"
#include "GLatticeGenerator.hpp"

namespace py = pybind11;
using namespace hlv;

PYBIND11_MODULE(hlv_engine, m) {
    m.doc() = "HLV G-Lattice C++ Core Engine powered by Pybind11";

    // -------------------------------
    // 1. SimulationContext Binding
    // -------------------------------
    py::class_<SimulationContext>(m, "SimulationContext",
        R"pbdoc(
            Immutable simulation metadata container.

            This object locks all run parameters at construction time
            and guarantees reproducibility of the simulation environment.
        )pbdoc")
        .def(py::init<
                std::string, std::string, std::string,
                std::string, std::string,
                uint64_t, std::string, std::string,
                std::map<std::string, double>, std::string>(),
             py::arg("run_id"), py::arg("timestamp"), py::arg("git_commit_hash"),
             py::arg("compiler_info"), py::arg("platform_info"),
             py::arg("master_seed"), py::arg("projection_matrix_id"),
             py::arg("window_type"), py::arg("window_parameters"),
             py::arg("output_directory"),
             R"pbdoc(
                Create a fully locked simulation context.

                All parameters are immutable and exported to JSON for
                reproducibility and reviewer safety.
             )pbdoc")
        .def("export_metadata", &SimulationContext::export_metadata,
             R"pbdoc(
                Export the simulation metadata to a JSON file.

                Uses atomic write semantics to guarantee file integrity.
             )pbdoc");

    // -------------------------------
    // 2. GLatticeGenerator Binding
    // -------------------------------
    py::class_<GLatticeGenerator>(m, "GLatticeGenerator",
        R"pbdoc(
            High-performance 6D → 3D cut-and-project generator.

            Performs the full integer-lattice sweep, applies the acceptance
            window, and returns both physical and internal coordinates.
        )pbdoc")
        .def(py::init<const SimulationContext&>(), py::arg("context"),
             R"pbdoc(
                Construct a generator bound to a specific SimulationContext.

                The context determines:
                - projection matrices
                - window geometry
                - reproducibility guarantees
             )pbdoc")

        .def("generate", &GLatticeGenerator::generate, py::arg("sampling_radius_R6"),
             R"pbdoc(
                Execute the full 6D sampling loop.

                Parameters
                ----------
                sampling_radius_R6 : int
                    The integer radius of the 6D hypercube to sweep.
             )pbdoc")

        .def("get_physical_nodes", &GLatticeGenerator::get_physical_nodes,
             R"pbdoc(
                Return all accepted 3D physical-space nodes as a NumPy array.
             )pbdoc")

        .def("get_internal_nodes", &GLatticeGenerator::get_internal_nodes,
             R"pbdoc(
                Return all accepted 3D internal-space nodes as a NumPy array.
             )pbdoc")

        // Structured JSON → Python dict
        .def("get_generation_metadata",
             [](const GLatticeGenerator& self) {
                 return self.get_generation_metadata();
             },
             R"pbdoc(
                Return generation statistics and geometry metadata as a Python dict.
             )pbdoc")

        // String dump for logging
        .def("get_generation_metadata_string",
             [](const GLatticeGenerator& self) {
                 return self.get_generation_metadata().dump(4);
             },
             R"pbdoc(
                Return generation metadata as a pretty-printed JSON string.
             )pbdoc");
}
