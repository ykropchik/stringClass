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

int yns::String::find(const yns::String &subString, unsigned int position) {
    if (this->length() == 0) {
        return -1;
    }

    if (position > (this->length() - subString.length())) {
        return -1;
    }

    unsigned int thisLength = this->length();
    unsigned int subLength = subString.length();
    int i, j;

    if (subLength > thisLength) {
        return -1;
    }

    for (i = position; i <= (thisLength - subLength); ++i) {
        for (j = 0; (j < subLength) && ((*this)[i + j] == subString[j]); ++j);

        if (j == subLength) {
            return i;
        }
    }

    return -1;
}

bool yns::String::replace(const yns::String &replaceable, const yns::String &string) {
    int replacePos = this->find(replaceable, 0);

    if (replacePos == -1) {
        return false;
    }

    while (replacePos != -1) {
        if (replaceable.length() == string.length()) {
            for (int i = 0; i < replaceable.length(); ++i) {
                (*this)[replacePos + i] = string[i];
            }
        } else {
            String result(this->clusterSize);

            for (int i = 0; i < replacePos; ++i) {
                result = result + (*this)[i];
            }

            for (int j = 0; j < string.length(); ++j) {
                result = result + string[j];
            }

            for (int k = (int) (replaceable.length() + replacePos); k < this->length(); ++k) {
                result = result + (*this)[k];
            }

            this->~String();
            *this = result;
        }

        replacePos = this->find(replaceable, (replacePos + string.length()));
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

    if (clusterPointer < clusterSize) {
        runner->cluster[clusterPointer] = '\0';
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

    if (clusterPointer < clusterSize) {
        runner->cluster[clusterPointer] = '\0';
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

    if (clusterPointer < clusterSize) {
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
    if (leftStr[0] == '\0') {
        return rightStr;
    }

    if (rightStr[0] == '\0') {
        return leftStr;
    }

    String result = leftStr;
    unsigned int length = result.length();
    unsigned int clusterPointer = 0;
    String::Element *runner = result.chain;

    for (int i = 0; i < ((length - 1) / result.clusterSize); ++i) {
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
    if (leftStr[0] == '\0') {
        return String(rightStr);
    }

    if (rightStr[0] == '\0') {
        return leftStr;
    }

    String result = leftStr;
    unsigned int length = result.length();
    unsigned int clusterPointer = 0;
    String::Element *runner = result.chain;

    for (int i = 0; i < ((length - 1) / result.clusterSize); ++i) {
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

yns::String yns::operator +(const std::string &leftStr, const yns::String &rightStr) {
    if (leftStr[0] == '\0') {
        return rightStr;
    }

    if (rightStr[0] == '\0') {
        return String(leftStr);
    }

    String result = leftStr;
    unsigned int length = result.length();
    unsigned int clusterPointer = 0;
    String::Element *runner = result.chain;

    for (int i = 0; i < ((length - 1) / result.clusterSize); ++i) {
        runner = runner->next;
    }

    while ((runner->cluster[clusterPointer] != '\0') && (clusterPointer != result.clusterSize)) {
        clusterPointer++;
    }

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
    if (leftStr[0] == '\0') {
        return String(rightStr);
    }

    if (rightStr[0] == '\0') {
        return leftStr;
    }

    String result = leftStr;
    unsigned int length = result.length();
    unsigned int clusterPointer = 0;
    String::Element *runner = result.chain;

    for (int i = 0; i < ((length - 1) / result.clusterSize); ++i) {
        runner = runner->next;
    }

    while ((runner->cluster[clusterPointer] != '\0') && (clusterPointer != result.clusterSize)) {
        clusterPointer++;
    }

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

yns::String yns::operator+(const yns::String &leftStr, const char &rightStr) {
    if (leftStr[0] == '\0') {
        return String(new char[2] {rightStr, '\0'});
    }

    if (rightStr == '\0') {
        return leftStr;
    }

    String result = leftStr;
    unsigned int length = result.length();
    unsigned int clusterPointer = 0;

    String::Element *runner = result.chain;

    for (int i = 0; i < ((length - 1) / result.clusterSize); ++i) {
        runner = runner->next;
    }

    while ((runner->cluster[clusterPointer] != '\0') && (clusterPointer != result.clusterSize)) {
        clusterPointer++;
    }

    if (clusterPointer == result.clusterSize){
        if (runner->next == nullptr) {
            result.addElement();
        }

        clusterPointer = 0;
        runner = runner->next;
    }

    runner->cluster[clusterPointer++] = rightStr;

    if (clusterPointer < (result.clusterSize - 1)) {
        runner->cluster[clusterPointer] = '\0';
    }

    return result;
}

yns::String yns::operator +(const char *leftStr, const yns::String &rightStr) {
    if (leftStr[0] == '\0') {
        return rightStr;
    }

    if (rightStr[0] == '\0') {
        return String(leftStr);
    }

    String result = leftStr;
    unsigned int length = result.length();
    unsigned int clusterPointer = 0;
    String::Element *runner = result.chain;

    for (int i = 0; i < ((length - 1) / result.clusterSize); ++i) {
        runner = runner->next;
    }

    while ((runner->cluster[clusterPointer] != '\0') && (clusterPointer != result.clusterSize)) {
        clusterPointer++;
    }

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

std::ostream &yns::operator<<(std::ostream &os, const yns::String &string) {
    if (string.chain == nullptr) {
        return os;
    }

    String::Element *runner = string.chain;

    while (runner != nullptr) {
        for (int i = 0; (runner->cluster[i] != '\0') && (i < string.clusterSize); ++i) {
            char temp = runner->cluster[i];
            os << temp;
        }

        runner = runner->next;
    }
    return os;
}