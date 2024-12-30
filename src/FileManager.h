#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QDir>
#include <QFileInfo>
#include <QStandardPaths>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class FileManager {
public:
  explicit FileManager(const QString &directoryName, const QString &fileName);

  void saveFile(json &jsonData);

  json loadFile();

private:
  QString dirName;
  QString fileName;
  QString dirPath;
  QString filePath;
};

#endif
