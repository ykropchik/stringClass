//
// Created by YKROPCHIK on 14.05.2020.
//
#include "iostream"
#include "string"

#define DEFAULT_CLUSTER_SIZE 7

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
        explicit String(unsigned int clusterSize);
        String(const char *initStr);
        String(const std::string &initStr);
        String(const String &string);
        String(unsigned int clusterSize, const char *initStr);
        String(unsigned int clusterSize, const std::string &initStr);

        unsigned int getLength();
        bool find(const String &subString);
        bool replace(const String &subString, const String &string);


        String &operator =(const String &rightStr);
        String &operator =(const char *rightStr);
        String &operator =(const std::string &rightStr);
        friend String operator +(const String &leftStr, const String &rightStr);
        friend String operator +(const String &leftStr, const std::string &rightStr);
        friend String operator +(const String &leftStr, const char *rightString);
        friend std::ostream& operator <<(std::ostream &os, const String &str);
        friend char* operator +(char *leftString, const String &rightString);
        friend std::string operator +(const std::string &leftString, const String &rightString);
    };
}
