/*
 * HLV G-Lattice Simulation Lab
 * Licensed under the MIT License
 */

#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include <pybind11/stl.h>

#include "GLatticeGenerator.hpp" 
#include "NeighborGraph.hpp"
#include "SimulationContext.hpp"

namespace py = pybind11;

// ============================================================================
// PYBIND11 MODULE BINDINGS
// ============================================================================
PYBIND11_MODULE(hlv_engine, m) {
    m.doc() = "HLV bare-metal C++ engine with precise Cut-and-Project and Graph capabilities";

    // 1. Bind SimulationContext (Inside hlv namespace)
    // Using readonly as previously determined by the compiler
    py::class_<hlv::SimulationContext>(m, "SimulationContext")
        .def_readonly("run_id", &hlv::SimulationContext::run_id)
        .def_readonly("master_seed", &hlv::SimulationContext::master_seed)
        .def_readonly("window_type", &hlv::SimulationContext::window_type);

    // 2. Bind GLatticeGenerator (Inside hlv namespace)
    py::class_<hlv::GLatticeGenerator>(m, "GLatticeGenerator")
        .def(py::init<const hlv::SimulationContext&>())
        .def("generate", &hlv::GLatticeGenerator::generate)
        .def("get_physical_nodes", &hlv::GLatticeGenerator::get_physical_nodes);
        // UNCOMMENT and verify name if you need the mask:
        // .def("get_interior_mask", &hlv::GLatticeGenerator::get_interior_mask); 

    // 3. Bind NeighborGraph (Global namespace - NO hlv:: prefix)
    py::class_<NeighborGraph>(m, "NeighborGraph")
        .def(py::init<const Eigen::MatrixXd &>(), py::arg("physical_nodes"))
        .def("compute_knn_graph", &NeighborGraph::compute_knn_graph, py::arg("k"),
             "Compute the k-nearest neighbor graph returning (node_i, node_j, squared_distance)");
        // UNCOMMENT and verify name if you need the Laplacian:
        // .def("get_laplacian", &NeighborGraph::get_laplacian); 
}
