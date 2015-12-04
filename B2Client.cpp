//
// Created by Oliver Albers on 18.11.15.
//

#include <curl_header.h>
#include <curl_form.h>
#include "B2Client.h"

B2APIMessage<B2AuthorizeAccountResponse> B2Client::authenticate(const string &accountId, const string &applicationKey) {
    curl::curl_easy curl;

    std::ostringstream data;
    std::ostringstream header;
    curl::curl_ios<ostringstream> body(data);
    curl.add<CURLOPT_WRITEFUNCTION>(body.get_function());
    curl.add<CURLOPT_WRITEDATA>(body.get_stream());

    curl.add<CURLOPT_URL>("https://api.backblaze.com/b2api/v1/b2_authorize_account");
    curl.add<CURLOPT_FOLLOWLOCATION>(1L);

    std::string authHeader = accountId + ":" + applicationKey;
    curl.add<CURLOPT_USERPWD>(authHeader.c_str());

    B2APIMessage<B2AuthorizeAccountResponse> result;

    try {
        curl.perform();

        boost::property_tree::ptree jsonpt;
        std::stringstream ss;
        ss << data.str();
        boost::property_tree::json_parser::read_json(ss, jsonpt);

        result.result = std::make_shared<B2AuthorizeAccountResponse>(
                jsonpt.get<std::string>("authorizationToken"),
                jsonpt.get<std::string>("apiUrl"),
                jsonpt.get<std::string>("downloadUrl")
        );
        result.success = true;

        m_auth = result.result;
    }
    catch (curl_easy_exception e) {
        result.success = false;
    }
    catch (boost::property_tree::ptree_bad_path e) {
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
    curl::curl_easy curl;

    std::ostringstream data;
    std::ostringstream header;
    curl::curl_ios<ostringstream> body(data);
    //curl.add<CURLOPT_WRITEFUNCTION>(body.get_function());
    //curl.add<CURLOPT_WRITEDATA>(body.get_stream());

    curl.add<CURLOPT_URL>("https://api.backblaze.com/b2api/v1/b2_list_buckets");
    curl.add<CURLOPT_FOLLOWLOCATION>(1L);

    curl::curl_header httpheader = {
        "Authorization: " + m_auth->getToken()
    };
    curl.add<CURLOPT_HTTPHEADER>(httpheader.get());

    curl::curl_form form;
    auto accountid_form = curl_pair<CURLformoption, std::string>(CURLFORM_COPYNAME, "accountId");
    auto accountid_content = curl_pair<CURLformoption, std::string>(CURLFORM_COPYCONTENTS, m_accountid);

    B2APIMessage<B2ListBucketsResponse> result;

    try {
        form.add(accountid_form, accountid_content);

        curl.perform();

      /*  boost::property_tree::ptree jsonpt;
        std::stringstream ss;
        ss << data.str();
        boost::property_tree::json_parser::read_json(ss, jsonpt);
*/
/*        result.result = std::make_shared<B2AuthorizeAccountResponse>(
                jsonpt.get<std::string>("authorizationToken"),
                jsonpt.get<std::string>("apiUrl"),
                jsonpt.get<std::string>("downloadUrl")
        );*/
        result.success = true;
    }
    catch (curl_easy_exception e) {
        result.success = false;
    }
    catch (boost::property_tree::ptree_bad_path e) {
        cout << "Could not access JSON property from API result: " << e.what() << std::endl;

        result.success = false;
    }

    return result;
}
