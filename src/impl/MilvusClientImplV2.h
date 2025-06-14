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

#include <memory>

#include "MilvusConnection.h"
#include "milvus/MilvusClientV2.h"

/**
 *  @brief namespace milvus
 */
namespace milvus {

class MilvusClientImplV2 : public MilvusClientV2 {
 public:
    MilvusClientImplV2() = default;
    virtual ~MilvusClientImplV2();

    Status
    Connect(const ConnectParam& connect_param) final;

    Status
    Disconnect() final;

    Status
    GetServerVersion(std::string& version) final;

    Status
    CreateCollection(const CollectionSchema& schema) final;

    Status
    HasCollection(const std::string& collection_name, bool& has) final;

    Status
    DropCollection(const std::string& collection_name) final;

    ListCollectionsResp
    ListCollections(const ListCollectionsReq& request) final;

    Status
    GetLoadingProgress(const std::string& collection_name, int& progress,
                       const std::vector<std::string>& partition_names, int timeout, bool is_refresh) final;

    Status
    WaitForLoadingCollection(const std::string& collection_name, int timeout, bool is_refresh) final;

    Status
    LoadCollection(const std::string& collection_name, int replica_number, bool refresh,
                   const std::string& resource_groups, const std::vector<std::string>& load_fields,
                   bool skip_load_dynamic_field, int timeout) final;

    Status
    ReleaseCollection(const std::string& collection_name) final;

    Status
    DescribeCollection(const std::string& collection_name, CollectionDesc& collection_desc) final;

    Status
    RenameCollection(const std::string& collection_name, const std::string& new_collection_name) final;

    Status
    GetCollectionStats(const std::string& collection_name, CollectionStat& collection_stat) final;

    Status
    ShowCollections(const std::vector<std::string>& collection_names, CollectionsInfo& collections_info) final;

    Status
    AlterCollectionProperties(const std::string& collection_name,
                              const std::vector<std::pair<std::string, std::string>>& properties, int timeout) final;

    Status
    DropCollectionProperties(const std::string& collection_name, const std::vector<std::string>& delete_keys,
                             int timeout) final;

    Status
    AlterCollectionField(const std::string& collection_name, const std::string& field_name,
                         const std::vector<std::pair<std::string, std::string>>& field_params,
                         const std::string& db_name, int timeout) final;

    Status
    CreatePartition(const std::string& collection_name, const std::string& partition_name) final;

    Status
    DropPartition(const std::string& collection_name, const std::string& partition_name) final;

    Status
    ListPartitions(const std::string& collection_name, std::vector<std::string>& results, int timeout) final;

    Status
    HasPartition(const std::string& collection_name, const std::string& partition_name, bool& has) final;

    // Status
    // LoadPartitions(const std::string& collection_name, const std::vector<std::string>& partition_names,
    //                int replica_number, const ProgressMonitor& progress_monitor) final;

    Status
    WaitForLoadingPartitions(const std::string& collection_name, const std::vector<std::string>& partition_names,
                             int timeout) final;

    Status
    LoadPartitions(const std::string& collection_name, const std::vector<std::string>& partition_names,
                   int replica_number, bool refresh, const std::vector<std::string>& resource_groups,
                   const std::vector<std::string>& load_fields, bool skip_load_dynamic_field, int timeout) final;

    Status
    ReleasePartitions(const std::string& collection_name, const std::vector<std::string>& partition_names,
                      int timeout) final;

    Status
    GetPartitionStats(const std::string& collection_name, const std::string& partition_name,
                      PartitionStat& partition_stat) final;

    Status
    ShowPartitions(const std::string& collection_name, const std::vector<std::string>& partition_names,
                   PartitionsInfo& partitions_info) final;

    Status
    GetLoadState(const std::string& collection_name, LoadState& state, const std::string& partition_name,
                 int timeout) final;

    Status
    GetLoadState(const std::string& collection_name, LoadState& state, const std::vector<std::string>& partition_names,
                 int timeout) final;

