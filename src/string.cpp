//
// Created by YKROPCHIK on 14.05.2020.
//

#include "string.h"

/**
 * Constructors
 */

yns::String::String() : String(DEFAULT_CLUSTER_SIZE){};

yns::String::String(unsigned int clusterSize) {
    this->clusterSize = clusterSize;
    this->chain = new Element;
    this->chain->prev = nullptr;
    this->chain->cluster = new char[clusterSize];
    this->chain->next = nullptr;
}

yns::String::String(unsigned int clusterSize, const char *initStr) : String(clusterSize){
    *this = initStr;
}

yns::String::String(unsigned int clusterSize, const std::string &initStr) : String(clusterSize){
    *this = initStr;
}

yns::String::String(const yns::String &initStr) : String(DEFAULT_CLUSTER_SIZE) {
    *this = initStr;
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
    if (this == &rightStr) {
        return *this;
    }

    return *this;
}

yns::String &yns::String::operator=(const char *rightStr) {
    return *this;
}

yns::String &yns::String::operator=(const std::string &rightStr) {
    return *this;
}

yns::String yns::operator+(const yns::String &leftStr, const yns::String &rightStr) {
    return yns::String(0);
}

yns::String yns::operator+(const yns::String &leftStr, const std::string &rightStr) {
    return yns::String(0);
}

yns::String yns::operator+(const yns::String &leftStr, const char *rightString) {
    return yns::String(0);
}

char *yns::operator+(char *leftString, const yns::String &rightString) {
    return nullptr;
}

std::string yns::operator+(const std::string &leftString, const yns::String &rightString) {
    return std::string();
}

std::ostream &yns::operator<<(std::ostream &os, const yns::String &str) {
    return os;
}


