//
// Created by Oliver Albers on 25.11.15.
//

#include "B2ListBucketsResponse.h"

void B2ListBucketsResponse::AddBucket(const B2Bucket &bucket) {
    this->m_buckets.push_back(bucket);
}

const std::vector<B2Bucket> B2ListBucketsResponse::getBuckets() const {
    return m_buckets;
}
