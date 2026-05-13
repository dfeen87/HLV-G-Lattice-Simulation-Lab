/*
 * HLV G-Lattice Simulation Lab
 * Licensed under the MIT License
 * * Standalone Bare-Metal Benchmark: 6D-to-3D Generation Stress Test
 */

#include <iostream>
#include <vector>
#include <unordered_set>
#include <chrono>
#include <cmath>
#include <iomanip>

// 6D Integer Lattice Point
struct HLVNode {
    double x, y, z;      // Physical Space E_||
    double ux, uy, uz;   // Internal Space E_perp
    uint32_t id;

    // Deduplication check based on physical coordinates
    bool operator==(const HLVNode& other) const {
        return std::abs(x - other.x) < 1e-9 && 
               std::abs(y - other.y) < 1e-9 && 
               std::abs(z - other.z) < 1e-9;
    }
};

struct NodeHasher {
    size_t operator()(const HLVNode& n) const {
        return std::hash<double>{}(std::round(n.x * 1e6)) ^ 
              (std::hash<double>{}(std::round(n.y * 1e6)) << 1) ^ 
              (std::hash<double>{}(std::round(n.z * 1e6)) << 2);
    }
};

class HLVSolidEngine {
    // 6D-to-3D Quasicrystalline Projection Constants
    const double phi = (1.0 + std::sqrt(5.0)) / 2.0;
    const double norm = 1.0 / std::sqrt(2.0 * (2.0 + phi));

    // Projection Matrices P_parallel and P_perp
    const double P_parallel[3][6] = {
        {phi, 0, 1, -phi, 0, 1},
        {1, phi, 0, 1, -phi, 0},
        {0, 1, phi, 0, 1, -phi}
    };

    const double P_perp[3][6] = {
        {1, phi, 0, -1, phi, 0},
        {0, 1, phi, 0, -1, phi},
        {phi, 0, 1, phi, 0, -1}
    };

public:
    void generate(int target_nodes, int R6_limit) {
        std::vector<HLVNode> lattice;
        std::unordered_set<HLVNode, NodeHasher> deduplicator;

        long long parent_points_sampled = 0;
        const double window_radius_sq = 1.2; // Acceptance Window W_ball

        std::cout << "Starting HLV Solid Engine: Target " << target_nodes << " Nodes..." << std::endl;
        auto start = std::chrono::high_resolution_clock::now();

        // High-speed 6D Enumeration
        for (int n1 = -R6_limit; n1 <= R6_limit; ++n1) {
        for (int n2 = -R6_limit; n2 <= R6_limit; ++n2) {
        for (int n3 = -R6_limit; n3 <= R6_limit; ++n3) {
        for (int n4 = -R6_limit; n4 <= R6_limit; ++n4) {
        for (int n5 = -R6_limit; n5 <= R6_limit; ++n5) {
        for (int n6 = -R6_limit; n6 <= R6_limit; ++n6) {

            parent_points_sampled++;
            int p[6] = {n1, n2, n3, n4, n5, n6};

            // 1. Compute Internal Projection (Acceptance Check)
            double ux = 0, uy = 0, uz = 0;
            for(int i=0; i<6; ++i) {
                ux += P_perp[0][i] * p[i] * norm;
                uy += P_perp[1][i] * p[i] * norm;
                uz += P_perp[2][i] * p[i] * norm;
            }

            if ((ux*ux + uy*uy + uz*uz) <= window_radius_sq) {

                // 2. Compute Physical Projection (Physical Coordinates)
                double px = 0, py = 0, pz = 0;
                for(int i=0; i<6; ++i) {
                    px += P_parallel[0][i] * p[i] * norm;
                    py += P_parallel[1][i] * p[i] * norm;
                    pz += P_parallel[2][i] * p[i] * norm;
                }

                HLVNode newNode{px, py, pz, ux, uy, uz, (uint32_t)lattice.size()};

                if (deduplicator.find(newNode) == deduplicator.end()) {
                    lattice.push_back(newNode);
                    deduplicator.insert(newNode);
                }
            }

            if (lattice.size() >= (size_t)target_nodes) goto finish;
        }}}}}}

    finish:
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;

        std::cout << "\n==========================================" << std::endl;
        std::cout << "   HLV SOLID ENGINE BENCHMARK REPORT" << std::endl;
        std::cout << "==========================================" << std::endl;
        std::cout << "Accepted Nodes:        " << lattice.size() << std::endl;
        std::cout << "Runtime:               " << std::fixed << std::setprecision(4) << elapsed.count() << " seconds" << std::endl;
        std::cout << "Parent Points Sampled: " << parent_points_sampled << std::endl;
        std::cout << "Acceptance Fraction:   " << (double)lattice.size()/parent_points_sampled << std::endl;
        std::cout << "==========================================" << std::endl;
    }
};

int main() {
    HLVSolidEngine engine;
    // We use a high R6_limit to ensure we find 1M points
    engine.generate(1000000, 22); 
    return 0;
}
