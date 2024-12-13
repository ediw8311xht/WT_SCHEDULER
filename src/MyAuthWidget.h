
#pragma once
#include <Wt/Auth/AuthWidget.h>
#include <Wt/Auth/RegistrationModel.h>

// Forward declaration
class MySession;

// Used for creating and handling authentication
class MyAuthWidget : public Wt::Auth::AuthWidget {
    public:
        MyAuthWidget(MySession& session, const std::string& basePath); 

        // Not needed.
        // Using authentication event change to handle
        // Updating view based after login/logout
        /*virtual void createLoggedInView() override;*/
};
