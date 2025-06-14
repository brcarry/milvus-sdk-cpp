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

#include <httplib.h>

#include <memory>

#include "Status.h"
#include "types/AliasDesc.h"
#include "types/AnnSearchRequest.h"
#include "types/CalcDistanceArguments.h"
#include "types/CollectionDesc.h"
#include "types/CollectionInfo.h"
#include "types/CollectionSchema.h"
#include "types/CollectionStat.h"
#include "types/CompactionPlan.h"
#include "types/CompactionState.h"
#include "types/ConnectParam.h"
#include "types/DatabaseDesc.h"
#include "types/DistanceArray.h"
#include "types/DmlResults.h"
#include "types/FieldData.h"
#include "types/GetArguments.h"
#include "types/HybridTimestamp.h"
#include "types/IndexDesc.h"
#include "types/IndexState.h"
#include "types/ListAliasesResult.h"
#include "types/LoadState.h"
#include "types/PartitionInfo.h"
#include "types/PartitionStat.h"
#include "types/PrivilegeGroupInfo.h"
#include "types/ProgressMonitor.h"
#include "types/QueryArguments.h"
#include "types/QueryResults.h"
#include "types/Ranker.h"
#include "types/ResourceGroupConfig.h"
#include "types/ResourceGroupDesc.h"
#include "types/RoleDesc.h"
#include "types/SearchArguments.h"
#include "types/SearchResults.h"
#include "types/SegmentInfo.h"
#include "types/UserResult.h"
#include "v2/request/ListCollectionsReq.h"
#include "v2/response/ListCollectionsResp.h"

/**
 *  @brief namespace milvus
 */
namespace milvus {

/**
 * @brief Milvus client abstract class, provide Create() method to create an implementation instance.
 */
class MilvusClientV2 {
 public:
    /**
     * Create a MilvusClientV2 instance.
     *
     * @return std::shared_ptr<MilvusClientV2>
     */
    static std::shared_ptr<MilvusClientV2>
    Create();

    /**
     * Connect to Milvus server.
     *
     * @param [in] connect_param server address and port
     * @return Status operation successfully or not
     */
    virtual Status
    Connect(const ConnectParam& connect_param) = 0;

    /**
     * Break connections between client and server.
     *
     * @return Status operation successfully or not
     */
    virtual Status
    Disconnect() = 0;

    /**
     * Get milvus server version
     *
     * @param [out] version version string
     * @return Status operation successfully or not
     *
     */
    virtual Status
    GetServerVersion(std::string& version) = 0;

    /**
     * Create a collection with schema.
     *
     * @param [in] schema schema of the collection
     * @return Status operation successfully or not
     */
    virtual Status
    CreateCollection(const CollectionSchema& schema) = 0;

    /**
     * Check existence of a collection.
     *
     * @param [in] collection_name name of the collection
     * @param [out] has true: collection exists, false: collection doesn't exist
     * @return Status operation successfully or not
     */
    virtual Status
    HasCollection(const std::string& collection_name, bool& has) = 0;

    /**
     * Drop a collection, with all its partitions, index and segments.
     *
     * @param [in] collection_name name of the collection
     * @return Status operation successfully or not
     */
    virtual Status
    DropCollection(const std::string& collection_name) = 0;

    virtual ListCollectionsResp ListCollections(const ListCollectionsReq& request) = 0;

    virtual Status
    GetLoadingProgress(const std::string& collection_name, int& progress,
                       const std::vector<std::string>& partition_names = {}, int timeout = 0,
                       bool is_refresh = false) = 0;

    virtual Status
    WaitForLoadingCollection(const std::string& collection_name, int timeout = 0, bool is_refresh = false) = 0;

    virtual Status
    LoadCollection(const std::string& collection_name, int replica_number = 1, bool refresh = false,
                   const std::string& resource_groups = "", const std::vector<std::string>& load_fields = {},
                   bool skip_load_dynamic_field = false, int timeout = 0) = 0;

