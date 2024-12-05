#include <Wt/WServer.h>
#include "Models.h"
#include "ScheduleApplication.h"

std::unique_ptr<WApplication> createApplication(const WEnvironment& env) {
    return std::make_unique<ScheduleApplication>(env);
}

int main(int argc, char **argv) {
    std::srand(std::time(0));

    try {
        WServer server(argc, argv, WTHTTP_CONFIGURATION);

        server.addEntryPoint(EntryPointType::Application, createApplication);

        MySession::configureAuth();

        server.run();
    }

    catch (WServer::Exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (std::exception &e) {
        std::cerr << "exception: " << e.what() << std::endl;
    }
    // return WRun(argc, argv, &create);
}
