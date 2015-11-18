//
// Created by Oliver Albers on 18.11.15.
//

#include <curl_receiver.h>
#include "B2Client.h"

B2APIMessage<B2AuthToken> B2Client::authenticate(const string &accountId, const string &applicationKey) {
    ostringstream data;

    curl::curl_ios<ostringstream> curl_writer(data);
    curl::curl_easy curl(curl_writer);

    curl.add<CURLOPT_URL>("https://api.backblaze.com/b2api/v1/b2_authorize_account");
    curl.add<CURLOPT_FOLLOWLOCATION>(1L);

    std::string authHeader = accountId + ":" + applicationKey;
    curl.add<CURLOPT_USERPWD>(authHeader.c_str());

    B2APIMessage<B2AuthToken> result;

    try {
        curl.perform();

    } catch (curl_easy_exception e) {
        result.success = false;
    }

    return result;
}