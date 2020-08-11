#ifndef FILEYSYSTEM_H
#define FILEYSYSTEM_H


#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "esp_err.h"
#include "esp_log.h"
#include "esp_spiffs.h"

#define MAX_FILES 5
#define MAX_NAME_SIZE 17

#define BASE_PATH "/spiffs"

#define DIR(NAME) BASE_PATH"/"#NAME".bin"

#define IDLE_FILE DIR(IDLE) // /spiffs/IDLE.txt
#define RITH_FILE DIR(RITH) // /spiffs/RITH.txt
#define CIRC_FILE DIR(CIRC) // /spiffs/CIRC.txt
#define LINE_FILE DIR(LINE) // /spiffs/LINE.txt



typedef enum
{
    WRITE,
    READ,
}File_action;

struct
{
    uint8_t R;
    uint8_t G;
    uint8_t B;
    uint32_t time_ms;
}typedef Data;

void clear_file_cursor();
void save_current_pos();
void load_curren_pos();
void file_system_init();
void deinit();
bool check_file_exist(const char* name);
void delete_file(const char* name);
void file_open(File_action r_w, const char* name);
void write_chunck(void* data, char data_type_size, int data_size);
bool read_chunk(void* data, char data_type_size,char num_of_elements);
void read_line();
void write_format_string(const char* format, ...);
void close_file();
void write_to_idle();
void write_to_rith();
//void Example1();
//void Example_struct();



#endif