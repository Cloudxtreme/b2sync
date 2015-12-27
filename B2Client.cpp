#include "B2Client.h"
#include <iostream>

#define API_URL_B2_AUTHORIZE_ACCOUNT    "https://api.backblaze.com/b2api/v1/b2_authorize_account"
#define API_URL_B2_LIST_BUCKETS         "/b2api/v1/b2_list_buckets"

/*
 * Construct and set up JSON parser
 */
boost::property_tree::ptree B2Client::parse_json(const std::string responseText) const {
    // Create JSON-Parser
    boost::property_tree::ptree jsonpt;

    std::stringstream ss;
    // Copy Response text to Parser stream

    ss << responseText;

    // And now parse the result
    boost::property_tree::json_parser::read_json(ss, jsonpt);

    return jsonpt;
}


B2APIMessage<B2AuthorizeAccountResponse> B2Client::authenticate(const std::string &accountId,
                                                                const std::string &applicationKey) {
    using namespace boost::property_tree;

    B2APIMessage<B2AuthorizeAccountResponse> result;

    try {
        auto response = cpr::Get(
                cpr::Url{API_URL_B2_AUTHORIZE_ACCOUNT},
                cpr::Authentication{accountId, applicationKey},
                cpr::Timeout{5000}
        );

        if (response.error) {
            std::cout << "Error logging in: " << response.error.message << std::endl;
        } else if (response.status_code == 200) {
            auto json = parse_json(response.text);

            result.result = std::make_shared<B2AuthorizeAccountResponse>(
                    json.get<std::string>("authorizationToken"),
                    json.get<std::string>("apiUrl"),
                    json.get<std::string>("downloadUrl")
            );
            result.success = true;

            m_auth = result.result;
        } else {
            std::cout << response.text << std::endl;
        }
    }
    catch (ptree_bad_path e) {
        std::cout << "Could not access JSON property from API result: " << e.what() << std::endl;
    }

    return result;
}

void B2Client::authenticate(const std::string &token, const std::string &apiUrl, const std::string &downloadUrl) {
    m_auth = std::make_shared<B2AuthorizeAccountResponse>(
            token,
            apiUrl,
            downloadUrl
    );
}

B2APIMessage<B2ListBucketsResponse> B2Client::listBuckets() {
    using namespace boost::property_tree;

    B2APIMessage<B2ListBucketsResponse> result;

    try {
        auto response = cpr::Post(
                cpr::Url{m_auth->getAPIUrl() + API_URL_B2_LIST_BUCKETS},
                cpr::Header{
                        {"Authorization", m_auth->getToken()}
                },
                cpr::Body{"{\"accountId\":\"" + m_accountid + "\"}"}
        );

        if (response.error) {
            std::cout << "Error listing buckets: " << response.error.message << std::endl;
        } else if (response.status_code == 200) {
            auto json = parse_json(response.text);

            result.success = true;

            result.result = std::make_shared<B2ListBucketsResponse>();
            for (auto bucket : json.get_child("buckets")) {
                result.result->addBucket(B2Bucket(bucket.second));
            }
        } else {
            std::cout << "Error when connecting to API: " << response.text << std::endl;
        }
    }
    catch (ptree_bad_path e) {
        std::cout << "Could not access JSON property from API result: " << e.what() << std::endl;

        result.success = false;
    }

    return result;
}

