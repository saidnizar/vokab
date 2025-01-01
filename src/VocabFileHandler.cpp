#include "VocabFileHandler.h"

void VocabFileHandler::addVocabEntry(VocabStruct vocab) {
  json vocabJson;
  vocabJson["word"] = vocab.word;
  vocabJson["translation"] = vocab.translation;
  vocabJson["example"] = vocab.example;

  std::cout << "Entry created successfully: " << vocab.word << "\n";
  // Load existing data from the file
  json fileData = m_vocab_file.loadFile();

  // Add the new user
  fileData.push_back(vocabJson);

  // Save back to the file
  m_vocab_file.saveFile(fileData);
}

bool VocabFileHandler::getNextEntry(VocabFileHandler::VocabStruct &vocab) {
  json vocabs = m_vocab_file.loadFile();
  int i = 0;
  // Search for the user in the JSON array
  for (const auto &item : vocabs.items()) {
    if (i == m_index) {
      vocab.word = item.value()["word"].get<std::string>();
      vocab.translation = item.value()["translation"].get<std::string>();
      m_index++;
      return true;
    }
    i++;
  }
  m_index = 0;
  return false;
}