    Status
    RefreshLoad(const std::string& collection_name, int timeout) final;

    Status
    CreateAlias(const std::string& collection_name, const std::string& alias) final;

    Status
    DropAlias(const std::string& alias) final;

    Status
    AlterAlias(const std::string& collection_name, const std::string& alias) final;

    Status
    ListAliases(const std::string& collection_name, ListAliasesResult& result, int timeout) final;

    Status
    DescribeAlias(const std::string& alias, AliasDesc& alias_desc, int timeout) final;

    Status
    UsingDatabase(const std::string& db_name) final;

    Status
    CreateDatabase(const std::string& db_name, const std::vector<std::pair<std::string, std::string>>& properties,
                   int timeout) final;

    Status
    DropDatabase(const std::string& db_name, int timeout) final;

    Status
    ListDatabases(std::vector<std::string>& db_names, int timeout) final;

    Status
    DescribeDatabase(const std::string& db_name, DatabaseDesc& database_desc, int timeout) final;

    Status
    AlterDatabaseProperties(const std::string& db_name,
                            const std::vector<std::pair<std::string, std::string>>& properties, int timeout) final;

    Status
    DropDatabaseProperties(const std::string& db_name, const std::vector<std::string>& delete_keys, int timeout) final;

    Status
    WaitForCreatingIndex(const std::string& collection_name, const std::string& field_name, int timeout) final;

    Status
    CreateIndex(const std::string& collection_name, const IndexDesc& index_desc) final;

    Status
    DescribeIndex(const std::string& collection_name, const std::string& field_name, IndexDesc& index_desc) final;

    Status
    GetIndexState(const std::string& collection_name, const std::string& field_name, IndexState& state) final;

    Status
    GetIndexBuildProgress(const std::string& collection_name, const std::string& field_name,
                          IndexProgress& progress) final;

    Status
    DropIndex(const std::string& collection_name, const std::string& field_name) final;

    Status
    ListIndexes(const std::string& collection_name, std::vector<std::string>& results,
                std::vector<std::string> field_names) final;

    Status
    Insert(const std::string& collection_name, const std::string& partition_name,
           const std::vector<FieldDataPtr>& fields, DmlResults& results) final;

    Status
    Upsert(const std::string& collection_name, const std::string& partition_name,
           const std::vector<FieldDataPtr>& fields, DmlResults& results) final;

    Status
    Delete(const std::string& collection_name, const std::string& partition_name, const std::string& expression,
           DmlResults& results) final;

    Status
    HybridSearch(SearchResults& results, const std::string& collection_name, const std::vector<AnnSearchRequest>& reqs,
                 const BaseRanker& ranker, int limit, const std::vector<std::string>& partition_names,
                 const std::vector<std::string>& output_fields, int round_decimal,
                 const std::vector<std::pair<std::string, std::string>>& params, int timeout) final;

    Status
    Search(const SearchArguments& arguments, SearchResults& results, int timeout) final;

    Status
    Query(const QueryArguments& arguments, QueryResults& results, int timeout) final;

    Status
    Get(const GetArguments& arguments, QueryResults& results, int timeout) final;

    Status
    ListUsers(std::vector<std::string>& results, int timeout) final;

    Status
    DescribeUser(const std::string& username, UserResult& results, int timeout) final;

    Status
    CreateUser(const std::string& username, const std::string& password, int timeout) final;

    Status
    UpdatePassword(const std::string& username, const std::string& old_password, const std::string& new_password,
                   bool reset_connection, int timeout) final;

    Status
    DropUser(const std::string& username, int timeout) final;

    Status
    CreateRole(const std::string& role_name, int timeout) final;

    Status
    DropRole(const std::string& role_name, int timeout) final;

    Status
    GrantRole(const std::string& username, const std::string& role_name, int timeout) final;

    Status
    RevokeRole(const std::string& username, const std::string& role_name, int timeout) final;

    Status
    DescribeRole(const std::string& role_name, RoleDesc& role_desc, int timeout) final;

    Status
    ListRoles(std::vector<std::string>& roles, int timeout) final;

