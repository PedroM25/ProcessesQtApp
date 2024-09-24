#pragma once

#include <set>

#include "ProcessInfo.h"

struct AddRemoveProcsStruct{

public:
    AddRemoveProcsStruct() = default;
    AddRemoveProcsStruct(std::set<ProcessInfo> toAdd, std::set<ProcessInfo> toRemove) : m_toAdd(toAdd), m_toRemove(toRemove) {}

    const std::set<ProcessInfo>& getToAdd(){
        return m_toAdd;
    }

    const std::set<ProcessInfo>& getToRemove(){
        return m_toRemove;
    }

private:
    std::set<ProcessInfo> m_toAdd;
    std::set<ProcessInfo> m_toRemove;
};
