#include "Models.h"

#include <Wt/WApplication.h>
#include <Wt/Auth/AuthService.h>
#include <Wt/Auth/HashFunction.h>
#include <Wt/Auth/PasswordService.h>
#include <Wt/Auth/PasswordStrengthValidator.h>
#include <Wt/Auth/PasswordVerifier.h>
// Might use these later
// Allows login through oath
#include <Wt/Auth/GoogleService.h>
#include <Wt/Auth/FacebookService.h>
// 
#include <Wt/Auth/Dbo/AuthInfo.h>
#include <Wt/Dbo/Impl.h>

#include <Wt/Dbo/backend/Sqlite3.h>

using namespace Wt;
// Multiple password services available, not using oauth, only regular passwords though
namespace {
  Auth::AuthService myAuthService;
  Auth::PasswordService myPasswordService(myAuthService);
}

MySession::MySession() {
    // Creates connection to SQL database
    auto connection = std::make_unique<Dbo::backend::Sqlite3>(WApplication::instance()->appRoot() + "schedule.db");
    connection->setProperty("show-queries", "true");
    setConnection(std::move(connection));

    // Creates transaction to SQL
    Dbo::Transaction t(*this);
    // Transaction is automatically committed when it goes out of scope
    // Might add explicit commit later, but it causes issues currently

    // Maps to database
    mapClass<User>("user");
    mapClass<Spot>("spot");
    mapClass<Day>("day");
    mapClass<AuthInfo>("auth_info");
    mapClass<AuthInfo::AuthIdentityType>("auth_identity");
    mapClass<AuthInfo::AuthTokenType>("auth_token");

    // createTables if they don't already exist.
    // If a new table is added, db will need to be manually modified.
    try {
        createTables();
        std::cerr << "Created database.\n";
    } catch (Wt::Dbo::Exception &e) {
        std::cerr << e.what() << '\n';
        std::cerr << "Using existing database\n";
    }

    // At some point, need to combine User and users created from UserDatabase.
    // Currently only information saved is that for authentication.
    users_ = std::make_unique<UserDatabase>(*this);
}


// Sets settings for authentication
void MySession::configureAuth()
{
    // Allow remembering login
    myAuthService.setAuthTokensEnabled(true, "logincookie");
    // Disabling email verification for now.
    myAuthService.setEmailVerificationEnabled(false);
    myAuthService.setEmailVerificationRequired(false);

    auto verifier = std::make_unique<Wt::Auth::PasswordVerifier>();
    // Keeping BCryptHasFunction at 7 for now, in production will change.
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

Wt::Auth::Login& MySession::login() {
    return login_;
}


