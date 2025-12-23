#include "clipboard.hpp"
#include "ui.hpp"
#include <format>
#include <algorithm>
#include <cstdio>
#include <memory>
#include <array>
#include <iostream>
#include <sys/wait.h>

#if defined(__MINGW32__)

void Clipboard::copy(std::string text) {
  UI::windowsIsNotAppreciated();
}

#elif defined(__APPLE__)

void Clipboard::copy(std::string text) {
  FILE* pipe = popen("pbcopy", "w");
  if (pipe == nullptr) {
    std::cerr << "Failed to open clipboard pipe" << std::endl;
    return;
  }

  fwrite(text.c_str(), sizeof(char), text.size(), pipe);

  int status = pclose(pipe);
  if (status == -1 || !WIFEXITED(status) || WEXITSTATUS(status) != 0) {
    std::cerr << "Failed to copy to clipboard" << std::endl;
  }
}

#elif defined(__linux__)

#if defined(BUILDING_WITH_X11)
void Clipboard::copy(std::string text) {
  FILE* pipe = popen("xclip -selection clipboard", "w");
  if (pipe == nullptr) {
    std::cerr << "Failed to open clipboard pipe" << std::endl;
    return;
  }

  fwrite(text.c_str(), sizeof(char), text.size(), pipe);

  int status = pclose(pipe);
  if (status == -1 || !WIFEXITED(status) || WEXITSTATUS(status) != 0) {
    std::cerr << "Failed to copy to clipboard" << std::endl;
  }
}
#endif


#if defined(BUILDING_WITH_WAYLAND)
void Clipboard::copy(std::string text) {
  FILE* pipe = popen("wl-copy", "w");
  if (pipe == nullptr) {
    std::cerr << "Failed to open clipboard pipe" << std::endl;
    return;
  }

  fwrite(text.c_str(), sizeof(char), text.size(), pipe);

  int status = pclose(pipe);
  if (status == -1 || !WIFEXITED(status) || WEXITSTATUS(status) != 0) {
    std::cerr << "Failed to copy to clipboard" << std::endl;
  }
}
#endif

#else

void Clipboard::copy(std::string text) {
  UI::platformNotSupported();
}

#endif
