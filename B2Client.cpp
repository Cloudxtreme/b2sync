//
// Created by Oliver Albers on 18.11.15.
//

#include "B2Client.h"

B2Client::B2Client() {
    m_curl = new curl::curl_easy();
}

B2Client::~B2Client() {
    delete m_curl;
}
