#include "crow.h"

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")
    .methods(crow::HTTPMethod::GET)([]() {
        return "Hello world!\n";
    });

    CROW_ROUTE(app, "/upload")
    .methods(crow::HTTPMethod::POST)([](const crow::request& req) {
        crow::multipart::message multipartMsg(req);

        auto filePart = multipartMsg.get_part_by_name("file");
        if (filePart.body.empty()) {
            return crow::response(400, "Error: No file uploaded or 'file' key missing.");
        }

        std::string filename = "uploaded_save.7z";
        auto headers = filePart.headers;

        std::ofstream outFile(filename, std::ios::binary);
        if (!outFile) {
            return crow::response(500, "Error: Failed to open file for writing on server.");
        }

        outFile << filePart.body;
        outFile.close();

        crow::json::wvalue responseJson;
        responseJson["status"] = "success";

        return crow::response(200, responseJson);
    });

    app.port(18080).multithreaded().run();
}