#include "file_ignore_list.hpp"
#include <fstream>
#include <algorithm>
#include <iostream>

FileIgnoreList::FileIgnoreList(const std::string& directory)
  : base_directory(directory) {
  addDefaultPatterns();
  loadGitignore();
}

void FileIgnoreList::addDefaultPatterns() {
  // Binary and executable files
  patterns.push_back("*.exe");
  patterns.push_back("*.dll");
  patterns.push_back("*.so");
  patterns.push_back("*.dylib");
  patterns.push_back("*.o");
  patterns.push_back("*.a");
  patterns.push_back("*.lib");
  patterns.push_back("*.out");
  patterns.push_back("*.bin");
  patterns.push_back("*.class");
  patterns.push_back("*.pyc");
  patterns.push_back("*.pyo");

  // Package/dependency directories
  patterns.push_back("node_modules/");
  patterns.push_back("node_modules/*");
  patterns.push_back(".venv/");
  patterns.push_back(".venv/*");
  patterns.push_back("venv/");
  patterns.push_back("venv/*");
  patterns.push_back("__pycache__/");
  patterns.push_back("__pycache__/*");
  patterns.push_back("vendor/");
  patterns.push_back("target/");
  patterns.push_back("build/");
  patterns.push_back("dist/");

  // Version control
  patterns.push_back(".git/");
  patterns.push_back(".git/*");
  patterns.push_back(".svn/");
  patterns.push_back(".hg/");

  // IDE and editor files
  patterns.push_back(".vscode/");
  patterns.push_back(".idea/");
  patterns.push_back("*.swp");
  patterns.push_back("*.swo");
  patterns.push_back("*~");
  patterns.push_back(".DS_Store");
  patterns.push_back("Thumbs.db");

  // Archives and compressed files
  patterns.push_back("*.zip");
  patterns.push_back("*.tar");
  patterns.push_back("*.tar.gz");
  patterns.push_back("*.tgz");
  patterns.push_back("*.rar");
  patterns.push_back("*.7z");

  // Image files (usually binary)
  patterns.push_back("*.png");
  patterns.push_back("*.jpg");
  patterns.push_back("*.jpeg");
  patterns.push_back("*.gif");
  patterns.push_back("*.bmp");
  patterns.push_back("*.ico");
  patterns.push_back("*.svg");

  // Media files
  patterns.push_back("*.mp3");
  patterns.push_back("*.mp4");
  patterns.push_back("*.avi");
  patterns.push_back("*.mov");
  patterns.push_back("*.wav");

  // Database files
  patterns.push_back("*.db");
  patterns.push_back("*.sqlite");
  patterns.push_back("*.sqlite3");

  // Log files
  patterns.push_back("*.log");

  // Lock files
  patterns.push_back("package-lock.json");
  patterns.push_back("yarn.lock");
  patterns.push_back("Gemfile.lock");
  patterns.push_back("Cargo.lock");
}

void FileIgnoreList::loadGitignore() {
  fs::path gitignore_path = fs::path(base_directory) / ".gitignore";

  if (!fs::exists(gitignore_path)) {
    return;
  }

  std::ifstream file(gitignore_path);
  if (!file.is_open()) {
    std::cerr << "Warning: Could not read .gitignore file" << std::endl;
    return;
  }

  std::string line;
  while (std::getline(file, line)) {
    line.erase(0, line.find_first_not_of(" \t\r\n"));
    line.erase(line.find_last_not_of(" \t\r\n") + 1);

    if (line.empty() || line[0] == '#') {
      continue;
    }

    patterns.push_back(line);
  }
}

bool FileIgnoreList::matchesPattern(const fs::path& file_path, const std::string& pattern) const {
  std::string path_str = file_path.string();
  std::string filename = file_path.filename().string();

  fs::path abs_base = fs::absolute(base_directory);
  fs::path abs_file = fs::absolute(file_path);

  std::string relative_path;
  if (abs_file.string().find(abs_base.string()) == 0) {
    relative_path = abs_file.string().substr(abs_base.string().length());
    if (!relative_path.empty() && relative_path[0] == '/') {
      relative_path = relative_path.substr(1);
    }
  } else {
    relative_path = path_str;
  }

  if (pattern.back() == '/' || pattern.find("/*") != std::string::npos) {
    std::string dir_pattern = pattern;
    if (dir_pattern.find("/*") != std::string::npos) {
      dir_pattern = dir_pattern.substr(0, dir_pattern.find("/*"));
    } else if (dir_pattern.back() == '/') {
      dir_pattern = dir_pattern.substr(0, dir_pattern.length() - 1);
    }

    fs::path check_path = file_path;
    while (check_path.has_parent_path() && check_path != abs_base) {
      if (check_path.filename() == dir_pattern) {
        return true;
      }
      check_path = check_path.parent_path();
    }

    if (relative_path.find(dir_pattern + "/") == 0 ||
        relative_path.find("/" + dir_pattern + "/") != std::string::npos) {
      return true;
    }
  }

  if (pattern[0] == '*' && pattern.find('.') != std::string::npos) {
    std::string extension = pattern.substr(pattern.find('.'));
    if (filename.length() >= extension.length()) {
      if (filename.substr(filename.length() - extension.length()) == extension) {
        return true;
      }
    }
  }

  if (filename == pattern) {
    return true;
  }

  if (relative_path == pattern) {
    return true;
  }

  if (relative_path.find(pattern + "/") == 0) {
    return true;
  }

  return false;
}

bool FileIgnoreList::isBinaryFile(const fs::path& file_path) const {
  std::vector<std::string> binary_extensions = {
    ".exe", ".dll", ".so", ".dylib", ".o", ".a", ".lib",
    ".png", ".jpg", ".jpeg", ".gif", ".bmp", ".ico",
    ".mp3", ".mp4", ".avi", ".mov", ".wav",
    ".zip", ".tar", ".gz", ".rar", ".7z",
    ".pdf", ".doc", ".docx", ".xls", ".xlsx",
    ".db", ".sqlite", ".sqlite3"
  };

  std::string ext = file_path.extension().string();
  std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

  return std::find(binary_extensions.begin(), binary_extensions.end(), ext) != binary_extensions.end();
}

bool FileIgnoreList::shouldIgnore(const fs::path& file_path) const {
  if (isBinaryFile(file_path)) {
    return true;
  }

  for (const auto& pattern : patterns) {
    if (matchesPattern(file_path, pattern)) {
      return true;
    }
  }

  return false;
}
