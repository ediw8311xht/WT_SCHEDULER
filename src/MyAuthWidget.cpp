#include "MyAuthWidget.h"
#include <Wt/WLineEdit.h>
#include <Wt/WTemplate.h>
#include <Wt/WText.h>
#include <Wt/Auth/PasswordService.h>
#include <Wt/Auth/RegistrationWidget.h>
#include <Wt/Auth/AuthModel.h>
#include "Models.h"

MyAuthWidget::MyAuthWidget(MySession &session, const std::string &basePath)
    : Wt::Auth::AuthWidget(session.login()) {

    auto model = std::make_unique<Wt::Auth::AuthModel>(session.passwordAuth().baseAuth(), session.users());

    model->addPasswordAuth(&session.passwordAuth());
    setModel(std::move(model));
    /*setRegistrationEnabled(true);*/

}
