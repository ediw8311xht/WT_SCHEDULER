#include "Models.h"

#include <Wt/WApplication.h>
#include <Wt/Auth/AuthService.h>
#include <Wt/Auth/HashFunction.h>
#include <Wt/Auth/PasswordService.h>
#include <Wt/Auth/PasswordStrengthValidator.h>
#include <Wt/Auth/PasswordVerifier.h>
#include <Wt/Auth/GoogleService.h>
#include <Wt/Auth/FacebookService.h>
#include <Wt/Auth/Dbo/AuthInfo.h>
#include <Wt/Dbo/Impl.h>

#include <Wt/Dbo/backend/Sqlite3.h>

using namespace Wt;
namespace {
  Auth::AuthService myAuthService;
  Auth::PasswordService myPasswordService(myAuthService);
}

MySession::MySession() {
    auto connection = std::make_unique<Dbo::backend::Sqlite3>(WApplication::instance()->appRoot() + "schedule.db");
    connection->setProperty("show-queries", "true");
    setConnection(std::move(connection));

    mapClass<User>("user");
    mapClass<AuthInfo>("auth_info");
    mapClass<AuthInfo::AuthIdentityType>("auth_identity");
    mapClass<AuthInfo::AuthTokenType>("auth_token");

    try {
        createTables();
        std::cerr << "Created database.\n";
    } catch (Wt::Dbo::Exception &e) {
        std::cerr << e.what() << '\n';
        std::cerr << "Using existing database\n";
    }

    users_ = std::make_unique<UserDatabase>(*this);
}


void MySession::configureAuth()
{
    myAuthService.setAuthTokensEnabled(true, "logincookie");
    myAuthService.setEmailVerificationEnabled(false);
    myAuthService.setEmailVerificationRequired(false);

    auto verifier = std::make_unique<Wt::Auth::PasswordVerifier>();
    verifier->addHashFunction(
        std::make_unique<Wt::Auth::BCryptHashFunction>(7));
    myPasswordService.setVerifier(std::move(verifier));
    myPasswordService.setPasswordThrottle(
        std::make_unique<Wt::Auth::AuthThrottle>());
    myPasswordService.setStrengthValidator(
        std::make_unique<Wt::Auth::PasswordStrengthValidator>());
}

Wt::Auth::AbstractUserDatabase& MySession::users()
{
  return *users_;
}

const Wt::Auth::AuthService& MySession::auth()
{
  return myAuthService;
}

const Wt::Auth::PasswordService& MySession::passwordAuth()
{
  return myPasswordService;
}
