//
// Created by Oliver Albers on 25.11.15.
//

#include "B2Bucket.h"

B2Bucket::B2Bucket(const std::string &accountId, const std::string &id, const std::string &name,
                   const std::string &buckettype) :
        m_accountId(accountId), m_id(id), m_name(name), m_buckettype(buckettype)
{

}
