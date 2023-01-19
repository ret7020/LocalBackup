#include "crow.h"

bool check_file(std::string storage, std::string file_name)
{
    
}

int main()
{
    // Temp conf
    std::string SERVER_STORAGE = "./Storage/";
    
    crow::SimpleApp app;
    CROW_ROUTE(app, "/")([](){
        return "Test";
    });
    CROW_ROUTE(app, "/get_file/<string>")([](std::string file_name){
        std::cout << file_name << "\n";
        return "File cont here";
    });

    CROW_ROUTE(app, "/sync/<string>")([](std::string file_name){
        std::cout << file_name << "\n";
        return "Uploading";
    });
    app.port(18080).multithreaded().run();
}

