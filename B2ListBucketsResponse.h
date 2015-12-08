//
// Created by Oliver Albers on 25.11.15.
//

#ifndef B2SYNC_B2LISTBUCKETSRESPONSE_H
#define B2SYNC_B2LISTBUCKETSRESPONSE_H


#include <vector>
#include "B2Bucket.h"

class B2ListBucketsResponse {
public:
    B2ListBucketsResponse()  { this->m_buckets = std::vector<B2Bucket>(); }

    const std::vector<B2Bucket> getBuckets() const;
    const void addBucket(const B2Bucket &bucket) { m_buckets.push_back(bucket); };
private:
    std::vector<B2Bucket> m_buckets;
};


#endif //B2SYNC_B2LISTBUCKETSRESPONSE_H
