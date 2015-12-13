//
// Created by Oliver Albers on 25.11.15.
//

#ifndef B2SYNC_B2BUCKET_H
#define B2SYNC_B2BUCKET_H

#include <string>
#include <boost/property_tree/ptree.hpp>

class B2Bucket {
public:
    B2Bucket(const std::string &accountId, const std::string &id, const std::string &name, const std::string &buckettype);
    B2Bucket(const boost::property_tree::ptree &ptree);

    const std::string &getAccountId() const {
        return m_accountId;
    }

    const std::string &getId() const {
        return m_id;
    }

    const std::string &getName() const {
        return m_name;
    }

    const std::string &getBucketType() const {
        return m_buckettype;
    }

private:
    std::string m_accountId;
    std::string m_id;
    std::string m_name;
    std::string m_buckettype;
};


#endif //B2SYNC_B2BUCKET_H
