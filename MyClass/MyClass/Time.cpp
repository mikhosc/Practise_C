#include <iostream>
#include <cstring>
#include "Time.hpp"

long long TIME::counter = 0;

void TIME::init(long int H, long int M, long int S, char* arr)
{
    printcounter();
    if (arr)
    {
        unsigned long len = strlen(arr);
        Name = new (std::nothrow) char[len+1];
        strcpy(Name, arr);
    }
    else
        Name = nullptr;
    if (!Name)
    
    if (H>0)
        Hours = H;
    else
        Hours = 0;
    if (M>0)
        Minutes = H;
    else
        Minutes = 0;
    if (S>0)
        Seconds = H;
    else
        Seconds = 0;
}

TIME::TIME() noexcept
{
    init();
}

TIME::TIME(char* arr) noexcept
{
    init(0,0,0,arr);
}

TIME::TIME(char* arr, int hours, int minutes, int seconds) noexcept: Hours(hours), Minutes(minutes), Seconds(seconds)
{
    init(hours, minutes, seconds, arr);
}

TIME::TIME(const TIME& time) noexcept
{
    printcounter();
    std::cout<<" Used () operator"<<'\n';
    Seconds = time.Seconds;
    Minutes = time.Minutes;
    Hours = time.Hours;
    delete [] Name; // <- here is a mistake
    if (time.Name != nullptr)
    {
        unsigned long len = strlen(time.Name);
        if (len)
        {
            Name = new (std::nothrow) char[len+1];
            for (int i=0 ; i<len ; i++)
                Name[i] = time.Name[i];
            Name[len] = '\0';
        }
    }
    else
        Name  = nullptr;
}

long TIME::operator()() const
{
    return Seconds + 60*Minutes + 60*60*Hours;
}

TIME& TIME::operator=(const TIME& time) noexcept
{
    std::cout<<" Used = operator"<<'\n';
    if (this == &time)
        return *this;
    
    delete [] Name;
    
    if (time.Name != nullptr)
    {
        unsigned long len = strlen(time.Name);
        if (len)
        {
            Name = new (std::nothrow) char[len+1];
            for (int i=0 ; i<len ; i++)
                Name[i] = time.Name[i];
            Name[len] = '\0';
        }
    }
    else
        Name  = nullptr;
    
    Hours = time.Hours;
    Minutes = time.Minutes;
    Seconds = time.Seconds;
    
    return *this;
}

TIME::~TIME()
{
    if (Name != nullptr)
        std::cout<< "Object '"<< Name << "' Deleted" << '\n';
    else
        std::cout << "Object without name deleted!\n";
    delete[] Name;
    
    counter-=2;
    printcounter();
}

void TIME::fix()
{
    if (Seconds > 59)
    {
        int new_sec = Seconds % 60;
        Minutes += (Seconds - new_sec) / 60;
        Seconds = new_sec;
    }
    
    if (Minutes > 59)
    {
        int new_min = Minutes % 60;
        Hours += (Minutes - new_min) / 60;
        Minutes = new_min;
    }
    
    Hours %= 24;
}


TIME operator+(const TIME &a, const TIME &b)
{
    TIME c;
    c.Seconds = a() + b();
    delete [] c.Name;
    unsigned long len = strlen(a.Name) + strlen(b.Name);
    c.Name = new (std::nothrow) char[len+2];
    
    for (int i=0 ; i< strlen(a.Name)  ; i++)
        c.Name[i] = a.Name[i];
    
    c.Name[strlen(a.Name)] = '+';
    
    for (int i=strlen(a.Name)+1 ; i< len+1; i++)
        c.Name[i] = b.Name[i-strlen(a.Name) -1 ];
    
    c.Name[len+1] = '\0';
    
    c.fix();
    return c;
}

bool operator<(const TIME& a, const TIME& b)
{
    return (a() < b());
}

bool operator>(const TIME& a, const TIME& b)
{
    return (a() > b());
}

