#include "cf/cli.hpp"
#include "cf/utils.hpp"
#include <iostream>

std::string parseValueFlag(int& i, int argc, char**argv);

CLI::CLI(int argc, char** argv) {
  if (argc == 1) {
    return;
  }

  int initial_index = 1;

  if (!std::string(argv[initial_index]).starts_with("-")) {
    this->main = argv[initial_index++];
  }

  for(int i = initial_index; i < argc; i++) { 
    std::string value = std::string(argv[i]);

    if (value == "--help" || value == "-h") {
      this->help = true;
      return;
    }

    if (value == "--print" || value == "-p") {
      this->print = true;
      continue;
    }

    if (value == "--no-ignore" || value == "-n") {
      this->no_ignore = true;
      continue;
    }

    if (value == "--directory" || value == "-d") {
      this->directory = parseValueFlag(i, argc, argv);
      continue;
    }

    if (value == "--extensions" || value == "-e") {
      this->extensions = parseValueFlag(i, argc, argv);
      continue;
    }
  }
}

std::string CLI::defaultValue(){
  return this->main;
}

bool CLI::boolFlag(BoolFlag flag){
  if (flag == Help) {
    return this->help;
  }

  if (flag == Print) {
    return this->print;
  }

  if (flag == NoIgnore) {
    return this->no_ignore;
  }

  return false;
}

std::string CLI::valueFlag(ValueFlag flag){
  if (flag == Directory) {
    return this->directory;
  }

  if (flag == Extensions) {
    return this->extensions;
  }

  return "";
}

std::string parseValueFlag(int &i, int argc, char **argv){
  if (++i >= argc) return "";

  std::vector<std::string> all_values;

  while(i < argc && !std::string(argv[i]).starts_with('-')) {
    all_values.push_back(std::string(argv[i]));
    ++i;
  }

  --i;

  return Utils::Join(all_values, ",");
}
