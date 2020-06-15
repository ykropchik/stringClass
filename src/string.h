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

        ~String();

        unsigned int length() const;
        int find(const String subString);
        bool replace(const String &replaceable, const String &string);


        String &operator =(const String &rightStr);
        String &operator =(const char *rightStr);
        String &operator =(const std::string &rightStr);
        char operator[](unsigned int index) const;
        char &operator[](unsigned int index);
        friend yns::String operator +(const String &leftStr, const String &rightStr);
        friend yns::String operator +(const String &leftStr, const std::string &rightStr);
        friend yns::String operator +(const std::string &rightStr, const String &leftStr);
        friend yns::String operator +(const String &leftStr, const char *rightStr);
        friend yns::String operator +(const char *rightStr, const String &leftStr);
        friend std::ostream& operator <<(std::ostream &os, const String &str);
    };


}
