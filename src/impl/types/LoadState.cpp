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

#include "milvus/types/LoadState.h"

namespace milvus {

LoadState::LoadState() : code_(LoadStateCode::NOT_EXIST) {
    updateStateDesc();
}

LoadState::LoadState(LoadStateCode code) : code_(code) {
    updateStateDesc();
}

LoadStateCode
LoadState::GetCode() const {
    return code_;
}

const std::string&
LoadState::GetDesc() const {
    return state_desc_;
}

void
LoadState::SetCode(LoadStateCode code) {
    code_ = code;
    updateStateDesc();
}

void
LoadState::updateStateDesc() {
    switch (code_) {
        case LoadStateCode::NOT_EXIST:
            state_desc_ = "NotExist";
            break;
        case LoadStateCode::NOT_LOAD:
            state_desc_ = "NotLoad";
            break;
        case LoadStateCode::LOADING:
            state_desc_ = "Loading";
            break;
        case LoadStateCode::LOADED:
            state_desc_ = "Loaded";
            break;
        default:
            state_desc_ = "Unknown";
    }
}

}  // namespace milvus
