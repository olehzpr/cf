#include <string>
#include <iostream>


namespace UI {
  void help();
  void platformNotSupported();
  void windowsIsNotAppreciated();
  void failedToOpenFile(std::string path);
  void usingDefaultValue(std::string value);
  void usingDirectoryFlag(std::string value);
}