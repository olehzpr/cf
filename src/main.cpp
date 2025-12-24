#include <iostream>
#include <filesystem>
#include "cf/cli.hpp"
#include "cf/ui.hpp"
#include "cf/clipboard.hpp"
#include "cf/utils.hpp"
#include "cf/file_collector.hpp"

namespace fs = std::filesystem;

int main(int argc, char** argv) {
  CLI cli(argc, argv);

  if (cli.boolFlag(Help)) {
    UI::help();
    return 0;
  }

  std::string directory = cli.valueFlag(Directory);
  if (directory != "") {
    UI::usingDirectoryFlag(directory);
  } else {
    directory = cli.defaultValue();
    UI::usingDefaultValue(directory);
  }

  std::vector<std::string> extensions;
  Utils::Split(',', extensions, cli.valueFlag(Extensions));

  std::string all_content;

  try {
    bool use_ignore = !cli.boolFlag(NoIgnore);
    FileCollector collector(directory, extensions, use_ignore);
    all_content = collector.collectFiles();
  } catch (const fs::filesystem_error& e) {
    std::cerr << "Filesystem error: " << e.what() << std::endl;
    return 1;
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }

  if (cli.boolFlag(Print)) {
    std::cout << all_content << std::flush;
  }

  Clipboard::copy(all_content);

  return 0;
}