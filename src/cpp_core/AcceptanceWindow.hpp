#pragma once

#include "SimulationContext.hpp"
#include <Eigen/Dense>
#include <vector>
#include <string>
#include <cmath>
#include <stdexcept>
#include <nlohmann/json.hpp>

namespace hlv {

class AcceptanceWindow {
private:
    std::string window_type;

    // Ball / Polyhedral parameters
    double radius = 0.0;
    double radius_sq = 0.0;

    // Ellipsoid parameters
    double rx = 0.0, ry = 0.0, rz = 0.0;
    double rx_sq = 0.0, ry_sq = 0.0, rz_sq = 0.0;

    // Polyhedral geometry
    std::vector<Eigen::Vector3d> plane_normals;
    std::vector<double> plane_offsets;

    void initialize_polyhedral_geometry() {
        double tau = (1.0 + std::sqrt(5.0)) / 2.0;
        double inv_tau = 1.0 / tau;

        if (window_type == "dodecahedron") {
            plane_normals = {
                Eigen::Vector3d(0, 1, tau).normalized(),
                Eigen::Vector3d(0, 1, -tau).normalized(),
                Eigen::Vector3d(1, tau, 0).normalized(),
                Eigen::Vector3d(1, -tau, 0).normalized(),
                Eigen::Vector3d(tau, 0, 1).normalized(),
                Eigen::Vector3d(tau, 0, -1).normalized()
            };
        }
        else if (window_type == "icosahedron") {
            plane_normals = {
                Eigen::Vector3d(1, 1, 1).normalized(),
                Eigen::Vector3d(1, 1, -1).normalized(),
                Eigen::Vector3d(1, -1, 1).normalized(),
                Eigen::Vector3d(-1, 1, 1).normalized(),
                Eigen::Vector3d(0, inv_tau, tau).normalized(),
                Eigen::Vector3d(0, inv_tau, -tau).normalized(),
                Eigen::Vector3d(inv_tau, tau, 0).normalized(),
                Eigen::Vector3d(inv_tau, -tau, 0).normalized(),
                Eigen::Vector3d(tau, 0, inv_tau).normalized(),
                Eigen::Vector3d(tau, 0, -inv_tau).normalized()
            };
        }

        // All faces are offset by the same radius
        plane_offsets.assign(plane_normals.size(), radius);
    }

public:
    explicit AcceptanceWindow(const SimulationContext& ctx)
        : window_type(ctx.window_type)
    {
        if (window_type == "ball" || 
            window_type == "dodecahedron" || 
            window_type == "icosahedron") 
        {
            radius = ctx.window_parameters.at("radius");
            if (radius <= 0.0)
                throw std::invalid_argument("Window radius must be > 0.");

            radius_sq = radius * radius;

            if (window_type != "ball") {
                initialize_polyhedral_geometry();
            }
        }
        else if (window_type == "ellipsoid") {
            rx = ctx.window_parameters.at("rx");
            ry = ctx.window_parameters.at("ry");
            rz = ctx.window_parameters.at("rz");

            if (rx <= 0.0 || ry <= 0.0 || rz <= 0.0)
                throw std::invalid_argument("Ellipsoid radii must be > 0.");

            rx_sq = rx * rx;
            ry_sq = ry * ry;
            rz_sq = rz * rz;
        }
        else {
            throw std::invalid_argument("Unknown window_type: " + window_type);
        }
    }

    inline bool contains(const Eigen::Vector3d& v) const {
        if (window_type == "ball") {
            return v.squaredNorm() <= radius_sq;
        }
        else if (window_type == "ellipsoid") {
            double x = v.x(), y = v.y(), z = v.z();
            return (x*x)/rx_sq + (y*y)/ry_sq + (z*z)/rz_sq <= 1.0;
        }
        else {
            for (size_t i = 0; i < plane_normals.size(); ++i) {
                double d = v.dot(plane_normals[i]);
                double off = plane_offsets[i];
                if (d > off || d < -off)
                    return false;
            }
            return true;
        }
    }

    nlohmann::json get_geometry_metadata() const {
        nlohmann::json meta;
        meta["shape"] = window_type;

        if (window_type == "ball") {
            meta["radius"] = radius;
            meta["radius_sq"] = radius_sq;
        }
        else if (window_type == "ellipsoid") {
            meta["rx"] = rx; meta["ry"] = ry; meta["rz"] = rz;
            meta["rx_sq"] = rx_sq; meta["ry_sq"] = ry_sq; meta["rz_sq"] = rz_sq;
        }
        else {
            meta["radius"] = radius;
            meta["radius_sq"] = radius_sq;

            std::vector<std::vector<double>> normals;
            for (const auto& n : plane_normals)
                normals.push_back({n.x(), n.y(), n.z()});

            meta["plane_normals"] = normals;
            meta["plane_offsets"] = plane_offsets;
        }

        return meta;
    }
};

} // namespace hlv
