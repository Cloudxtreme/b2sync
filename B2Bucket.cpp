//
// Created by Oliver Albers on 25.11.15.
//

#include "B2Bucket.h"

B2Bucket::B2Bucket(const std::string &accountId, const std::string &id, const std::string &name,
                   const std::string &buckettype) :
        m_accountId(accountId), m_id(id), m_name(name), m_buckettype(buckettype)
{

}

B2Bucket::B2Bucket(const boost::property_tree::ptree &ptree) {
    m_accountId = ptree.get<std::string>("accountId");
    m_id = ptree.get<std::string>("bucketId");
    m_name = ptree.get<std::string>("bucketName");
    m_buckettype = ptree.get<std::string>("bucketType");
}

const std::string B2Bucket::TYPE_PUBLIC = "allPublic";
const std::string B2Bucket::TYPE_PRIVATE = "allPrivate";