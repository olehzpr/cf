#ifndef FILE_COLLECTOR_HPP
#define FILE_COLLECTOR_HPP

#include <string>
#include <vector>
#include <filesystem>
#include <memory>
#include "cf/file_ignore_list.hpp"

namespace fs = std::filesystem;

class FileCollector {
private:
  std::string directory;
  std::vector<std::string> extensions;
  std::unique_ptr<FileIgnoreList> ignore_list;
  bool use_ignore_list;

  bool shouldProcessFile(const fs::path& file_path) const;
  std::string readFileContent(const fs::path& file_path) const;

public:
  FileCollector(const std::string& dir, const std::vector<std::string>& exts, bool use_ignore = true);
  std::string collectFiles();
};

#endif
