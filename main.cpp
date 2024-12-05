#include "ScheduleApplication.h"

std::unique_ptr<WApplication> create(const WEnvironment& env) {
    return std::make_unique<ScheduleApplication>(env);
}

int main(int argc, char **argv) {
    std::srand(std::time(0));
    return WRun(argc, argv, &create);
}
