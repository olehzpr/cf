#include <iostream>
#include <filesystem>
#include <fstream>
#include "cli.hpp"
#include "ui.hpp"
#include "clipboard.hpp"
#include "utils.cpp"

namespace fs = std::filesystem;

int main(int argc, char** argv) {
  CLI* cli = new CLI(argc, argv);

  if (cli->boolFlag(Help)) {
    UI::help();
    return 0;
  }

  std::string directory = cli->valueFlag(Directory);
  if (directory != "") {
    UI::usingDirectoryFlag(directory);
  } else {
    directory = cli->defaultValue();
    UI::usingDefaultValue(directory);
  }

  std::string all_content;

  for (auto const& dir_entry: fs::recursive_directory_iterator(directory)) {
    std::ifstream file(dir_entry.path());

    if (!file.is_open()) {
      UI::failedToOpenFile(dir_entry.path());
      continue;
    }

    std::vector<std::string> extensions;
    Utils::Split(',', extensions, cli->valueFlag(Extensions));
    std::string file_extension = "";
    if (dir_entry.path().has_extension()) {
      std::string dot_extension = dir_entry.path().extension();
      file_extension = dot_extension.substr(1, dot_extension.size());
    } else if (extensions.size() != 0) {
      continue;
    }
    if (extensions.size() != 0 && std::find(extensions.begin(), extensions.end(), file_extension) == extensions.end()) {
      continue;
    }


    std::string file_content{std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};

    if (file_content == "") {
      continue;
    }

    all_content += std::string(dir_entry.path()) + "\n" + file_content + "\n";
  }

  if (cli->boolFlag(Print)) {
    std::cout << all_content << std::flush;
  }

  Clipboard::copy(all_content);

  return 0;
}