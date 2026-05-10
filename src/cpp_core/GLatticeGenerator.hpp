#pragma once

#include "SimulationContext.hpp"
#include "AcceptanceWindow.hpp"
#include <Eigen/Dense>
#include <vector>
#include <cmath>
#include <nlohmann/json.hpp>

namespace hlv {

class GLatticeGenerator {
private:
    const SimulationContext& ctx;
    AcceptanceWindow window;

    Eigen::Matrix<double, 3, 6> proj_physical;
    Eigen::Matrix<double, 3, 6> proj_internal;

    std::vector<Eigen::Vector3d> physical_nodes;
    std::vector<Eigen::Vector3d> internal_nodes;

    uint64_t total_sampled = 0;
    uint64_t total_accepted = 0;

    void initialize_projection_matrices() {
        double tau = (1.0 + std::sqrt(5.0)) / 2.0;
        double norm_factor = 1.0 / std::sqrt(2.0 * (2.0 + tau));

        proj_physical <<
            1,   tau,  0,  -1,   tau,  0,
            tau, 0,    1,   tau,  0,  -1,
            0,   1,   tau,  0,   -1,  tau;
        proj_physical *= norm_factor;

        proj_internal <<
           -tau,  1,    0,   tau,   1,    0,
            1,    0,   -tau,  1,    0,   tau,
            0,   -tau,  1,    0,   tau,  1;
        proj_internal *= norm_factor;
    }

public:
    explicit GLatticeGenerator(const SimulationContext& context)
        : ctx(context), window(context)
    {
        initialize_projection_matrices();
    }

    void generate(int sampling_radius_R6) {
        physical_nodes.clear();
        internal_nodes.clear();
        total_sampled = 0;
        total_accepted = 0;

        uint64_t side = 2 * sampling_radius_R6 + 1;
        uint64_t total_volume = side * side * side * side * side * side;

        size_t estimated_nodes = total_volume / 40; // ~2.5%
        physical_nodes.reserve(estimated_nodes);
        internal_nodes.reserve(estimated_nodes);

        Eigen::Matrix<double, 6, 1> v6;

        for (int n1 = -sampling_radius_R6; n1 <= sampling_radius_R6; ++n1)
        for (int n2 = -sampling_radius_R6; n2 <= sampling_radius_R6; ++n2)
        for (int n3 = -sampling_radius_R6; n3 <= sampling_radius_R6; ++n3)
        for (int n4 = -sampling_radius_R6; n4 <= sampling_radius_R6; ++n4)
        for (int n5 = -sampling_radius_R6; n5 <= sampling_radius_R6; ++n5)
        for (int n6 = -sampling_radius_R6; n6 <= sampling_radius_R6; ++n6)
        {
            total_sampled++;

            v6 << n1, n2, n3, n4, n5, n6;

            Eigen::Vector3d internal_coord = proj_internal * v6;

            if (window.contains(internal_coord)) {
                Eigen::Vector3d physical_coord = proj_physical * v6;

                physical_nodes.push_back(physical_coord);
                internal_nodes.push_back(internal_coord);
                total_accepted++;
            }
        }
    }

    const std::vector<Eigen::Vector3d>& get_physical_nodes() const { return physical_nodes; }
    const std::vector<Eigen::Vector3d>& get_internal_nodes() const { return internal_nodes; }

    nlohmann::json get_generation_metadata() const {
        nlohmann::json meta;

        meta["sampling_radius_R6"] = ctx.window_parameters.at("sampling_radius_R6");
        meta["total_sampled_6d_points"] = total_sampled;
        meta["total_accepted_nodes"] = total_accepted;

        if (total_sampled > 0) {
            meta["acceptance_fraction"] =
                static_cast<double>(total_accepted) / total_sampled;
        }

        meta["window_geometry"] = window.get_geometry_metadata();

        meta["projection_matrices"]["physical"] = {
            {proj_physical(0,0), proj_physical(0,1), proj_physical(0,2),
             proj_physical(0,3), proj_physical(0,4), proj_physical(0,5)},
            {proj_physical(1,0), proj_physical(1,1), proj_physical(1,2),
             proj_physical(1,3), proj_physical(1,4), proj_physical(1,5)},
            {proj_physical(2,0), proj_physical(2,1), proj_physical(2,2),
             proj_physical(2,3), proj_physical(2,4), proj_physical(2,5)}
        };

        meta["projection_matrices"]["internal"] = {
            {proj_internal(0,0), proj_internal(0,1), proj_internal(0,2),
             proj_internal(0,3), proj_internal(0,4), proj_internal(0,5)},
            {proj_internal(1,0), proj_internal(1,1), proj_internal(1,2),
             proj_internal(1,3), proj_internal(1,4), proj_internal(1,5)},
            {proj_internal(2,0), proj_internal(2,1), proj_internal(2,2),
             proj_internal(2,3), proj_internal(2,4), proj_internal(2,5)}
        };

        return meta;
    }
};

} // namespace hlv
