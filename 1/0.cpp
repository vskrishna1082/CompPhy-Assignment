#include <iostream>
#include <iomanip>

int main() {
    std::string Name="Krishna Iyer V S"; // string object in stdlib
    int integer=5;
    float decimal=3.14159;
    double longDecimal=3.14159265;
    std::cout << Name << std::endl;
    std::cout << integer << std::endl;
    std::cout << decimal << std::endl;
    std::cout << std::setprecision(10) << longDecimal << std::endl; // increase precision as std::cout truncates to 6 sig. digits
    return 0;
}
