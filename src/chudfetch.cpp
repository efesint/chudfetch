#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>

#include <unistd.h>

// hell yea i rewrite this shit in c++
// written in c++ only for linux based
// this code is bloat as shi XD

    const std::string gr = "\033[32m";
    const std::string wh = "\033[0m";
    const std::string rd = "\033[31m";
std::string os() {
    std::ifstream f("/etc/os-release");
    std::string line;
    while (std::getline(f, line)) {
        if (line.rfind("PRETTY_NAME=", 0) == 0) {
            std::string v = line.substr(12);
            if (v.size() >= 2 && v.front() == '"' && v.back() == '"') {
                v = v.substr(1, v.size() - 2);
            }
            return v;
        }
    }
    return "unknown";
}

std::string hostname() {
 char buf[256];
    if(gethostname(buf, sizeof(buf)) == 0) {
      return std::string(buf);
    }

return "unknowm";
}

std::string sh(const std::string& cmd) {
    FILE* fp = popen(cmd.c_str(), "r");
    if (!fp) {
        return "";
    }
    std::string out;
    char buf[256];
    while (fgets(buf, sizeof(buf), fp)) {
        out += buf;
    }
    pclose(fp);
    while (!out.empty() && (out.back() == '\n' || out.back() == '\r')) {
        out.pop_back();
    }
    return out;
}

int main() {
    const char* u = std::getenv("USER");
    std::string username = u ? u : "unknown";
    std::string ram   = sh("free -h | awk '/Mem:/{print $3\"/\"$2}'");
    std::string cpu   = sh("lscpu | grep 'Model name' | cut -d: -f2-");
    std::string procs = sh("ps -e --no-headers | wc -l"); 
    std::string kernel= sh("uname -r");
    std::string disk  = sh("df -h / | awk 'NR==2{print $4\"/\"$2}'");
    std::string up    = sh("uptime -p");
    std::string gpu   = sh("lspci | grep -i vga | cut -d: -f3-");


   std::cout << gr <<"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⣛⣛⣛⣛⣟⣛⣛⡻⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿ " << gr << username << wh << "@" << gr << hostname() << "\n";

   std::cout << "⣿⣿⣿⣿⣿⣿⣿⢟⣫⣭⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣝⠻⣿⣿⣿⣿⣿⣿ " << wh << "-----------\n" << gr;

   std::cout << "⣿⣿⣿⣿⣿⣿⢇⣼⣿⣿⣿⣿⣿⣠⣤⣤⣛⣻⣿⣿⣿⠿⣿⣿⣜⠻⣿⣿⣿⣿ user: "<< wh << username << gr << "\n";

   std::cout << "⣿⣿⣿⣿⣿⠇⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⣿⣿⣿⣿⣿⣿⣿⣿⡜⢿⣿⣿ os: " << wh << os() << gr << "\n";

   std::cout << "⣿⣿⣿⣿⡟⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣮⣭⣭⣭⣭⣿⣿⣿⡜⣿⣿ hostname: " << wh << hostname() << gr << "\n";

   std::cout << "⣿⣿⣿⣿⢣⣿⣿⣿⣿⣿⣿⡿⣫⣵⣶⣶⣶⣭⣻⢿⣿⣿⣿⣿⢫⣭⣭⣃⢿⣿ kernel: " << wh << kernel << gr << "\n";

   std::cout << "⣿⣿⣿⣿⢸⣿⣿⣿⣿⣿⣿⣷⣿⣿⠿⢿⠿⡿⣿⣦⣹⣿⡟⣱⣾⣿⣿⣿⡆⣿ uptime: " << wh << up << gr << "\n";

   std::cout << "⣿⣿⣿⣿⢸⡏⣴⣶⣦⣤⣭⣉⣭⢰⠒⡒⠒⠶⣶⣌⠛⣛⠻⠟⠩⠭⠭⢭⡅⠹ ram: " << wh << ram << rd << " Used" << gr << "\n";

   std::cout << "⣿⣿⣿⣿⡆⢷⣴⣿⣿⣿⣿⣿⣿⢸⣦⣥⣤⣤⣴⡿⢸⣿⣿⡆⣚⣀⣀⣿⡇  disk: " << wh << disk << gr << " Free" << "\n";

   std::cout << "⣿⣿⣿⣿⣷⡸⣿⡿⣿⣿⠿⣿⣿⣬⣙⣛⣛⣛⣛⣃⣼⣿⡏⣇⠛⡛⠻⠛⡓⠀ " << "\n";

   std::cout << "⣿⣿⣿⣿⣿⣷⡙⣿⣮⡑⠐⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣌⠻⣿⣿⡿⢜⠐ " << "\n";  

   std::cout << "⣿⣿⣿⣿⣿⣿⣷⢹⣿⡩⠈⣛⣿⣿⣿⣿⣿⣿⣅⠶⡿⢻⡿⠟⣱⣿⡿⠷⠁⣼   " << "\n";

   std::cout << "⣿⣿⣿⣿⣿⣿⣿⢸⣿⣟⡅⠉⢻⣿⣿⣿⢩⣾⠟⢫⠥⡍⡛⡓⢟⢻⣇⢋⣸⣿   " << "\n";
 
   std::cout << "⣿⣿⣿⣿⣿⣿⡿⣸⣿⣿⡇⣴⠈⠿⣿⣿⣘⡇⠀⠀⠀⠀⠀⠀⢸⣌⠁⣼⣿⣿   " << "\n";

   std::cout << "⣿⣿⣿⣿⣿⣿⠇⣿⣿⣿⣴⣷⣶⠂⠋⡻⣿⣷⡀⠀⠀⠀⠀⢠⡯⠉⣰⣿⣿⣿   " << "\n";
 
   std::cout << "⣿⣿⣿⣿⣿⡏⣾⣿⣿⡟⢩⣿⣿⣷⣧⠁⡍⢹⣿⡄⠀⢰⣾⡟⡄⣼⣿⣿⣿⣿   " << "\n";

   std::cout << "⣿⣿⡿⠿⠫⣾⣿⡿⢟⣼⣿⣿⣿⣿⣿⣶⣀⣀⠊⢐⢃⣂⡉⠤⠶⠿⠿⠿⢿⣿  " << "\n" ;

  std::cout << "⣯⣴⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣟⣻⢿⣿⠿⣗⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣶    " << "\n";

    return 0;
}