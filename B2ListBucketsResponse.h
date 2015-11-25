//
// Created by Oliver Albers on 25.11.15.
//

#ifndef B2SYNC_B2LISTBUCKETSRESPONSE_H
#define B2SYNC_B2LISTBUCKETSRESPONSE_H


#include <vector>
#include "B2Bucket.h"

class B2ListBucketsResponse {
public:
    void AddBucket(const B2Bucket &bucket);
    const std::vector<B2Bucket> getBuckets() const;
private:
    std::vector<B2Bucket> m_buckets;
};


#endif //B2SYNC_B2LISTBUCKETSRESPONSE_H
