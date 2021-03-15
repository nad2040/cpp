#include "BufferReader.h"
#include <iostream>
#include <cassert>

void BufferReader::readBuffer() {
    std::string line;
    std::getline(std::cin, line);
    buffer_ += line;
}

int listEnd(std::string& buffer, int pos) {
    assert(buffer[pos] == '(');
    int idx = pos+1;
    int count = 1;
    while (idx < buffer.size()) {
        if (buffer[idx] == '(') ++count;
        else if (buffer[idx] == ')') --count;
        if (count == 0) return ++idx;
        ++idx;
    }
    return pos;
}

int atomEnd(std::string& buffer, int pos) {
    assert(!isspace(buffer[pos]));
    int idx = pos+1;
    while (idx < buffer.size() && !isspace(buffer[idx])) ++idx;
    return idx;
}

std::string BufferReader::nextExpression() {
    //return empty when no full expression in buffer
    //std::cout << "readPos:" << readPos_ << " current buffer:" << buffer_ << '\n';
    while (readPos_ < buffer_.size()) {
        if (isspace(buffer_[readPos_])) ++readPos_;
        else if (buffer_[readPos_] == '(') {
            int listBeg = readPos_;
            int listEnd = ::listEnd(buffer_, listBeg);
            //std::cout << "list begin:" << listBeg << " end:" << listEnd << '\n';
            if (listBeg != listEnd) {
                readPos_ = listEnd;
                return buffer_.substr(listBeg, listEnd);
            }
            return "";
        } else {
            int atomBeg = readPos_;
            int atomEnd = ::atomEnd(buffer_, atomBeg);
            if (atomBeg != atomEnd) {
                readPos_ = atomEnd;
                return buffer_.substr(atomBeg, atomEnd);
            }
            return "";
        }
        ++readPos_;
    }
    return "";
}

