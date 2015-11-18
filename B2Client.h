//
// Created by Oliver Albers on 18.11.15.
//

#ifndef B2SYNC_B2CLIENT_H
#define B2SYNC_B2CLIENT_H

#include <curl_easy.h>

class B2Client {
public:
    B2Client();
    ~B2Client();


protected:
    curl::curl_easy *m_curl;
};

#endif //B2SYNC_B2CLIENT_H
