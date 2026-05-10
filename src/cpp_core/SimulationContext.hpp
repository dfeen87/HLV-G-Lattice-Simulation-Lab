/*
 * HLV-G-Lattice-Simulation-Lab
 * 
 * Copyright (c) 2026 Don Michael Feeney Jr., Marcel Krüger
 * SPDX-License-Identifier: MIT
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 */

#pragma once

#include <string>
#include <map>
#include <vector>
#include <cstdint>
#include <fstream>
#include <stdexcept>
#include <filesystem>
#include <nlohmann/json.hpp>

namespace hlv {

class SimulationContext {
public:
    // 1. Core Run Identification
    const std::string run_id;
    const std::string timestamp;
    const std::string git_commit_hash;
    
    // 2. System & Environment
    const std::string compiler_info;
    const std::string platform_info;

    // 3. Mathematical & Generation Parameters
    const uint64_t master_seed;
    const std::string projection_matrix_id; 
    const std::string window_type;
    const std::map<std::string, double> window_parameters;
    
    // 4. Output Configuration
    const std::string output_directory;

    SimulationContext(
        std::string id, std::string time, std::string commit,
        std::string compiler, std::string platform,
        uint64_t seed, std::string matrix_id, std::string win_type,
        std::map<std::string, double> win_params, std::string out_dir
    ) : run_id(std::move(id)), timestamp(std::move(time)), 
        git_commit_hash(std::move(commit)), compiler_info(std::move(compiler)), 
        platform_info(std::move(platform)), master_seed(seed), 
        projection_matrix_id(std::move(matrix_id)), window_type(std::move(win_type)), 
        window_parameters(std::move(win_params)), output_directory(std::move(out_dir)) {}

    // Export metadata with atomic write + directory creation
    void export_metadata() const {
        namespace fs = std::filesystem;

        // Ensure output directory exists
        fs::create_directories(output_directory);

        // Build JSON explicitly
        nlohmann::json metadata;
        metadata["run_id"] = run_id;
        metadata["timestamp"] = timestamp;
        metadata["git_commit_hash"] = git_commit_hash;

        metadata["environment"] = {
            {"compiler", compiler_info},
            {"platform", platform_info}
        };

        nlohmann::json win_params_json = nlohmann::json::object();
        for (const auto& [key, value] : window_parameters) {
            win_params_json[key] = value;
        }

        metadata["generation_parameters"] = {
            {"master_seed", master_seed},
            {"projection_matrix_id", projection_matrix_id},
            {"window_type", window_type},
            {"window_parameters", win_params_json}
        };

        const std::string filepath = output_directory + "/" + run_id + "_metadata.json";
        const std::string tmp_path = filepath + ".tmp";

        // Write to temp file first
        {
            std::ofstream tmp(tmp_path, std::ios::trunc);
            if (!tmp.is_open()) {
                throw std::runtime_error("Failed to open temp metadata file: " + tmp_path);
            }
            tmp << metadata.dump(4);
        }

        // Atomic replace
        fs::rename(tmp_path, filepath);
    }
};

} // namespace hlv
