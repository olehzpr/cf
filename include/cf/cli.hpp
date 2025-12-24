#include <string>

enum BoolFlag {
  Help,
  Print,
  NoIgnore
};

enum ValueFlag {
  Directory,
  Extensions
};

class CLI{
  private:
    // defualt value
    std::string main = ".";
    
    // boolean flags
    bool help = false;
    bool print = false;
    bool no_ignore = false;
    
    // value flags
    std::string directory = "";
    std::string extensions = "";

  public:
    CLI(int argc, char** argv);
    std::string defaultValue();
    bool boolFlag(BoolFlag flag);
    std::string valueFlag(ValueFlag flag);
};