#include <fstream>

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "logging.h"
#include "system.h"
#include <thread>

#define LOG_TAG "HelpersSystem"

void reset_to_boot_code_hard(void)
{
	sync();	//force all pending write to disk
	system("reboot");
	while(1)
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

void prepare_shutdown(void)
{
	sync();	//force all pending write to disk
}

void system_shutdown(void)
{
	system("halt");
	while(1)
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

struct bsp_version get_bsp_version(void)
{
	// BSP version can be found in /etc/version
	// The first line has this format:
	//   poky-gen7 11.0.0 (dirty build)

	struct bsp_version version = {0,0,0};
	std::string s;

	std::ifstream is("/etc/version");
	if (is.is_open()) {
		is >> s >> version.major >> s >> version.minor >> s >> version.patch;
	}

	return version;
}

std::string get_bootloader_bsp_number(void)
{
	std::string bsp_number = "";
	std::string command = "fw_printenv | grep bsp_number | cut -d = -f 2";

	FILE *in = popen((const char*)command.c_str(), "r");
	if(!in) {
		log_print(LOG_ERR, LOG_TAG, "popen failed: %s", command.c_str());
		return bsp_number;
	}
	char in_buff[32];
	if(fgets(in_buff, sizeof(in_buff), in) == NULL) {
		log_print(LOG_ERR, LOG_TAG, "fgets failed: %s", command.c_str());
	}
	int ret = pclose(in);
	if(ret != 0) {
		log_print(LOG_ERR, LOG_TAG,
				"process exit error: %s returned %d",
				command.c_str(), ret);
		return bsp_number;
	}

	bsp_number += in_buff;

	//rtrim bsp_number
	const char* ws = " \t\n\r\f\v";
	bsp_number.erase(bsp_number.find_last_not_of(ws) + 1);

	return bsp_number;
}

std::string get_time_stamp(void)
{
	std::string s = "";
	std::string filename = "/etc/timestamp";
	std::ifstream istrm(filename);

	if (!istrm.is_open()) {
		log_print(LOG_ERR, LOG_TAG,
				"/etc/timestamp open failed: %d - %s",
				errno, strerror(errno));
	} else {
		istrm >> s;
		s.insert(4,"-");
		s.insert(7,"-");
		s.insert(10," ");
		s.insert(13,":");
		s.insert(16,":");
	}

	return s;
}

std::string get_rootfs_bsp_number(void)
{
	std::string s = "";
	std::string filename = "/etc/bsp-number";
	std::ifstream istrm(filename);

	if (!istrm.is_open()) {
		log_print(LOG_ERR, LOG_TAG,
				"/etc/bsp-number open failed: %d - %s",
				errno, strerror(errno));
	} else {
		istrm >> s;
	}

	return s;
}

unsigned int get_comp_id(void)
{
	int fd;
	unsigned int comp_id = 1234; //ID of prototype boards

	fd = open("/sys/firmware/devicetree/base/comp-id", O_RDONLY);
	if (fd == -1) {
		//version file not found, kernel driver may not have yet a version
		return comp_id;
	}

	char comp_id_attr[32];
	ssize_t size = read(fd, comp_id_attr, 32);
	close(fd);

	if(size <= 0)
		throw std::runtime_error("read_module_version read error");

	comp_id_attr[size] = 0;

	sscanf(comp_id_attr, "%d", &comp_id);

	return comp_id;
}

struct module_version get_module_version(const char *module_name)
{
	int fd;
	char version_path[64];
	struct module_version version = {0,0,0,0};

	sprintf(version_path, "/sys/module/%s/version", module_name);
	fd = open(version_path, O_RDONLY);
	if (fd == -1) {
		//version file not found, kernel driver may not have yet a version
		return version;
	}

	char version_attr[32];
	ssize_t size = read(fd, version_attr, 32);
	close(fd);

	if(size <= 0)
		throw std::runtime_error("read_module_version read error");

	version_attr[size] = 0;

	sscanf(version_attr, "%d.%d.%d.%d",
			&version.major,
			&version.minor,
			&version.patch,
			&version.build);

	return version;
}
void get_bsp_rev(char * s,int size) //this returns the entire version string see get_bsp_version for format
{
	std::string filename = "/etc/version";
	std::ifstream istrm(filename);

	if (!istrm.is_open()) {
		log_print(LOG_ERR, LOG_TAG,
				"/etc/version open failed: %d - %s",
				errno, strerror(errno));
	} else {
		istrm.getline(s,size);
	}
}
