// Licensed to the LF AI & Data foundation under one
// or more contributor license agreements. See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership. The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License. You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <cstdint>
#include <vector>

namespace milvus {

/**
 * @brief 2-d array distances for CalcDistance(), each distance could be int type or float type.
 *
 * Note: std::vector<std::vector<int>> for "HAMMING" or std::vector<std::vector<float>> for others.
 */
class DistanceArray {
 public:
    DistanceArray() = default;

    explicit DistanceArray(std::vector<std::vector<int32_t>> distance_array)
        : int_array_(std::move(distance_array)), is_int_distance_{true} {
    }

    explicit DistanceArray(std::vector<std::vector<float>> distance_array) : float_array_(std::move(distance_array)) {
    }

    /**
     * @brief Test the distance is float or integer
     */
    bool
    IsIntegerDistance() const {
        return is_int_distance_;
    }

    /**
     * @brief Integer distance 2-d array
     *        Assume the vectors_left: L_1, L_2, L_3
     *        Assume the vectors_right: R_a, R_b
     *        Distance between L_n and R_m we called "D_n_m"
     *        The returned distances are arranged like this: [[D_1_a, D_1_b], [D_2_a, D_2_b], [D_3_a, D_3_b]]
     */
    const std::vector<std::vector<int32_t>>&
    IntDistanceArray() const {
        return int_array_;
    }

    /**
     * @brief Set integer distance array
     */
    void
    SetIntDistance(std::vector<std::vector<int32_t>>&& distance_array) {
        int_array_ = std::move(distance_array);
        float_array_.clear();
        is_int_distance_ = true;
    }

    /**
     * @brief Float distance 2-d array
     *        Assume the vectors_left: L_1, L_2, L_3
     *        Assume the vectors_right: R_a, R_b
     *        Distance between L_n and R_m we called "D_n_m"
     *        The returned distances are arranged like this: [[D_1_a, D_1_b], [D_2_a, D_2_b], [D_3_a, D_3_b]]
     */
    const std::vector<std::vector<float>>&
    FloatDistanceArray() const {
        return float_array_;
    }

    /**
     * @brief Set float distance array
     */
    void
    SetFloatDistance(std::vector<std::vector<float>>&& distance_array) {
        float_array_ = std::move(distance_array);
        int_array_.clear();
        is_int_distance_ = false;
    }

 private:
    bool is_int_distance_ = false;
    std::vector<std::vector<int32_t>> int_array_;
    std::vector<std::vector<float>> float_array_;
};

}  // namespace milvus