#include "cf/file_collector.hpp"
#include "cf/ui.hpp"
#include <fstream>
#include <algorithm>

FileCollector::FileCollector(const std::string& dir, const std::vector<std::string>& exts, bool use_ignore)
  : directory(dir), extensions(exts), use_ignore_list(use_ignore) {
  if (use_ignore_list) {
    ignore_list = std::make_unique<FileIgnoreList>(dir);
  }
}

bool FileCollector::shouldProcessFile(const fs::path& file_path) const {
  if (extensions.empty()) {
    return true;
  }

  if (!file_path.has_extension()) {
    return false;
  }

  std::string dot_extension = file_path.extension();
  std::string file_extension = dot_extension.substr(1, dot_extension.size());

  return std::find(extensions.begin(), extensions.end(), file_extension) != extensions.end();
}

std::string FileCollector::readFileContent(const fs::path& file_path) const {
  std::ifstream file(file_path);

  if (!file.is_open()) {
    UI::failedToOpenFile(file_path);
    return "";
  }

  std::string content{std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};
  return content;
}

std::string FileCollector::collectFiles() {
  std::string all_content;

  for (auto const& dir_entry: fs::recursive_directory_iterator(directory)) {
    if (!dir_entry.is_regular_file()) {
      continue;
    }

    if (use_ignore_list && ignore_list->shouldIgnore(dir_entry.path())) {
      continue;
    }

    if (!shouldProcessFile(dir_entry.path())) {
      continue;
    }

    std::string file_content = readFileContent(dir_entry.path());

    if (file_content.empty()) {
      continue;
    }

    all_content += std::string(dir_entry.path()) + "\n" + file_content + "\n";
  }

  return all_content;
}