    /**
     * Release collection data from query node.
     *
     * @param [in] collection_name name of the collection
     * @return Status operation successfully or not
     */
    virtual Status
    ReleaseCollection(const std::string& collection_name) = 0;

    /**
     * Get collection description, including its schema.
     *
     * @param [in] collection_name name of the collection
     * @param [out] collection_desc collection's description
     * @return Status operation successfully or not
     */
    virtual Status
    DescribeCollection(const std::string& collection_name, CollectionDesc& collection_desc) = 0;

    /**
     * RenameCollection rename a collection.
     *
     * @param [in] collection_name name of the collection
     * @param [in] new_collection_name new name of the collection
     * @return Status operation successfully or not
     */
    virtual Status
    RenameCollection(const std::string& collection_name, const std::string& new_collection_name) = 0;

    /**
     * Get collection statistics, currently only return row count. \n
     * If the timeout is specified, this api will call Flush() and wait all segments persisted into storage.
     *
     * @param [in] collection_name name of the collection
     * @param [out] collection_stat statistics of the collection
     * @return Status operation successfully or not
     */
    virtual Status
    GetCollectionStats(const std::string& collection_name, CollectionStat& collection_stat) = 0;

    /**
     * If the collection_names is empty, list all collections brief information's. \n
     * If the collection_names is specified, return the specified collection's loading process state.
     *
     * @param [in] collection_names name array of collections
     * @param [out] collections_info brief information's of the collections
     * @return Status operation successfully or not
     */
    virtual Status
    ShowCollections(const std::vector<std::string>& collection_names, CollectionsInfo& collections_info) = 0;

    virtual Status
    AlterCollectionProperties(const std::string& collection_name,
                              const std::vector<std::pair<std::string, std::string>>& properties, int timeout = 0) = 0;

    virtual Status
    DropCollectionProperties(const std::string& collection_name, const std::vector<std::string>& delete_keys,
                             int timeout = 0) = 0;

    virtual Status
    AlterCollectionField(const std::string& collection_name, const std::string& field_name,
                         const std::vector<std::pair<std::string, std::string>>& field_params,
                         const std::string& db_name = "", int timeout = 0) = 0;

    /**
     * Create a partition in a collection.
     *
     * @param [in] collection_name name of the collection
     * @param [in] partition_name name of the partition
     * @return Status operation successfully or not
     */
    virtual Status
    CreatePartition(const std::string& collection_name, const std::string& partition_name) = 0;

    /**
     * Drop a partition, with its index and segments.
     *
     * @param [in] collection_name name of the collection
     * @param [in] partition_name name of the partition
     * @return Status operation successfully or not
     */
    virtual Status
    DropPartition(const std::string& collection_name, const std::string& partition_name) = 0;

    virtual Status
    ListPartitions(const std::string& collection_name, std::vector<std::string>& results, int timeout = 0) = 0;

    /**
     * Check existence of a partition.
     *
     * @param [in] collection_name name of the collection
     * @param [in] partition_name name of the partition
     * @param [out] has true: partition exists, false: partition doesn't exist
     * @return Status operation successfully or not
     */
    virtual Status
    HasPartition(const std::string& collection_name, const std::string& partition_name, bool& has) = 0;

    virtual Status
    WaitForLoadingPartitions(const std::string& collection_name, const std::vector<std::string>& partition_names,
                             int timeout = 0) = 0;

    virtual Status
    LoadPartitions(const std::string& collection_name, const std::vector<std::string>& partition_names,
                   int replica_number = 1, bool refresh = false, const std::vector<std::string>& resource_groups = {},
                   const std::vector<std::string>& load_fields = {}, bool skip_load_dynamic_field = false,
                   int timeout = 0) = 0;

    /**
     * Release specific partitions data of one collection into query nodes.
     *
     * @param [in] collection_name name of the collection
     * @param [in] partition_names name array of the partitions
     * @return Status operation successfully or not
     */
    virtual Status
    ReleasePartitions(const std::string& collection_name, const std::vector<std::string>& partition_names,
                      int timeout = 0) = 0;

