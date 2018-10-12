//---------------------------------------------------------------------------
//  Copyright (C) Honeywell International, Inc. 2017
//---------------------------------------------------------------------------

#ifndef SRC_HELPERS_INCLUDE_MAKEPATH_H_
#define SRC_HELPERS_INCLUDE_MAKEPATH_H_

#include <sys/types.h>
#include <string.h>
#include "strdupa.h"

#ifdef __cplusplus
extern "C" {
#endif

int     mkpath     (const char *dir, mode_t mode);
int     makepath   (const char *dir);

#ifdef __cplusplus
}
#endif

#endif /* SRC_HELPERS_INCLUDE_MAKEPATH_H_ */
