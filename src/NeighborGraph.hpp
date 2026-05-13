#pragma once

#include <Eigen/Dense>
#include <vector>
#include <tuple>
#include "external/nanoflann.hpp"

// 1. THE ADAPTOR: Teaches nanoflann how to read Eigen memory directly (Zero-copy)
struct EigenMatrixAdaptor {
    const Eigen::MatrixXd& mat;
    EigenMatrixAdaptor(const Eigen::MatrixXd& mat) : mat(mat) {}

    // Must return the number of data points
    inline size_t kdtree_get_point_count() const { return mat.rows(); }

    // Must return the Euclidean distance metric for the tree
    inline double kdtree_get_pt(const size_t idx, const size_t dim) const {
        return mat(idx, dim);
    }

    // Optional bounding box method (we don't need it, just return false)
    template <class BBOX>
    bool kdtree_get_bbox(BBOX& /*bb*/) const { return false; }
};

// 2. THE GRAPH ENGINE
class NeighborGraph {
private:
    Eigen::MatrixXd nodes;
    EigenMatrixAdaptor adaptor;
    
    // Define the strict KD-Tree type
    using KDTreeType = nanoflann::KDTreeSingleIndexAdaptor<
        nanoflann::L2_Simple_Adaptor<double, EigenMatrixAdaptor>,
        EigenMatrixAdaptor,
        3 /* dimensionality (3D physical space) */
    >;
    
    KDTreeType index;

public:
    // Constructor takes your projected nodes and instantly builds the spatial tree
    NeighborGraph(const Eigen::MatrixXd& physical_nodes) 
        : nodes(physical_nodes), 
          adaptor(nodes), 
          index(3, adaptor, nanoflann::KDTreeSingleIndexAdaptorParams(10 /* max leaf size */)) 
    {
        // This is where the magic happens. 76k nodes sorted in milliseconds.
        index.buildIndex();
    }

    // Searches the tree and returns triplets: (node_i, node_j, squared_distance)
    std::vector<std::tuple<int, int, double>> compute_knn_graph(size_t k) {
        std::vector<std::tuple<int, int, double>> triplets;
        
        // Memory optimization: Pre-allocate the exact size to prevent RAM reallocation
        triplets.reserve(nodes.rows() * k);

        // Loop over every node to find its neighbors
            for (Eigen::Index i = 0; i < nodes.rows(); ++i) {
            std::vector<size_t> ret_index(k + 1);    // +1 because a node will find itself
            std::vector<double> out_dist_sqr(k + 1);
            
            nanoflann::KNNResultSet<double> resultSet(k + 1);
            resultSet.init(ret_index.data(), out_dist_sqr.data());
            
            std::vector<double> query_pt = {nodes(i, 0), nodes(i, 1), nodes(i, 2)};
            index.findNeighbors(resultSet, query_pt.data(), nanoflann::SearchParameters());
            
            // Extract the neighbors (skip j=0 because that is the node itself with dist=0)
            for (size_t j = 1; j <= k; ++j) {
                triplets.emplace_back(i, ret_index[j], out_dist_sqr[j]);
            }
        }
        return triplets;
    }
};