    /**
     * Get partition statistics, currently only return row count.
     * If the timeout is specified, this api will call Flush() and wait all segments persisted into storage. \n
     *
     * @param [in] collection_name name of the collection
     * @param [in] partition_name name of the partition
     * @param [out] partition_stat statistics of the partition
     * @return Status operation successfully or not
     */
    virtual Status
    GetPartitionStats(const std::string& collection_name, const std::string& partition_name,
                      PartitionStat& partition_stat) = 0;

    virtual Status
    GetLoadState(const std::string& collection_name, LoadState& state, const std::string& partition_name = "",
                 int timeout = 0) = 0;

    virtual Status
    GetLoadState(const std::string& collection_name, LoadState& state,
                 const std::vector<std::string>& partition_names = {}, int timeout = 0) = 0;

    virtual Status
    RefreshLoad(const std::string& collection_name, int timeout = 0) = 0;

    /**
     * If the partition_names is empty, list all partitions brief information's. \n
     * If the partition_names is specified, return the specified partition's loading process state.
     *
     * @param [in] collection_name name of the collection
     * @param [in] partition_names name array of the partitions
     * @param [out] partitions_info brief information's of the partitions
     * @return Status operation successfully or not
     */
    virtual Status
    ShowPartitions(const std::string& collection_name, const std::vector<std::string>& partition_names,
                   PartitionsInfo& partitions_info) = 0;

    /**
     * Create an alias for a collection. Alias can be used in search or query to replace the collection name. \n
     * For more information: https://wiki.lfaidata.foundation/display/MIL/MEP+10+--+Support+Collection+Alias
     *
     * @param [in] collection_name name of the collection
     * @param [in] alias alias of the partitions
     * @return Status operation successfully or not
     */
    virtual Status
    CreateAlias(const std::string& collection_name, const std::string& alias) = 0;

    /**
     * Drop an alias.
     *
     * @param [in] alias alias of the partitions
     * @return Status operation successfully or not
     */
    virtual Status
    DropAlias(const std::string& alias) = 0;

    /**
     * Change an alias from a collection to another.
     *
     * @param [in] collection_name name of the collection
     * @param [in] alias alias of the partitions
     * @return Status operation successfully or not
     */
    virtual Status
    AlterAlias(const std::string& collection_name, const std::string& alias) = 0;

    virtual Status
    ListAliases(const std::string& collection_name, ListAliasesResult& result, int timeout = 0) = 0;

    virtual Status
    DescribeAlias(const std::string& alias, AliasDesc& alias_desc, int timeout = 0) = 0;

    virtual Status
    UsingDatabase(const std::string& db_name) = 0;

    virtual Status
    CreateDatabase(const std::string& db_name, const std::vector<std::pair<std::string, std::string>>& properties = {},
                   int timeout = 0) = 0;

    virtual Status
    DropDatabase(const std::string& db_name, int timeout = 0) = 0;

    virtual Status
    ListDatabases(std::vector<std::string>& db_names, int timeout = 0) = 0;

    virtual Status
    DescribeDatabase(const std::string& db_name, DatabaseDesc& database_desc, int timeout = 0) = 0;

    virtual Status
    AlterDatabaseProperties(const std::string& db_name,
                            const std::vector<std::pair<std::string, std::string>>& properties, int timeout = 0) = 0;

    virtual Status
    DropDatabaseProperties(const std::string& db_name, const std::vector<std::string>& delete_keys,
                           int timeout = 0) = 0;

    virtual Status
    WaitForCreatingIndex(const std::string& collection_name, const std::string& field_name, int timeout = 0) = 0;

    /**
     * Create an index on a field. Currently only support index on vector field.
     *
     * @param [in] collection_name name of the collection
     * @param [in] index_desc the index descriptions and parameters
     * @return Status operation successfully or not
     */
    virtual Status
    CreateIndex(const std::string& collection_name, const IndexDesc& index_desc) = 0;

