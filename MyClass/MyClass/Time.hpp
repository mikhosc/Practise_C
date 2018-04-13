#ifndef Time_hpp
#define Time_hpp

#include <stdio.h>
#include <cstring>

class TIME{
private:
    char* Name; //dynamicly allocateed array of characters
    long int Hours; //0-23
    long int Minutes; //0-59
    long int Seconds; //0-59
    void init(long int H=0, long int M=0, long int S=0, char* arr=nullptr );
    void fix(); //changing values so as TIME is in right format
    long operator()() const; //returning number of Seconds
    inline void printcounter() {counter++; std::cout<<"counter count: "<<counter<<'\n';};
    static long long counter; //counter of current objects
public:
    explicit TIME(char* arr, int hours, int minutes, int seconds) noexcept;
    explicit TIME(char* arr) noexcept;
    explicit TIME() noexcept;
    ~TIME();
    TIME& operator=(const TIME&) noexcept;
    TIME(const TIME&) noexcept;
    friend std::ostream& operator<<(std::ostream& out, const TIME& time);
    friend std::istream& operator>>(std::istream& in, TIME &time);
    friend TIME operator+(const TIME &a, const TIME &b);
    friend bool operator==(const TIME &a, const TIME &b);
    friend bool operator<(const TIME& a, const TIME& b);
    friend bool operator>(const TIME& a, const TIME& b);
};
#endif /* Time_hpp */
