#include <curl_header.h>
#include <curl_form.h>
#include "B2Client.h"

B2APIMessage<B2AuthorizeAccountResponse> B2Client::authenticate(const string &accountId, const string &applicationKey) {
    using namespace std;
    using namespace boost::property_tree;
    using namespace curl;

    curl_easy curl;

    ostringstream data;
    ostringstream header;
    curl_ios<ostringstream> body(data);
    curl.add<CURLOPT_WRITEFUNCTION>(body.get_function());
    curl.add<CURLOPT_WRITEDATA>(body.get_stream());

    curl.add<CURLOPT_URL>("https://api.backblaze.com/b2api/v1/b2_authorize_account");
    curl.add<CURLOPT_FOLLOWLOCATION>(1L);

    string authHeader = accountId + ":" + applicationKey;
    curl.add<CURLOPT_USERPWD>(authHeader.c_str());

    B2APIMessage<B2AuthorizeAccountResponse> result;

    try {
        curl.perform();

        ptree jsonpt;
        stringstream ss;
        ss << data.str();
        json_parser::read_json(ss, jsonpt);

        auto status = jsonpt.get<int>("status");
        if (status == 200) {
            result.result = make_shared<B2AuthorizeAccountResponse>(
                    jsonpt.get<string>("authorizationToken"),
                    jsonpt.get<string>("apiUrl"),
                    jsonpt.get<string>("downloadUrl")
            );
            result.success = true;
        } else {
            cout << "Could not authenticate: " << jsonpt.get<string>("message") << std::endl;
        }

        m_auth = result.result;
    }
    catch (curl_easy_exception e) {
        result.success = false;
    }
    catch (ptree_bad_path e) {
        cout << "Could not access JSON property from API result: " << e.what() << std::endl;

        result.success = false;
    }

    return result;
}

void B2Client::authenticate(const string &token, const string &apiUrl, const string &downloadUrl) {
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
    auto curl = prepareAuthorizedAPICall("/b2api/v1/b2_list_buckets", {}, data);

    B2APIMessage<B2ListBucketsResponse> result;

    try {
        curl->perform();

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
    catch (curl_easy_exception e) {
        result.success = false;
    }
    catch (ptree_bad_path e) {
        cout << "Could not access JSON property from API result: " << e.what() << endl;

        result.success = false;
    }

    return result;
}

std::unique_ptr<curl::curl_easy> B2Client::prepareAuthorizedAPICall(const std::string &url,
                                                                    const std::vector<std::pair<std::string, std::string>> &post_data,
                                                                    std::ostringstream &curl_result) {
    using namespace std;
    using namespace curl;

    unique_ptr<curl_easy> curl;

    ostringstream header;
    curl_ios<ostringstream> body(curl_result);
    curl->add<CURLOPT_WRITEFUNCTION>(body.get_function());
    curl->add<CURLOPT_WRITEDATA>(body.get_stream());

    auto apiUrl = m_auth->getAPIUrl() + url;
    char* apiUrlC = const_cast<char*>(apiUrl.c_str());

    curl->add<CURLOPT_URL>(apiUrlC);
    curl->add<CURLOPT_FOLLOWLOCATION>(1L);

    curl_header httpheader = {
            "Authorization: " + m_auth->getToken()
    };

    curl->add<CURLOPT_HTTPHEADER>(httpheader.get());

    auto accountId = "{\"accountId\":\"" + m_accountid + "\"}";
    for(auto post : post_data) {
        accountId += "\r\n" + post.first + ": " + post.second;
    }

    char* postData = const_cast<char*>(accountId.c_str());

    curl->add<CURLOPT_POSTFIELDS>(postData);
    curl->add<CURLOPT_POST>(1L);

    return curl;
}