    /**
     * Get index descriptions and parameters.
     *
     * @param [in] collection_name name of the collection
     * @param [in] field_name name of the field
     * @param [out] index_desc index descriptions and parameters
     * @return Status operation successfully or not
     */
    virtual Status
    DescribeIndex(const std::string& collection_name, const std::string& field_name, IndexDesc& index_desc) = 0;

    /**
     * Get state of an index. From the state client can know whether the index has finished or in-progress.
     *
     * @param [in] collection_name name of the collection
     * @param [in] field_name name of the field
     * @param [out] state index state of field
     * @return Status operation successfully or not
     */
    virtual Status
    GetIndexState(const std::string& collection_name, const std::string& field_name, IndexState& state) = 0;

    /**
     * Get progress of an index. From the progress client can how many rows have been indexed.
     *
     * @param [in] collection_name name of the collection
     * @param [in] field_name name of the field
     * @param [out] progress progress array of field, currently only return one index progress
     * @return Status operation successfully or not
     */
    virtual Status
    GetIndexBuildProgress(const std::string& collection_name, const std::string& field_name,
                          IndexProgress& progress) = 0;

    /**
     * Drop index of a field.
     *
     * @param [in] collection_name name of the collection
     * @param [in] field_name name of the field
     * @return Status operation successfully or not
     */
    virtual Status
    DropIndex(const std::string& collection_name, const std::string& field_name) = 0;

    virtual Status
    ListIndexes(const std::string& collection_name, std::vector<std::string>& results,
                std::vector<std::string> field_names = {}) = 0;

    /**
     * Insert entities into a collection.
     *
     * @param [in] collection_name name of the collection
     * @param [in] partition_name name of the partition, optional(pass an empty string to skip)
     * @param [in] fields insert data
     * @param [out] results insert results
     * @return Status operation successfully or not
     */
    virtual Status
    Insert(const std::string& collection_name, const std::string& partition_name,
           const std::vector<FieldDataPtr>& fields, DmlResults& results) = 0;

    virtual Status
    Upsert(const std::string& collection_name, const std::string& partition_name,
           const std::vector<FieldDataPtr>& fields, DmlResults& results) = 0;

    /**
     * Delete entities by filtering condition.
     *
     * @param [in] collection_name name of the collection
     * @param [in] partition_name name of the partition, optional(pass an empty string to skip)
     * @param [in] expression the expression to filter out entities, currently only support primary key as filtering.
     * For example: "id in [1, 2, 3]"
     * @param [out] results insert results
     * @return Status operation successfully or not
     */
    virtual Status
    Delete(const std::string& collection_name, const std::string& partition_name, const std::string& expression,
           DmlResults& results) = 0;

    virtual Status
    HybridSearch(SearchResults& results, const std::string& collection_name, const std::vector<AnnSearchRequest>& reqs,
                 const BaseRanker& ranker, int limit, const std::vector<std::string>& partition_names = {},
                 const std::vector<std::string>& output_fields = {}, int round_decimal = -1,
                 const std::vector<std::pair<std::string, std::string>>& params = {}, int timeout = 0) = 0;

    /**
     * Search a collection based on the given parameters and return results.
     *
     * @param [in] arguments search arguments
     * @param [out] results search results
     * @param [in] timeout search timeout in milliseconds
     * @return Status operation successfully or not
     */
    virtual Status
    Search(const SearchArguments& arguments, SearchResults& results, int timeout = 0) = 0;

    /**
     * Query with a set of criteria, and results in a list of records that match the query exactly.
     *
     * @param [in] arguments query arguments
     * @param [out] results query results
     * @param [in] timeout search timeout in milliseconds
     * @return Status operation successfully or not
     */
    virtual Status
    Query(const QueryArguments& arguments, QueryResults& results, int timeout = 0) = 0;

