//
// Created by Oliver Albers on 18.11.15.
//

#ifndef B2SYNC_B2AUTHTOKEN_H
#define B2SYNC_B2AUTHTOKEN_H


class B2AuthToken {
public:
    B2AuthToken(const std::string& token) : m_token(token) {};
private:
    std::string m_token;
};


#endif //B2SYNC_B2AUTHTOKEN_H
