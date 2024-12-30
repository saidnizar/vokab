#include "FileManager.h"

FileManager::FileManager(const QString &directoryName, const QString &fileName)
    : dirName(directoryName), fileName(fileName) {
  // Get the user's home directory
  QString homeDir =
      QStandardPaths::writableLocation(QStandardPaths::HomeLocation);

  // Construct the full directory path
  dirPath = homeDir + QDir::separator() + dirName;

  // Ensure the directory exists
  QDir dir(dirPath);
  if (!dir.exists()) {
    if (!dir.mkpath(".")) {
      std::cerr << "Failed to create directory: " << dirPath.toStdString()
                << std::endl;
      throw std::runtime_error("Directory creation failed");
    }
  }

  // Construct the full file path
  filePath = dirPath + QDir::separator() + fileName;
}

void FileManager::saveFile(json &jsonData) {
  QFileInfo fileInfo(filePath);

  if (fileInfo.exists()) {
    // If the file exists, load its content
    std::ifstream inFile(filePath.toStdString());
    if (!inFile.is_open()) {
      std::cerr << "Failed to open file for reading: " << filePath.toStdString()
                << std::endl;
      throw std::runtime_error("File read error");
    }
  }

  if (!jsonData.is_array()) {
    jsonData = json::array();
  }

  // Save the updated JSON array back to the file
  std::ofstream outFile(filePath.toStdString());
  if (!outFile.is_open()) {
    std::cerr << "Failed to open file for writing: " << filePath.toStdString()
              << std::endl;
    throw std::runtime_error("File write error");
  }
  outFile << jsonData.dump(4); // Save with 4 spaces of indentation
}

json FileManager::loadFile() {
  QFileInfo fileInfo(filePath);

  if (!fileInfo.exists()) {
    std::cerr << "File does not exist: " << filePath.toStdString() << std::endl;

    // If the file doesn't exist, return an empty array
    return json::array();
  }

  std::ifstream inFile(filePath.toStdString());
  if (!inFile.is_open()) {
    std::cerr << "Failed to open file for reading: " << filePath.toStdString()
              << std::endl;
    throw std::runtime_error("File read error");
  }

  json fileData;
  try {
    fileData = json::parse(inFile);
  } catch (const json::parse_error &e) {
    std::cerr << "JSON parse error: " << e.what() << std::endl;
    throw std::runtime_error("Invalid JSON structure");
  }

  return fileData;
}
