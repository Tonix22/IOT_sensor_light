#ifndef MEMORY_ADMIN_H
#define MEMORY_ADMIN_H

// =============================================================================
// DEFINES
// =============================================================================
#define DEBUG_RGB() printf("[%d, ",(LedStick->feature_collection[feature]->back()).RED);\
                    printf(",%d, ",(LedStick->feature_collection[feature]->back()).GREEN);\
                    printf(",%d], ",(LedStick->feature_collection[feature]->back()).BLUE);

// =============================================================================
// EVENT GROUPS BITS DEFINES
// =============================================================================
#define BAD_FORMAT BIT0
#define EMPTYFILE  BIT1

#ifdef __cplusplus
extern "C" 
{
#endif
    // =============================================================================
    // C INCLUDES
    // =============================================================================
    #include "structs.h"
    #include "FreeRTOS_wrapper.h"
    // =============================================================================
    // C Function prototypes
    // =============================================================================
    EventBits_t file_exist(feature_t feature);
    void file_read(feature_t feature);
    void init_flash_status_group(void);
    #ifdef __cplusplus
    // =============================================================================
    // C++ INCLUDES
    // =============================================================================
    #include "file_system.h"
    
}
    #endif


#endif
