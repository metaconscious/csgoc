//
// Created by user on 1/18/2023.
//

#ifndef CSGOC_SDK_H
#define CSGOC_SDK_H

#include "IBaseClientDLL.h"
#include "IClientEntityList.h"
#include "NetVars.h"
#include <Windows.h>
#include <compare>
#include <cstdint>
#include <string_view>
#include <type_traits>

using GetInterfaceType = std::add_pointer_t<void* __cdecl(const char* name, int* returnCode)>;

[[nodiscard]] void* getInterface(std::string_view dllName, std::string_view interfaceName)
{
    auto GetInterface{
            reinterpret_cast<GetInterfaceType>(
                    GetProcAddress(
                            GetModuleHandle(dllName.data()),
                            "CreateInterface")) };

    int returnCode{ 0 };

    return GetInterface(interfaceName.data(), &returnCode);
}

[[nodiscard]] uintptr_t getOffset(RecvTable* recvTable,
        std::string_view tableName,
        std::string_view netVarName)
{
    for (std::size_t i{ 0 }; i < recvTable->m_nProps; ++i)
    {
        auto prop{ recvTable->m_pProps[i] };

        if (prop.m_pVarName == netVarName)
        {
            return prop.m_Offset;
        }

        if (prop.m_pDataTable != nullptr)
        {
            auto offset{ getOffset(prop.m_pDataTable, tableName, netVarName) };

            if (offset != 0)
            {
                return offset + prop.m_Offset;
            }
        }
    }
    return 0;
}

[[nodiscard]] uintptr_t getNetVarOffset(ClientClass* clientClass,
        std::string_view tableName,
        std::string_view netVarName)
{
    for (auto currentNode{ clientClass };
         currentNode->m_pNext != nullptr;
         currentNode = currentNode->m_pNext)
    {
        if (currentNode->m_pRecvTable->m_pNetTableName == tableName)
        {
            return getOffset(currentNode->m_pRecvTable, tableName, netVarName);
        }
    }

    return 0;
}

#endif //CSGOC_SDK_H
