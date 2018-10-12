#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include <string>

#include <stdint.h>

void reset_to_boot_code_hard(void);
void prepare_shutdown(void);
void system_shutdown(void);

struct bsp_version {
	uint32_t major;
	uint32_t minor;
	uint32_t patch;
};
struct bsp_version get_bsp_version(void);

std::string get_bootloader_bsp_number(void);
std::string get_rootfs_bsp_number(void);
std::string get_time_stamp(void);
void get_bsp_rev(char * s,int size); //this returns the entire version string see get_bsp_version for format

unsigned int get_comp_id(void);

struct module_version {
	uint32_t major;
	uint32_t minor;
	uint32_t patch;
	uint32_t build;
};
struct module_version get_module_version(const char *module_name);

#endif
