#include "B2Client.h"
#include <iostream>

B2APIMessage<B2AuthorizeAccountResponse> B2Client::authenticate(const std::string &accountId, const std::string &applicationKey) {
    using namespace boost::property_tree;

    B2APIMessage<B2AuthorizeAccountResponse> result;
    result.success = false;

    try {
        auto response = cpr::Get(
          cpr::Url{"https://api.backblaze.com/b2api/v1/b2_authorize_account"},
          cpr::Authentication{accountId, applicationKey}//,
          //cpr::Timeout{2500}
        );

        if (response.error) {
            std::cout << "Error logging in: " << response.error.message << std::endl;
        }
        if (response.status_code == 200) {
            // Create JSON-Parser
            ptree jsonpt;
            std::stringstream ss;
            // Copy Response text to Parser stream
            ss << response.text;
            // And now parse the result
            json_parser::read_json(ss, jsonpt);


            result.result = std::make_shared<B2AuthorizeAccountResponse>(
                    jsonpt.get<std::string>("authorizationToken"),
                    jsonpt.get<std::string>("apiUrl"),
                    jsonpt.get<std::string>("downloadUrl")
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
    using namespace std;
    using namespace boost::property_tree;

    ostringstream data;
    //auto curl = prepareAuthorizedAPICall("/b2api/v1/b2_list_buckets", {}, data);

    /*
     * curl_header httpheader = {
            "Authorization: " + m_auth->getToken()
    };

    curl->add<CURLOPT_HTTPHEADER>(httpheader.get());

    auto accountId = "{\"accountId\":\"" + m_accountid + "\"}";
    for(auto post : post_data) {
        accountId += "\r\n" + post.first + ": " + post.second;
    }
     */

    B2APIMessage<B2ListBucketsResponse> result;

    try {
        //curl->perform();

        ptree jsonpt;
        stringstream ss;
        auto datastr = data.str();
        ss << data.str();
        json_parser::read_json(ss, jsonpt);

        result.result = make_shared<B2ListBucketsResponse>();

        auto status = jsonpt.get<int>("status");
        if (status == 200) {
            for(auto bucket : jsonpt.get_child("buckets")) {
                result.result->addBucket(B2Bucket(bucket.second));
            }

            result.success = true;
        } else {
            cout << "Error listing buckets: " << jsonpt.get<string>("message") << endl;
        }
    }
    catch (ptree_bad_path e) {
        cout << "Could not access JSON property from API result: " << e.what() << endl;

        result.success = false;
    }

    return result;
}
