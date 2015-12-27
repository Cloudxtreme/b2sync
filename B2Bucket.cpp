//
// Created by Oliver Albers on 25.11.15.
//

#include "B2Bucket.h"
#include <iostream>

B2Bucket::B2Bucket(const std::string &accountId, const std::string &id, const std::string &name,
                   const B2BucketType &buckettype) :
        m_accountId(accountId), m_id(id), m_name(name), m_buckettype(buckettype) {

}

B2Bucket::B2Bucket(const boost::property_tree::ptree &ptree) {
    m_accountId = ptree.get<std::string>("accountId");
    m_id = ptree.get<std::string>("bucketId");
    m_name = ptree.get<std::string>("bucketName");

    auto type = ptree.get<std::string>("bucketType");
    if (type.compare("allPrivate") == 0) {
        m_buckettype = B2BucketType::ALLPRIVATE;
    } else if (type.compare("allPublic") == 0) {
        m_buckettype = B2BucketType::ALLPUBLIC;
    } else {
        // TODO: Throw exception?
        m_buckettype = B2BucketType::ALLPUBLIC;
    }
}

const B2BucketType B2Bucket::TypeFromString(const std::string &typeString) {
    if (typeString.compare("allPrivate") == 0) {
        return B2BucketType::ALLPRIVATE;
    }
    if (typeString.compare("allPublic") == 0) {
        return B2BucketType::ALLPUBLIC;
    }

    throw typeString;
}

const std::string B2Bucket::StringFromType(const B2BucketType &type) {
    switch (type) {
        case B2BucketType::ALLPRIVATE :
            return "allPrivate";
        case B2BucketType::ALLPUBLIC :
            return "allPublic";
    };
}
