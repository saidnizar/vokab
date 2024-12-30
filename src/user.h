#ifndef USER_H
#define USER_H

#include "FileManager.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <string>

// Use the nlohmann namespace for JSON
using json = nlohmann::json;

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
  bool registerUser(const std::string &username, const std::string &pwd);
  std::string getUsername() { return m_username; }

private:
  User() : userDB("vokab", "user.vkb") {}

  bool m_loggedIn = false;
  uint64_t m_id = 0;
  std::string m_username;
  FileManager userDB;
  void createUser(const std::string &username, const uint64_t HashedPwd,
                  uint64_t userId);
  uint64_t findUser(const std::string &username, const uint64_t pwd);
  uint64_t PwdHash(const std::string &pwd);
};

#endif // USER_H