    Status
    GrantPrivilege(const std::string& role_name, const std::string& object_type, const std::string& privilege,
                   const std::string& object_name, const std::string& db_name, int timeout) final;

    Status
    RevokePrivilege(const std::string& role_name, const std::string& object_type, const std::string& privilege,
                    const std::string& object_name, const std::string& db_name, int timeout) final;

    Status
    CreatePrivilegeGroup(const std::string& group_name, int timeout) final;

    Status
    DropPrivilegeGroup(const std::string& group_name, int timeout) final;

    Status
    ListPrivilegeGroups(std::vector<PrivilegeGroupInfo>& privilege_groups, int timeout) final;

    Status
    AddPrivilegesToGroup(const std::string& group_name, const std::vector<std::string>& privileges, int timeout) final;

    Status
    RemovePrivilegesFromGroup(const std::string& group_name, const std::vector<std::string>& privileges,
                              int timeout) final;

    Status
    GrantPrivilegeV2(const std::string& role_name, const std::string& privilege, const std::string& collection_name,
                     const std::string& db_name, int timeout) final;

    Status
    RevokePrivilegeV2(const std::string& role_name, const std::string& privilege, const std::string& collection_name,
                      const std::string& db_name, int timeout) final;

    Status
    CreateResourceGroup(const std::string& resource_group, const ResourceGroupConfig& config, int timeout) final;

    Status
    DropResourceGroup(const std::string& resource_group, int timeout) final;

    Status
    DescribeResourceGroup(const std::string& resource_group, ResourceGroupDesc& resource_group_desc,
                          int timeout = 0) final;

    Status
    ListResourceGroups(std::vector<std::string>& resource_groups, int timeout) final;

    Status
    UpdateResourceGroup(const std::string& resource_group, const ResourceGroupConfig& config, int timeout) final;

    Status
    WaitForFlushing(const std::map<std::string, std::vector<int64_t>>& collection_segments, int timeout) final;

    Status
    Flush(const std::vector<std::string>& collection_names) final;

    Status
    GetFlushState(const std::vector<int64_t>& segments, bool& flushed) final;

    Status
    GetPersistentSegmentInfo(const std::string& collection_name, SegmentsInfo& segments_info) final;

    Status
    GetQuerySegmentInfo(const std::string& collection_name, QuerySegmentsInfo& segments_info) final;

    Status
    GetMetrics(const std::string& request, std::string& response, std::string& component_name) final;

    Status
    LoadBalance(int64_t src_node, const std::vector<int64_t>& dst_nodes, const std::vector<int64_t>& segments) final;

    Status
    Compact(const std::string& collection_name, int64_t& compaction_id, bool is_clustering, int timeout) final;

    Status
    GetCompactionState(int64_t compaction_id, CompactionState& compaction_state) final;

    Status
    ManualCompaction(const std::string& collection_name, uint64_t travel_timestamp, int64_t& compaction_id) final;

    Status
    GetCompactionPlans(int64_t compaction_id, CompactionPlans& plans) final;

    Status
    CreateCredential(const std::string& username, const std::string& password) final;

    Status
    UpdateCredential(const std::string& username, const std::string& old_password,
                     const std::string& new_password) final;

    Status
    DeleteCredential(const std::string& username) final;

    Status
    ListCredUsers(std::vector<std::string>& users) final;

 private:
    using GrpcOpts = MilvusConnection::GrpcContextOptions;

    /**
     * Internal wait for status query done.
     *
     * @param [in] query_function one time query for return Status, return TIMEOUT status if not done
     * @param [in] progress_monitor timeout setting for waiting progress
     * @return Status, the final status
     */
    static Status
    WaitForStatus(const std::function<Status(Progress&)>& query_function, const ProgressMonitor& progress_monitor);

