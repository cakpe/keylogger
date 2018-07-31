#ifndef HELPER_H
#define HELPER_H

#include <string>
#include <ctime>
#include <sstream> //to convert to strings
#include <fstream>

namespace Helper{
    template <class T> //same as saying typename T

    std::string ToString(const T &);

    struct DateTime{//yes structs can have constructors too

        int D,m,y,H,M,S;

        DateTime(){
            time_t ms; //time_t is a data type in ctime
            time(&ms); //takes the system time and passes it into ms
            struct tm *info = localtime(&ms); //tm is a type from the ctime linrary

            D = info->tm_mday; // D is also an attribute from the struct DateTime. So is tm_day
            m = info->tm_mon + 1;
            y = 1900 + info->tm_year;
            M = info->tm_min;
            H = info->tm_hour;
            S = info->tm_sec;
        }

        DateTime(int D, int m, int y, int H, int M, int S): D(D), m(m), y(y), H(H), M(M), S(S){} //another way of initializing
        DateTime(int D, int m, int y): D(D), m(m), y(y), H(0), M(0), S(0){}

        //to return the date and time of the system
        DateTime Now() const{
            return DateTime();
        }

        std::string GetDateString() const{
            return std::string(D<10?"0":"")+Helper::ToString(D) + std::string(m<10?".0":".") + Helper::ToString(m) +
            "." + Helper::ToString(y);
        }
        std::string GetTimeString(const std::string &sep = ":") const{
            return std::string(H<10?"0":"")+ToString(H)+sep+
                   std::string(M<10?"0":"")+ToString(M)+sep+
                   std::string(S<10?"0":"")+ToString(S);
        }
        std::string GetDateTimeString(const std::string &sep = ":") const{
            return GetDateString() + " " + GetTimeString(sep);
        }

    };

    template <class T>
    std::string ToString(const T &e){
        std::ostringstream s;
        s<<e;
        return s.str();
    }
    //next bit isn't compulsory. Just to record the key logs
    void writeAppLogs(const std::string &s){
        std::ofstream file("AppLogs.txt", std::ios::app);
        file<<"["<<Helper::DateTime().GetDateTimeString()<<"]"<<
        "\n"<<s<<std::endl<<"\n";
        file.close();
    }
}

#endif // HELPER_H
