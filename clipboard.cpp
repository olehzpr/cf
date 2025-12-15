#include "clipboard.hpp"
#include "ui.hpp"
#include <format>
#include <algorithm>

#if defined(__MINGW32__)

void Clipboard::copy(std::string text) {
  UI::windowsIsNotAppreciated();
}

#elif defined(__APPLE__)

void Clipboard::copy(std::string text) {
  std::string cmd = std::format("echo '{0}' | pbcopy", text);
  system(cmd.c_str());
}

#elif defined(__linux__)

#if defined(BUILDING_WITH_X11)
void Clipboard::copy(std::string text) {
  std::string cmd = std::format("echo '{0}' | xclip -selection clipboard", text);
  system(cmd.c_str());
}
#endif


#if defined(BUILDING_WITH_WAYLAND)
void Clipboard::copy(std::string text) {
  std::string cmd = std::format("echo '{0}' | wl-copy", text);
  system(cmd.c_str());
}
#endif

#else

void Clipboard::copy(std::string text) {
  UI::platformNotSupported()
}

#endif