    virtual Status
    Get(const GetArguments& arguments, QueryResults& results, int timeout = 0) = 0;

    virtual Status
    ListUsers(std::vector<std::string>& results, int timeout = 0) = 0;

    virtual Status
    DescribeUser(const std::string& username, UserResult& results, int timeout = 0) = 0;

    virtual Status
    CreateUser(const std::string& username, const std::string& password, int timeout = 0) = 0;

    virtual Status
    UpdatePassword(const std::string& username, const std::string& old_password, const std::string& new_password,
                   bool reset_connection = false, int timeout = 0) = 0;

    virtual Status
    DropUser(const std::string& username, int timeout = 0) = 0;

    virtual Status
    CreateRole(const std::string& role_name, int timeout = 0) = 0;

    virtual Status
    DropRole(const std::string& role_name, int timeout = 0) = 0;

    virtual Status
    GrantRole(const std::string& username, const std::string& role_name, int timeout = 0) = 0;

    virtual Status
    RevokeRole(const std::string& username, const std::string& role_name, int timeout = 0) = 0;

    virtual Status
    DescribeRole(const std::string& role_name, RoleDesc& role_desc, int timeout = 0) = 0;

    virtual Status
    ListRoles(std::vector<std::string>& roles, int timeout = 0) = 0;

    virtual Status
    GrantPrivilege(const std::string& role_name, const std::string& object_type, const std::string& privilege,
                   const std::string& object_name, const std::string& db_name = "", int timeout = 0) = 0;

    virtual Status
    RevokePrivilege(const std::string& role_name, const std::string& object_type, const std::string& privilege,
                    const std::string& object_name, const std::string& db_name = "", int timeout = 0) = 0;

    virtual Status
    CreatePrivilegeGroup(const std::string& group_name, int timeout = 0) = 0;

    virtual Status
    DropPrivilegeGroup(const std::string& group_name, int timeout = 0) = 0;

    virtual Status
    ListPrivilegeGroups(std::vector<PrivilegeGroupInfo>& privilege_groups, int timeout = 0) = 0;

    virtual Status
    AddPrivilegesToGroup(const std::string& group_name, const std::vector<std::string>& privileges,
                         int timeout = 0) = 0;

    virtual Status
    RemovePrivilegesFromGroup(const std::string& group_name, const std::vector<std::string>& privileges,
                              int timeout = 0) = 0;

    virtual Status
    GrantPrivilegeV2(const std::string& role_name, const std::string& privilege, const std::string& collection_name,
                     const std::string& db_name = "", int timeout = 0) = 0;

    virtual Status
    RevokePrivilegeV2(const std::string& role_name, const std::string& privilege, const std::string& collection_name,
                      const std::string& db_name = "", int timeout = 0) = 0;

    virtual Status
    CreateResourceGroup(const std::string& resource_group, const ResourceGroupConfig& config, int timeout = 0) = 0;

    virtual Status
    DropResourceGroup(const std::string& resource_group, int timeout = 0) = 0;

    virtual Status
    DescribeResourceGroup(const std::string& resource_group, ResourceGroupDesc& resource_group_desc,
                          int timeout = 0) = 0;

    virtual Status
    ListResourceGroups(std::vector<std::string>& resource_groups, int timeout = 0) = 0;

    virtual Status
    UpdateResourceGroup(const std::string& resource_group, const ResourceGroupConfig& config, int timeout = 0) = 0;

    virtual Status
    WaitForFlushing(const std::map<std::string, std::vector<int64_t>>& collection_segments, int timeout = 0) = 0;

    /**
     * Flush insert buffer into storage.  \n
     * To make sure the buffer persisted successfully, it calls GetFlushState() to check related segments state.
     *
     * @param [in] collection_names specify target collection names, if this array is empty, will flush all collections
     * @param [in] progress_monitor timeout setting for waiting progress. Set ProgressMonitor::NoWait() to return
     * instantly, set to ProgressMonitor::Forever() to wait until finished.
     * @return Status operation successfully or not
     */
    virtual Status
    Flush(const std::vector<std::string>& collection_names) = 0;

