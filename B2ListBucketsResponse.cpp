//
// Created by Oliver Albers on 25.11.15.
//

#include "B2ListBucketsResponse.h"

const std::vector<B2Bucket> B2ListBucketsResponse::getBuckets() const {
    return m_buckets;
}
