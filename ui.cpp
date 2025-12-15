#include "ui.hpp"

void UI::help() {
  std::cout << "Usage:" << std::endl;
  std::cout << "cf <directory>\t Base directory of the program" << std::endl << std::endl;
  std::cout << "-h, --help\tHelp" << std::endl;
  std::cout << "-p, --print\tShow output" << std::endl;
  std::cout << "-e, --extensions <file extensions>\t List of allowed extensions" << std::endl;
  std::cout << "\texample: -e py,cpp,js" << std::endl;
  std::cout << "-d, --directory <base directory>\t Base directory of the program" << std::endl;
  std::cout << "\texample: -d src" << std::endl;
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
