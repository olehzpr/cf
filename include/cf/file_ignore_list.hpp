#ifndef FILE_IGNORE_LIST_HPP
#define FILE_IGNORE_LIST_HPP

#include <string>
#include <vector>
#include <filesystem>
#include <regex>

namespace fs = std::filesystem;

class FileIgnoreList {
private:
  std::vector<std::string> patterns;
  std::string base_directory;

  void addDefaultPatterns();
  void loadGitignore();
  bool matchesPattern(const fs::path& file_path, const std::string& pattern) const;
  bool isBinaryFile(const fs::path& file_path) const;

public:
  FileIgnoreList(const std::string& directory);
  bool shouldIgnore(const fs::path& file_path) const;
};

#endif
