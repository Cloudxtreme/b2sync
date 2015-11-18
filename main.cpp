#include <iostream>
#include "B2Client.h"

using namespace std;

int main() {
    B2Client client;
    auto token = client.authenticate("a", "b");
    if (! token.success) {
        cout << "Could not log in to B2 API" << std::endl;
        return 1;
    }

    cout << token.result;

    return 0;
}