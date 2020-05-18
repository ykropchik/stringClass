//
// Created by YKROPCHIK on 14.05.2020.
//

#include "string.h"

/**
 * Constructors
 */

yns::String::String() {
    String(7);
};

yns::String::String(unsigned int clusterSize) {
    this->clusterSize = clusterSize;
    this->chain = new Element;
    this->chain->prev = nullptr;
    this->chain->cluster = new char[clusterSize];
    this->chain->next = nullptr;
}

yns::String::String(unsigned int clusterSize, char *initStr) {

}

yns::String::String(unsigned int clusterSize, const std::string &initStr) {

}

yns::String::String(const yns::String &string) {

}

/**
 * Private methods
 */

void yns::String::addElement() {

}

/**
 * Public methods
 *
 */

unsigned int yns::String::getLength() {
    return 0;
}

bool yns::String::find(const yns::String &subString) {
    return false;
}

bool yns::String::replace(const yns::String &subString, const String &string) {
    return false;
}


yns::String &yns::String::operator=(const yns::String &rightStr) {
    return *this;
}

yns::String yns::operator+(const String &leftStr, const yns::String &rightStr) {
    return yns::String(0);
}

yns::String yns::operator+(const String &leftStr, const std::string &rightStr) {
    return yns::String(0);
}

yns::String yns::operator+(const yns::String &leftStr, const char *rightString) {
    return yns::String(0);
}

char *yns::operator+(char *leftString, const yns::String &rightString) {
    return nullptr;
}

std::string yns::operator+(std::string leftString, const yns::String &rightString) {
    return std::string();
}

std::ostream &yns::operator<<(std::ostream &os, const yns::String &str) {
    return os;
}




