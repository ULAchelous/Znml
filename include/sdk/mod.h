
#ifndef ZNML_SDK_MOD_H
#define ZNML_SDK_MOD_H

#include "../il2cpp/abi.h"
#include <stdint.h>

#pragma pack(push, 1)
typedef struct {        
    char id[64];        
    char name[64];           
    char version[32];         
    char author[64];          
    
    uint32_t target_sdk_ver;
    
    bool (*on_load)(il2cpp_funcs_t* il2cpp_abi);

    void (*on_unload)(void);
} znml_mod_metadata_t;
#pragma pack(pop)

#define MOD_SYMBOL "ZNML_MOD"

#ifdef __cplusplus
#define MOD_DEFINATION extern "C" __attribute__((visibility("default"))) __attribute__((used))
#else
#define MOD_DEFINATION __attribute__((visibility("default"))) __attribute__((used))
#endif

#endif