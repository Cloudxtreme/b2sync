//
// Created by Oliver Albers on 18.11.15.
//

#ifndef B2SYNC_B2AUTHTOKEN_H
#define B2SYNC_B2AUTHTOKEN_H


class B2AuthorizeAccountResponse {
public:
    B2AuthorizeAccountResponse(const std::string& token, const std::string& apiurl, const std::string& downloadurl)
            : m_token(token), m_apiurl(apiurl), m_downloadurl(downloadurl)
    {
    }

    const string &getToken() const {
        return m_token;
    }

    const string &getAPIUrl() const {
        return m_apiurl;
    }

    const string &getDownloadUrl() const {
        return m_downloadurl;
    }

private:
    std::string m_token;
    std::string m_apiurl;
    std::string m_downloadurl;
};


#endif //B2SYNC_B2AUTHTOKEN_H
