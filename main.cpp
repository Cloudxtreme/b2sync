#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/info_parser.hpp>
#include "B2Client.h"

using namespace std;

int main() {
    boost::property_tree::ptree b2config;
    boost::property_tree::info_parser::read_info("b2config.info", b2config);


    int configerrs = 0;
    if (b2config.count("accountid") == 0) {
        cout << "b2config.info does not contain the key accountid" << std::endl;
        configerrs++;
    }
    if (b2config.count("applicationkey") == 0) {
        cout << "b2config.info does not contain the key applicationkey" << std::endl;
        configerrs++;
    }
    if (configerrs > 0) {
        return 1;
    }

    B2Client client(b2config.get<std::string>("accountid"));

    shared_ptr<B2AuthorizeAccountResponse> authtoken = nullptr;

    if (b2config.count("token") == 0 || b2config.count("apiurl") == 0 || b2config.count("downloadurl") == 0) {
        // If no access token is known the account has to be authenticated first
        auto token = client.authenticate(
                b2config.get<std::string>("accountid"),
                b2config.get<std::string>("applicationkey")
        );
        if (!token.success) {
            cout << "Could not log in to B2 API" << std::endl;
            return 1;
        }

        b2config.put<std::string>("token", token.result->getToken());
        b2config.put<std::string>("apiurl", token.result->getAPIUrl());
        b2config.put<std::string>("downloadurl", token.result->getDownloadUrl());

        boost::property_tree::info_parser::write_info("b2config.info", b2config);
    } else {
        client.authenticate(
                b2config.get<std::string>("token"),
                b2config.get<std::string>("apiurl"),
                b2config.get<std::string>("downloadurl")
        );
    }

    auto buckets = client.listBuckets();
    if (buckets.success) {
        for (auto bucket : buckets.result->getBuckets()) {
            cout << "Found bucket " << bucket.getName() << " with access " << bucket.getBucketType() << std::endl;

            if (bucket.getName().find("kjashdkjsatestbucket") != std::string::npos) {
                auto result = client.deleteBucket(bucket);
                if (result.success) {
                    cout << "  bucket was deleted" << std::endl;
                }
            }
        }
    }

    /*auto newBucket = client.createBucket("kjashdkjsatestbucket", B2BucketType::ALLPUBLIC);
    if (newBucket.success) {
        cout << "New bucket " << newBucket.result->getName() << "(ID " << newBucket.result->getId() << ") created" << std::endl;
    }*/

    return 0;
}