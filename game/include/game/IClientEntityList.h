//
// Created by user on 1/18/2023.
//

#ifndef CSGOC_ICLIENTENTITYLIST_H
#define CSGOC_ICLIENTENTITYLIST_H

class IClientEntityList
{
public:
    virtual void* GetClientNetworkable(int entnum) = 0;

    virtual void* GetClientNetworkableFromHandle(int hEnt) = 0;

    virtual void* GetClientUnknownFromHandle(int hEnt) = 0;

    // NOTE: This function is only a convenience wrapper.
    // It returns GetClientNetworkable( entnum )->GetIClientEntity().
    virtual void* GetClientEntity(int entnum) = 0;

    virtual void* GetClientEntityFromHandle(int hEnt) = 0;

    virtual int NumberOfEntities(bool bIncludeNonNetworkable) = 0;

    virtual int GetHighestEntityIndex() = 0;

    virtual void SetMaxEntities(int maxents) = 0;

    virtual int GetMaxEntities() = 0;
};

#endif //CSGOC_ICLIENTENTITYLIST_H
