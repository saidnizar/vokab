
#include "user.h"

void User::createUser(const std::string &username, uint64_t hashedPwd,
                      uint64_t userId) {
  json userJson;
  userJson["username"] = username;
  userJson["pwd"] = hashedPwd;
  userJson["userId"] = userId;

  // Load existing data from the file
  json fileData = userDB.loadFile();

  // Add the new user
  fileData.push_back(userJson);

  // Save back to the file
  userDB.saveFile(fileData);

  std::cout << "User created successfully: " << username << "\n";
}

// Finds a user in the JSON file by username
uint64_t User::findUser(const std::string &username, const uint64_t pwd) {
  json fileData = userDB.loadFile();
  // Search for the user in the JSON array
  for (const auto &item : fileData.items()) {
    if ((item.value()["username"].get<std::string>() == username) &&
        (item.value()["pwd"].get<uint64_t>() == pwd))
      return item.value()["userId"].get<uint64_t>();
  }

  return 0;
}

uint64_t User::PwdHash(const std::string &input) {
  uint64_t hashValue = 0;
  uint64_t prime = 31; // Use a small prime number to reduce collisions

  for (char c : input) {
    hashValue = hashValue * prime + c;
  }

  return hashValue;
}

bool User::registerUser(const std::string &username, const std::string &pwd) {
  uint64_t hash_pwd = PwdHash(pwd);
  if (!findUser(username, hash_pwd)) {
    createUser(username, hash_pwd, hash_pwd);
    m_id = hash_pwd;
    m_loggedIn = true;
    m_username = username;
    return true;
  }
  return false;
}

bool User::logInUser(const std::string &username, const std::string &pwd) {
  uint64_t hash_pwd = PwdHash(pwd);

  if (findUser(username, hash_pwd)) {
    m_loggedIn = true;
    m_id = hash_pwd;
    m_username = username;
    return true;
  }
  return false;
}
