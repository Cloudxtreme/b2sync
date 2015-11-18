//
// Created by Oliver Albers on 18.11.15.
//

#ifndef B2SYNC_B2CLIENT_H
#define B2SYNC_B2CLIENT_H

#include <curl_easy.h>
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include "B2APIMessage.h"
#include "B2AuthToken.h"

class B2Client {
public:
    B2APIMessage<B2AuthToken> authenticate(const string &accountId, const string &applicationKey);
};

#endif //B2SYNC_B2CLIENT_H
