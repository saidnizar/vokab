#ifndef VOCABFILEHANDLER_H
#define VOCABFILEHANDLER_H

#include <fstream>
#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <string>

#include "FileManager.h"

// VocabFileHandler class
class VocabFileHandler {
public:
  struct VocabStruct {
    std::string word;
    std::string translation;
    std::string example;
  };

  // Get the singleton instance of the VocabFileHandler class
  static VocabFileHandler *getInstance(const QString &userId = "") {
    if (!instance) {
      instance = new VocabFileHandler(userId);
    }
    return instance;
  }

  static void destroyInstance() {
    delete instance;
    instance = nullptr;
  }

  // Delete copy constructor and assignment operator for singleton
  VocabFileHandler(const VocabFileHandler &) = delete;
  VocabFileHandler &operator=(const VocabFileHandler &) = delete;
  void addVocabEntry(VocabStruct vocab);
  bool getNextEntry(VocabStruct &vocab);

private:
  VocabFileHandler(const QString &userId) : m_vocab_file("vokab", userId) {}
  FileManager m_vocab_file;
  uint32_t m_index = 0;
  static VocabFileHandler *instance;
};

#endif // VOCABFILEHANDLER_H
