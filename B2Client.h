//
// Created by Oliver Albers on 18.11.15.
//

#ifndef B2SYNC_B2CLIENT_H
#define B2SYNC_B2CLIENT_H

#include <cpr/cpr.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "B2APIMessage.h"
#include "B2AuthorizeAccountResponse.h"
#include "B2ListBucketsResponse.h"

class B2Client {
protected:
    std::shared_ptr<B2AuthorizeAccountResponse> m_auth;
    std::string m_accountid;

public:
    B2Client(const std::string &m_accountid) : m_accountid(m_accountid) { }

    B2APIMessage<B2AuthorizeAccountResponse> authenticate(const std::string &accountId, const std::string &applicationKey);
    void authenticate(const std::string &token, const std::string &apiUrl, const std::string &downloadUrl);
    B2APIMessage<B2ListBucketsResponse> listBuckets();

protected:
    boost::property_tree::ptree parse_json(const std::string responseText) const;
};

#endif //B2SYNC_B2CLIENT_H
