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
 * Destructor
 */

yns::String::~String() {
    if (chain == nullptr){
        return;
    }

    Element *runner = chain;

    while (runner->next != nullptr) {
        runner = runner->next;
    }

    while (runner != chain) {
        runner = runner->prev;
        delete[] runner->next->cluster;
        delete runner->next;
    }

    delete[] chain->cluster;
    delete chain;
    chain = nullptr;
}

/**
 * Private methods
 */

void yns::String::addElement() {
    if (chain == nullptr) {
        chain = new Element;
        chain->prev = nullptr;
        chain->cluster = new char[clusterSize];
        chain->next = nullptr;
    } else {
        Element *runner = chain;

        while (runner->next != nullptr) {
            runner = runner->next;
        }

        runner->next = new Element;
        runner->next->prev = runner;
        runner->next->next = nullptr;
        runner->next->cluster = new char[clusterSize];
    }
}

/**
 * Public methods
 *
 */

unsigned int yns::String::length() const {
    Element *runner = chain;
    unsigned int counter = 0;

    while (runner != nullptr) {
        for (int i = 0; (i < clusterSize) && (runner->cluster[i] != '\0'); ++i) {
            counter++;
        }
        runner = runner->next;
    }
    return counter;
}

int yns::String::find(const yns::String subString) {
    unsigned int thisLength = this->length();
    unsigned int subLength = subString.length();
    int i, j;

    if (subLength > thisLength) {
        return -1;
    }

    for (i = 0; i <= (thisLength - subLength); ++i) {
        for (j = 0; (j < subLength) && ((*this)[i + j] == subString[j]); ++j);

        if (j == subLength) {
            return i;
        }
    }

    return -1;
}

bool yns::String::replace(const yns::String &replaceable, const yns::String &string) {
    int replacePos = this->find(replaceable);

    if (replacePos == -1) {
        return false;
    }

    if (replaceable.length() == string.length()) {
        for (int i = 0; i < replaceable.length(); ++i) {
            (*this)[replacePos + i] = string[i];
        }
    } else {

    }

    return true;
}


