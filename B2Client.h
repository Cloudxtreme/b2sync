//
// Created by Oliver Albers on 18.11.15.
//

#ifndef B2SYNC_B2CLIENT_H
#define B2SYNC_B2CLIENT_H

#include <curl_easy.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "B2APIMessage.h"
#include "B2AuthorizeAccountResponse.h"

class B2Client {
protected:
    std::shared_ptr<B2AuthorizeAccountResponse> m_auth;

public:
    B2APIMessage<B2AuthorizeAccountResponse> authenticate(const string &accountId, const string &applicationKey);
    void authenticate(const string &token, const string &apiUrl, const string &downloadUrl);
};

#endif //B2SYNC_B2CLIENT_H
