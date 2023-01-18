//
// Created by user on 1/18/2023.
//

#ifndef CSGOC_IBASECLIENTDLL_H
#define CSGOC_IBASECLIENTDLL_H

#include "NetVars.h"

class IBaseClientDLL
{
public:
    // Called once when the client DLL is loaded
    virtual int Init(void* appSystemFactory,
            void* physicsFactory,
            void* pGlobals) = 0;

    virtual void PostInit() = 0;

    // Called once when the client DLL is being unloaded
    virtual void Shutdown() = 0;

    // Called once the client is initialized to setup client-side replay interface pointers
    virtual bool ReplayInit(void* replayFactory) = 0;

    virtual bool ReplayPostInit() = 0;

    // Called at the start of each level change
    virtual void LevelInitPreEntity(char const* pMapName) = 0;

    // Called at the start of a new level, after the entities have been received and created
    virtual void LevelInitPostEntity() = 0;

    // Called at the end of a level
    virtual void LevelShutdown() = 0;

    // Request a pointer to the list of client datatable classes
    virtual ClientClass* GetAllClasses() = 0;
};

#endif //CSGOC_IBASECLIENTDLL_H
