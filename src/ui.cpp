#include "cf/ui.hpp"

void UI::help() {
  std::cout << "Usage: cf [directory] [options]" << std::endl;
  std::cout << std::endl;
  std::cout << "Copy file contents from a directory to clipboard" << std::endl;
  std::cout << "By default, ignores binaries, common junk files, and .gitignore patterns" << std::endl;
  std::cout << std::endl;
  std::cout << "Options:" << std::endl;
  std::cout << "  -h, --help                    Show this help message" << std::endl;
  std::cout << "  -p, --print                   Print output to stdout (in addition to clipboard)" << std::endl;
  std::cout << "  -n, --no-ignore               Disable automatic file filtering (include all files)" << std::endl;
  std::cout << "  -d, --directory <path>        Specify base directory" << std::endl;
  std::cout << "  -e, --extensions <ext,...>    Filter by file extensions (comma-separated)" << std::endl;
  std::cout << std::endl;
  std::cout << "Examples:" << std::endl;
  std::cout << "  cf                            Copy all files from current directory" << std::endl;
  std::cout << "  cf src                        Copy all files from src directory" << std::endl;
  std::cout << "  cf -e cpp,hpp                 Copy only .cpp and .hpp files" << std::endl;
  std::cout << "  cf -n                         Include all files (no filtering)" << std::endl;
  std::cout << "  cf src -e js,ts -p            Copy .js and .ts from src, print to stdout" << std::endl;
}

void UI::platformNotSupported(){
  std::cout << "Platform is not supported. File content was not copied :(" << std::endl;
}

void UI::windowsIsNotAppreciated(){
  std::cout << "We do not tolerate windows users!" << std::endl;
}

void UI::failedToOpenFile(std::string path){
  std::cout << "Failed to open file: " << path << std::endl;
}

void UI::usingDefaultValue(std::string value){
  std::cout << "Contents of " << value << " copied to clipboard" << std::endl;
}

void UI::usingDirectoryFlag(std::string value){
  std::cout << "Contents of " << value << " directory copied to clipboard" << std::endl;
}