    /**
     * @brief template for public api call
     *        validate -> pre -> rpc -> wait_for_status -> post
     */
    template <typename Request, typename Response>
    Status
    apiHandler(const std::function<Status(void)>& validate, std::function<Request(void)> pre,
               Status (MilvusConnection::*rpc)(const Request&, Response&, const GrpcOpts&),
               std::function<Status(const Response&)> wait_for_status, std::function<void(const Response&)> post,
               const GrpcOpts& options = GrpcOpts{}) {
        if (connection_ == nullptr) {
            return {StatusCode::NOT_CONNECTED, "Connection is not ready!"};
        }

        if (validate) {
            auto status = validate();
            if (!status.IsOk()) {
                return status;
            }
        }

        Request rpc_request = pre();
        Response rpc_response;
        auto status = std::bind(rpc, connection_.get(), std::placeholders::_1, std::placeholders::_2,
                                std::placeholders::_3)(rpc_request, rpc_response, options);
        if (!status.IsOk()) {
            // response's status already checked in connection class
            return status;
        }

        if (wait_for_status) {
            status = wait_for_status(rpc_response);
        }

        if (status.IsOk() && post) {
            post(rpc_response);
        }
        return status;
    }

    /**
     * @brief template for public api call
     */
    template <typename Request, typename Response>
    Status
    apiHandler(std::function<Status(void)> validate, std::function<Request(void)> pre,
               Status (MilvusConnection::*rpc)(const Request&, Response&, const GrpcOpts&),
               std::function<void(const Response&)> post, const GrpcOpts& options = GrpcOpts{}) {
        return apiHandler(validate, pre, rpc, std::function<Status(const Response&)>{}, post, options);
    }

    /**
     * @brief template for public api call
     */
    template <typename Request, typename Response>
    Status
    apiHandler(std::function<Status(void)> validate, std::function<Request(void)> pre,
               Status (MilvusConnection::*rpc)(const Request&, Response&, const GrpcOpts&),
               const GrpcOpts& options = GrpcOpts{}) {
        return apiHandler(validate, pre, rpc, std::function<Status(const Response&)>{},
                          std::function<void(const Response&)>{}, options);
    }

    /**
     * @brief template for public api call
     */
    template <typename Request, typename Response>
    Status
    apiHandler(std::function<Request(void)> pre,
               Status (MilvusConnection::*rpc)(const Request&, Response&, const GrpcOpts&),
               std::function<void(const Response&)> post, const GrpcOpts& options = GrpcOpts{}) {
        return apiHandler(std::function<Status(void)>{}, pre, rpc, std::function<Status(const Response&)>{}, post,
                          options);
    }

    /**
     * @brief template for public api call
     */
    template <typename Request, typename Response>
    Status
    apiHandler(std::function<Request(void)> pre,
               Status (MilvusConnection::*rpc)(const Request&, Response&, const GrpcOpts&),
               const GrpcOpts& options = GrpcOpts{}) {
        return apiHandler(std::function<Status(void)>{}, pre, rpc, std::function<Status(const Response&)>{},
                          std::function<void(const Response&)>{}, options);
    }

    const FieldSchema*
    extractPrimaryField(const CollectionSchema& schema) {
        const auto& fields = schema.Fields();
        for (const auto& field : fields) {
            if (field.IsPrimaryKey()) {
                return &field;
            }
        }
        return nullptr;
    }

    std::string
    packPksExpr(const CollectionSchema& schema, const std::vector<int64_t>& pks) {
        auto primary_field = extractPrimaryField(schema);
        if (primary_field == nullptr) {
            return "";
        }

        std::string expr = primary_field->Name() + " in [";

        if (primary_field->FieldDataType() == DataType::VARCHAR) {
            for (size_t i = 0; i < pks.size(); i++) {
                if (i > 0) {
                    expr += ",";
                }
                expr += "'" + std::to_string(pks[i]) + "'";
            }
        } else {
            for (size_t i = 0; i < pks.size(); i++) {
                if (i > 0) {
                    expr += ",";
                }
                expr += std::to_string(pks[i]);
            }
        }

        expr += "]";
        return expr;
    }

 private:
    std::shared_ptr<MilvusConnection> connection_;
};

}  // namespace milvus
