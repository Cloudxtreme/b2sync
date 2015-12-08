//
// Created by Oliver Albers on 18.11.15.
//

#ifndef B2SYNC_B2APIMESSAGE_H
#define B2SYNC_B2APIMESSAGE_H


template <typename T>
struct B2APIMessage {

    bool success;
    std::shared_ptr<T> result;
};


#endif //B2SYNC_B2APIMESSAGE_H