    /**
     * Get flush state of specified segments.
     *
     * @param [in] segments id array of segments
     * @param [out] flushed true: all the segments has been flushed, false: still in flush progress
     * @return Status operation successfully or not
     */
    virtual Status
    GetFlushState(const std::vector<int64_t>& segments, bool& flushed) = 0;

    /**
     * Retrieve information of persistent segments from data nodes.
     *
     * @param [in] collection_name name of the collection
     * @param [out] segments_info information array for persistent segments
     * @return Status operation successfully or not
     */
    virtual Status
    GetPersistentSegmentInfo(const std::string& collection_name, SegmentsInfo& segments_info) = 0;

    /**
     * Retrieve information of segments from query nodes.
     *
     * @param [in] collection_name name of the collection
     * @param [out] segments_info information array for segments
     * @return Status operation successfully or not
     */
    virtual Status
    GetQuerySegmentInfo(const std::string& collection_name, QuerySegmentsInfo& segments_info) = 0;

    /**
     * Get server runtime statistics.
     *
     * @param [in] request request in json format
     * @param [out] response response in json format
     * @param [out] component_name metrics from which component
     * @return Status operation successfully or not
     */
    virtual Status
    GetMetrics(const std::string& request, std::string& response, std::string& component_name) = 0;

    /**
     * Rebalanced sealed segments from one query node to others.
     *
     * @param [in] src_node the source query node id
     * @param [in] dst_nodes the destiny query nodes id array
     * @param [in] segments the segments id array to be balanced
     * @return Status operation successfully or not
     */
    virtual Status
    LoadBalance(int64_t src_node, const std::vector<int64_t>& dst_nodes, const std::vector<int64_t>& segments) = 0;

    virtual Status
    Compact(const std::string& collection_name, int64_t& compaction_id, bool is_clustering = false,
            int timeout = 0) = 0;

    /**
     * Get compaction action state.
     *
     * @param [in] compaction_id the compaction action id
     * @param [out] compaction_state state of the compaction action
     * @return Status operation successfully or not
     */
    virtual Status
    GetCompactionState(int64_t compaction_id, CompactionState& compaction_state) = 0;

    /**
     * Manually trigger a compaction action.
     *
     * @param [in] collection_name name of the collection
     * @param [in] travel_timestamp specify a timestamp to compact on a data view at a specified point in time.
     * @param [out] compaction_id id of the compaction action
     * @return Status operation successfully or not
     */
    virtual Status
    ManualCompaction(const std::string& collection_name, uint64_t travel_timestamp, int64_t& compaction_id) = 0;

    /**
     * Get plans of a compaction action.
     *
     * @param [in] compaction_id the compaction action id
     * @param [out] plans compaction plan array
     * @return Status operation successfully or not
     */
    virtual Status
    GetCompactionPlans(int64_t compaction_id, CompactionPlans& plans) = 0;

    /**
     * Create Credential
     *
     * @param [in] username the username for created
     * @param [in] password the password for the user to be created
     * @return Status operation successfully or not
     */
    virtual Status
    CreateCredential(const std::string& username, const std::string& password) = 0;

    /**
     * Update Credential
     *
     * @param [in] username the username for updated
     * @param [in] old_password the old password for the user
     * @param [in] new_password the updated password for the user
     * @return Status operation successfully or not
     */
    virtual Status
    UpdateCredential(const std::string& username, const std::string& old_password, const std::string& new_password) = 0;

    /**
     * Delete Credential
     *
     * @param [in] username the username to be deleted
     * @return Status operation successfully or not
     */
    virtual Status
    DeleteCredential(const std::string& username) = 0;

    /**
     * List Users
     *
     * @param [out] the usernames
     * @return Status operation successfully or not
     */
    virtual Status
    ListCredUsers(std::vector<std::string>& names) = 0;
};

}  // namespace milvus
