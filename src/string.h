//
// Created by YKROPCHIK on 14.05.2020.
//
#include "string"

namespace yns{
    class String {
    private:
        struct Element {
            Element *prev;
            char *cluster;
            Element * next;
        };

        unsigned int clusterSize;
        Element *chain;

        void addElement();

    public:
        String();
        String(unsigned int clusterSize);
        String(unsigned int clusterSize, char *initStr);
        String(unsigned int clusterSize, const std::string &initStr);
        String(const String &string);
        unsigned int getLength();
        bool find(const String &subString);
        bool replace(const String &subString, const String &string);


        String& operator =(const String &rightStr);
        friend String operator +(const String &leftStr, const String &rightStr);
        friend String operator +(const String &leftStr, const std::string &rightStr);
        friend String operator +(const String &leftStr, const char *rightString);
        friend std::ostream& operator <<(std::ostream &os, const String &str);
        friend char* operator +(char *leftString, const String &rightString);
        friend std::string operator +(std::string leftString, const String &rightString);
    };
}
