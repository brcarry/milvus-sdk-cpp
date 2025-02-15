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

#include <gtest/gtest.h>

#include "milvus/types/CollectionStat.h"
#include "milvus/types/Constant.h"

class CollectionStatTest : public ::testing::Test {};

TEST_F(CollectionStatTest, GeneralTesting) {
    milvus::CollectionStat stat;
    stat.SetName("test");
    EXPECT_EQ(stat.Name(), "test");
    EXPECT_EQ(stat.RowCount(), 0);
    stat.Emplace(milvus::KeyRowCount(), "1000");
    EXPECT_EQ(stat.RowCount(), 1000);
}