yns::String &yns::String::operator=(const yns::String &rightStr) {
    this->~String();

    if (rightStr[0] == '\0'){
        return *this;
    }

    if (chain == nullptr) {
        this->addElement();
    }

    Element *runner = chain;
    unsigned int clusterPointer = 0;

    for (int i = 0; i < rightStr.length(); ++i) {
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

yns::String &yns::String::operator=(const char *rightStr) {
    this->~String();

    if (rightStr[0] == '\0'){
        return *this;
    }

    if (chain == nullptr) {
        this->addElement();
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
    this->~String();

    if (rightStr.length() == 0){
        return *this;
    }

    if (chain == nullptr) {
        this->addElement();
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
        runner->cluster[clusterPointer] = '\0';
    }

    return *this;
}

char yns::String::operator[](unsigned int index) const{
    unsigned int length = this->length();

    if ((index >= length) || (chain == nullptr)) {
        return '\0';
    }

    Element *runner = chain;
    unsigned int clusterNumber = (index / this->clusterSize);

    for (int i = 0; i < clusterNumber; ++i) {
        runner = runner->next;
    }

    return runner->cluster[index - (clusterNumber * this->clusterSize)];
}

char &yns::String::operator[](unsigned int index) {
    unsigned int length = this->length();

    if ((index >= length) || (chain == nullptr)) {
        return this->chain->cluster[0];
    }

    Element *runner = chain;
    unsigned int clusterNumber = (index / this->clusterSize);

    for (int i = 0; i < clusterNumber; ++i) {
        runner = runner->next;
    }

    return runner->cluster[index - (clusterNumber * this->clusterSize)];
}


yns::String yns::operator+(const yns::String &leftStr, const yns::String &rightStr) {
    String result = leftStr;

    unsigned int length = result.length();
    unsigned int clusterPointer = 0;
    String::Element *runner = result.chain;

    for (int i = 0; i < (length / result.clusterSize); ++i) {
        runner = runner->next;
    }

    while ((runner->cluster[clusterPointer] != '\0') && (clusterPointer != result.clusterSize)) {
        clusterPointer++;
    }

    for (int j = 0; j < rightStr.length(); ++j) {
        if (clusterPointer == result.clusterSize){
            if (runner->next == nullptr) {
                result.addElement();
            }

            clusterPointer = 0;
            runner = runner->next;
        }

        runner->cluster[clusterPointer++] = rightStr[j];
    }

    if (clusterPointer < (result.clusterSize - 1)) {
        runner->cluster[clusterPointer] = '\0';
    }

    return result;
}

yns::String yns::operator+(const yns::String &leftStr, const std::string &rightStr) {
    String result = leftStr;

    unsigned int length = result.length();
    unsigned int clusterPointer = 0;
    String::Element *runner = result.chain;

    for (int i = 0; i < (length / result.clusterSize); ++i) {
        runner = runner->next;
    }

    while ((runner->cluster[clusterPointer++] != '\0') || (clusterPointer != result.clusterSize));

    for (int j = 0; j < rightStr.length(); ++j) {
        if (clusterPointer == result.clusterSize){
            if (runner->next == nullptr) {
                result.addElement();
            }

            clusterPointer = 0;
            runner = runner->next;
        }

        runner->cluster[clusterPointer++] = rightStr[j];
    }

    if (clusterPointer < (result.clusterSize - 1)) {
        runner->cluster[clusterPointer] = '\0';
    }

    return result;
}

yns::String yns::operator +(const std::string &leftStr, const yns::String &rightStr) {
    String result = rightStr;

    unsigned int length = result.length();
    unsigned int clusterPointer = 0;
    String::Element *runner = result.chain;

    for (int i = 0; i < (length / result.clusterSize); ++i) {
        runner = runner->next;
    }

    while ((runner->cluster[clusterPointer++] != '\0') || (clusterPointer != result.clusterSize));

    for (int j = 0; j < leftStr.length(); ++j) {
        if (clusterPointer == result.clusterSize){
            if (runner->next == nullptr) {
                result.addElement();
            }

            clusterPointer = 0;
            runner = runner->next;
        }

        runner->cluster[clusterPointer++] = leftStr[j];
    }

    if (clusterPointer < (result.clusterSize - 1)) {
        runner->cluster[clusterPointer] = '\0';
    }

    return result;
}

yns::String yns::operator+(const yns::String &leftStr, const char *rightStr) {
    String result = leftStr;

    unsigned int length = result.length();
    unsigned int clusterPointer = 0;
    String::Element *runner = result.chain;

    for (int i = 0; i < (length / result.clusterSize); ++i) {
        runner = runner->next;
    }

    while ((runner->cluster[clusterPointer++] != '\0') || (clusterPointer != result.clusterSize));

    for (int j = 0; j < rightStr[j] != '\0'; ++j) {
        if (clusterPointer == result.clusterSize){
            if (runner->next == nullptr) {
                result.addElement();
            }

            clusterPointer = 0;
            runner = runner->next;
        }

        runner->cluster[clusterPointer++] = rightStr[j];
    }

    if (clusterPointer < (result.clusterSize - 1)) {
        runner->cluster[clusterPointer] = '\0';
    }

    return result;
}

yns::String yns::operator +(const char *leftStr, const yns::String &rightStr) {
    String result = rightStr;

    unsigned int length = result.length();
    unsigned int clusterPointer = 0;
    String::Element *runner = result.chain;

    for (int i = 0; i < (length / result.clusterSize); ++i) {
        runner = runner->next;
    }

    while ((runner->cluster[clusterPointer++] != '\0') || (clusterPointer != result.clusterSize));

    for (int j = 0; j < leftStr[j] != '\0'; ++j) {
        if (clusterPointer == result.clusterSize){
            if (runner->next == nullptr) {
                result.addElement();
            }

            clusterPointer = 0;
            runner = runner->next;
        }

        runner->cluster[clusterPointer++] = leftStr[j];
    }

    if (clusterPointer < (result.clusterSize - 1)) {
        runner->cluster[clusterPointer] = '\0';
    }

    return result;
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
