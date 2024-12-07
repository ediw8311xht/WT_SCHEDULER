
#pragma once
#include <Wt/Auth/AuthWidget.h>
#include <Wt/Auth/RegistrationModel.h>

class MySession;

class MyAuthWidget : public Wt::Auth::AuthWidget {
    public:
        MyAuthWidget(MySession& session, const std::string& basePath); 
        /*virtual void createLoggedInView() override;*/
};
