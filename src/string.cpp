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
    this->chain = nullptr;
}

yns::String::String(const char *initStr) : String(DEFAULT_CLUSTER_SIZE) {
    *this = initStr;
}

yns::String::String(const std::string &initStr) : String(DEFAULT_CLUSTER_SIZE) {
    *this = initStr;
}

yns::String::String(const yns::String &initStr) : String(DEFAULT_CLUSTER_SIZE) {
    *this = initStr;
}

yns::String::String(unsigned int clusterSize, const char *initStr) : String(clusterSize){
    *this = initStr;
}

yns::String::String(unsigned int clusterSize, const std::string &initStr) : String(clusterSize){
    *this = initStr;
}

/**
 * Private methods
 */

void yns::String::addElement() {
    Element *runner = chain;
    while (runner->next != nullptr) {
        runner = runner->next;
    }

    runner->next = new Element;
    runner->next->prev = runner;
    runner->next->next = nullptr;
    runner->next->cluster = new char[clusterSize];
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
    if (rightStr[0] == '\0'){
        return *this;
    }

    if (chain == nullptr) {
        chain = new Element;
        chain->cluster = new char[clusterSize];
    }

    Element *runner = chain;
    unsigned int clusterPointer = 0;

    for (int i = 0; rightStr[i] != '\0'; ++i) {
        if (clusterPointer == clusterSize) {
            if (runner->next == nullptr) {
                this->addElement();
            }

            clusterPointer = 0;
            runner = runner->next;

        }
        runner->cluster[clusterPointer++] = rightStr[i];
    }

    if (clusterPointer < (clusterSize - 1)) {
        runner->cluster[++clusterPointer] = '\0';
    }

    return *this;
}

yns::String &yns::String::operator=(const std::string &rightStr) {
    if (rightStr[0] == '\0'){
        return *this;
    }

    if (chain == nullptr) {
        chain = new Element;
        chain->cluster = new char[clusterSize];
    }

    Element *runner = chain;
    unsigned int clusterPointer = 0;

    for (int i = 0; rightStr[i] != '\0'; ++i) {
        if (clusterPointer == clusterSize) {
            if (runner->next == nullptr) {
                this->addElement();
            }

            clusterPointer = 0;
            runner = runner->next;

        }
        runner->cluster[clusterPointer++] = rightStr[i];
    }

    if (clusterPointer < (clusterSize - 1)) {
        runner->cluster[++clusterPointer] = '\0';
    }

    return *this;
}

yns::String yns::operator+(const yns::String &leftStr, const yns::String &rightStr) {
    return yns::String();
}

yns::String yns::operator+(const yns::String &leftStr, const std::string &rightStr) {
    return yns::String();
}

yns::String yns::operator+(const yns::String &leftStr, const char *rightString) {
    return yns::String();
}

char *yns::operator+(char *leftString, const yns::String &rightString) {
    return nullptr;
}

std::string yns::operator+(const std::string &leftString, const yns::String &rightString) {
    return std::string();
}

std::ostream &yns::operator<<(std::ostream &os, const yns::String &str) {
    if (str.chain == nullptr) {
        return os;
    }

    String::Element *runner = str.chain;

    while (runner != nullptr) {
        for (int i = 0; (runner->cluster[i] != '\0') && (i < str.clusterSize); ++i) {
            char temp = runner->cluster[i];
            os << temp;
        }

        runner = runner->next;
    }
    return os;
}



