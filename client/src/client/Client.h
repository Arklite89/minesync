#pragma once

#import <string>

class Client {
private:
    std::string serverURL;

public:
    explicit Client(const std::string &new_server_url);

    std::string getServerUrl();
    bool setServerUrl(const std::string &new_server_url);

    bool syncLocalSave();
};