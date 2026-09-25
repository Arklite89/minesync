#pragma once

#import <string>

class Client {
private:
    std::string server_url;

public:
    explicit Client(const std::string &new_server_url);
    std::string get_server_url();
    void set_server_url(const std::string &new_server_url);
};