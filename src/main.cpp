#include <Wt/WServer.h>
#include "Models.h"
#include "ScheduleApplication.h"

std::unique_ptr<WApplication> createApplication(const WEnvironment& env) {
    return std::make_unique<ScheduleApplication>(env);
}

int main(int argc, char **argv) {
    std::srand(std::time(0));

    try {
        // Creates WServer with configuration from WTHTTP_CONFIGURATION (default)
        WServer server(argc, argv, WTHTTP_CONFIGURATION);

        // Add Application as entry point.
        // New Application is created for each user session and
        // deleted when session is over.
        // Multiple entrypoints can exist.
        server.addEntryPoint(EntryPointType::Application, createApplication);

        // Must configureAuth() before using authWidget.
        // Ensures correct settings for authWidget.
        MySession::configureAuth();

        // Start server.
        server.run();
    }

    // Handle exceptions.
    catch (WServer::Exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (std::exception &e) {
        std::cerr << "exception: " << e.what() << std::endl;
    }
    // Optional method of creating and running server
    // Since I need to configureAuth before starting server,
    // this won't work for me.
    // return WRun(argc, argv, &create);
}
