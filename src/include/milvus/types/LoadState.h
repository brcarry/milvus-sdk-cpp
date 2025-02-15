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

#include <string>

namespace milvus {

enum class LoadStateCode { NOT_EXIST = 0, NOT_LOAD = 1, LOADING = 2, LOADED = 3 };

class LoadState {
 public:
    LoadState();
    explicit LoadState(LoadStateCode code);

    LoadStateCode
    GetCode() const;
    const std::string&
    GetDesc() const;
    void
    SetCode(LoadStateCode code);

 private:
    LoadStateCode code_;
    std::string state_desc_;
    void
    updateStateDesc();
};

}  // namespace milvus
