#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/info_parser.hpp>
#include "B2Client.h"

using namespace std;

int main() {
    boost::property_tree::ptree b2config;
    boost::property_tree::info_parser::read_info("b2config.info", b2config);

    B2Client client;
    auto token = client.authenticate(
            b2config.get<std::string>("accountid"),
            b2config.get<std::string>("applicationkey")
    );
    if (! token.success) {
        cout << "Could not log in to B2 API" << std::endl;
        return 1;
    }

    cout << token.result;

    return 0;
}