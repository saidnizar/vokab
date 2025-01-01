#ifndef USER_H
#define USER_H

#include <fstream>
#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <string>

#include "FileManager.h"

// User class
class User {
public:
  // Get the singleton instance of the User class
  static User &getInstance() {
    static User instance;
    return instance;
  }

  // Delete copy constructor and assignment operator for singleton
  User(const User &) = delete;
  User &operator=(const User &) = delete;
  bool logInUser(const std::string &username, const std::string &pwd);
  void logoutUser();
  bool registerUser(const std::string &username, const std::string &pwd);
  std::string getUsername() { return m_username; }
  uint64_t getUserID() { return m_id; }
  bool loadPreviousSession();

private:
  User() : userDB("vokab", "user.vkb"), m_session("tmp", "session.vkb") {}

  bool m_loggedIn = false;
  uint64_t m_id = 0;
  std::string m_username;
  FileManager userDB;
  FileManager m_session;
  void createUser(const std::string &username, const uint64_t HashedPwd,
                  uint64_t userId);
  uint64_t findUser(const std::string &username, const uint64_t pwd);
  uint64_t PwdHash(const std::string &pwd);
  void saveSession();
  void destroySession();
};

#endif // USER_H
