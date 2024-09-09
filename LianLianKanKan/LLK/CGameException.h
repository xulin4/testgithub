#pragma once
#include <string>
class CGameException : public std::exception {
public:
    CGameException(const std::string& msg) : m_msg(msg) {}

    const char* what() const noexcept override {
        return m_msg.c_str();
    }

private:
    std::string m_msg;
};

