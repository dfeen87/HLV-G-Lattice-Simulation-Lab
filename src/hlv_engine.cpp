/*
 * HLV G-Lattice Simulation Lab
 * Licensed under the MIT License
 */

#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include <pybind11/stl.h>

#include "GLatticeGenerator.hpp" 
#include "NeighborGraph.hpp"

namespace py = pybind11;

// ============================================================================
// PYBIND11 MODULE BINDINGS
// ============================================================================
PYBIND11_MODULE(hlv_engine, m) {
    m.doc() = "HLV bare-metal C++ engine with precise Cut-and-Project and Graph capabilities";

    // 1. Bind the immutable context
    py::class_<SimulationContext>(m, "SimulationContext")
        .def(py::init<>())
        .def_readwrite("run_id", &SimulationContext::run_id)
        .def_readwrite("master_seed", &SimulationContext::master_seed)
        .def_readwrite("window_type", &SimulationContext::window_type);

    // 2. Bind the Generation Engine
    py::class_<GLatticeGenerator>(m, "GLatticeGenerator")
        .def(py::init<const SimulationContext&>())
        .def("generate", &GLatticeGenerator::generate)
        .def("get_physical_nodes", &GLatticeGenerator::get_physical_nodes);

    // 3. Bind the KD-Tree Neighbor Graph
    py::class_<NeighborGraph>(m, "NeighborGraph")
        .def(py::init<const Eigen::MatrixXd &>(), py::arg("physical_nodes"))
        .def("compute_knn_graph", &NeighborGraph::compute_knn_graph, py::arg("k"),
             "Compute the k-nearest neighbor graph returning (node_i, node_j, squared_distance)");
}