bool operator==(const TIME &a, const TIME &b)
{
    if (a() == b())
        return 1;
    else
        return 0;
}

std::ostream& operator<<(std::ostream& out, const TIME& time)
{
    if (time.Name != nullptr)
        out<<"'"<<time.Name<<"'"<<" "; // check if nullptr
    else
        out<< "No name ";
    out<<time.Hours<<":"<<time.Minutes<<":"<<time.Seconds;
    return out;
}

std::istream& operator>>(std::istream& in, TIME &time)
{
    bool condition = 1;
    while (condition)
    {
        std::cout<<"Enter name of your time: ";
        std::string s;
        in >> s;
        unsigned long len = s.length();
        
        if (len)
        {
            delete [] time.Name;
            time.Name = new (std::nothrow) char[len+1];
            for (int i=0 ; i<len ; i++)
                time.Name[i] = s[i];
            time.Name[len] = '\0';
            
            condition = 0;
        }
    }
    
    condition = 1;
    while (condition)
    {
        std::cout<<"Enter hours between 0 and 23 : ";
        in>>time.Hours;
        if (time.Hours<0 || time.Hours>23)
        {
            std::cout<<"Wrong number -> ";
        }
        else
            condition = 0;
    }
    
    condition = 1;
    while (condition)
    {
        std::cout<<"Enter minutes between 0 and 59 : ";
        in>>time.Minutes;
        if (time.Minutes<0 || time.Minutes>59)
        {
            std::cout<<"Wrong number -> ";
        }
        else
            condition = 0;
    }
    
    condition = 1;
    while (condition)
    {
        std::cout<<"Enter seconds between 0 and 59 : ";
        in>>time.Seconds;
        if (time.Seconds<0 || time.Seconds>59)
        {
            std::cout<<"Wrong number -> ";
        }
        else
            condition = 0;
    }
    
    return in;
}

/*
TIME::TIME()
{
    Hours = Minutes = Seconds = 0;
    strcpy(Name, "no_name");
}

TIME::TIME(char name[20], int hours, int minutes, int seconds)
{
    strcpy(Name, name);
    Hours = hours;
    Minutes = minutes;
    Seconds = seconds;
}

void TIME::print() const
{
    cout<<"Name: "<<Name<<" ";
    cout<<Hours<<":"<<Minutes<<":"<<Seconds<<endl;
}

int compare(const TIME &a, const TIME &b)
{
    if ((a.Hours == b.Hours) && (a.Seconds == b.Seconds) && (a.Minutes == b.Minutes))
        return 0;
    
    
    if (a.Hours > b.Hours)
        return 1;
    if (a.Hours < b.Hours)
        return -1;
    
    if (a.Minutes > b.Minutes)
        return 1;
    if (a.Minutes < b.Minutes)
        return -1;
    
    if (a.Seconds > b.Seconds)
        return 1;
    if (a.Seconds < b.Seconds)
        return -1;

    return 0;
}

TIME add(const TIME &a, const TIME &b, char s[20])
{
    TIME c;
    c.Seconds = a.Seconds + b.Seconds;
    c.Minutes = a.Minutes + b.Minutes;
    c.Hours = a.Hours + b.Hours;
    
    strcpy(c.Name, s);
    
    c.check_and_change();
    
    return c;
}

void TIME::read()
{
    cout<<"Enter name of your time: ";
    cin>>Name;
a:
    cout<<"Enter hours between 0 and 23 : ";
    cin>>Hours;
    if (Hours<0 || Hours>23)
    {
        cout<<"Wrong number -> ";
        goto a;
    }
    
b:
    cout<<"Enter minutes between 0 and 59 : ";
    cin>>Minutes;
    if (Minutes<0 || Minutes>59)
    {
        cout<<"Wrong number -> ";
        goto b;
    }

c:
    cout<<"Enter seconds between 0 and 59 : ";
    cin>>Seconds;
    if (Seconds<0 || Seconds>59)
    {
        cout<<"Wrong number -> ";
        goto c;
    }

}*/
