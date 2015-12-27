//
// Created by Oliver Albers on 25.11.15.
//

#ifndef B2SYNC_B2BUCKET_H
#define B2SYNC_B2BUCKET_H

#include <string>
#include <boost/property_tree/ptree.hpp>

enum class B2BucketType { ALLPUBLIC, ALLPRIVATE };

class B2Bucket {
public:
    B2Bucket(const std::string &accountId, const std::string &id, const std::string &name, const B2BucketType &buckettype);
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

    const B2BucketType &getBucketType() const {
        return m_buckettype;
    }

    static const B2BucketType TypeFromString(const std::string &typeString);
    static const std::string StringFromType(const B2BucketType &type);

private:
    std::string m_accountId;
    std::string m_id;
    std::string m_name;
    B2BucketType m_buckettype;
};


// Output operator for bucket types enum
inline std::ostream& operator<<(std::ostream &ostream, const B2BucketType &bt) {
    return ostream << B2Bucket::StringFromType(bt);
}


#endif //B2SYNC_B2BUCKET_H
