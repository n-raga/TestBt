#include "svn_version.h"

#define TOSTRING2(s) #s
#define TOSTRING(s) TOSTRING2(s)

#define VERSION_MAJOR               1
#define VERSION_MINOR               0
#define VERSION_REVISION            0
#define VERSION_BUILD               SVN_REVISION

#if SVN_LOCAL_MODIFICATIONS
    #define VERSION_MODIFIER        "m"
#else
    #define VERSION_MODIFIER
#endif

#define VER_COMPANY_NAME_STR        "TEXA S.p.A."
#define VER_FILE_DESCRIPTION_STR    "MsBTManager7"
#define VER_FILE_VERSION            VERSION_MAJOR, VERSION_MINOR, VERSION_REVISION, VERSION_BUILD
#define VER_FILE_VERSION_STR        TOSTRING(VERSION_MAJOR)        \
                                    "." TOSTRING(VERSION_MINOR)    \
                                    "." TOSTRING(VERSION_REVISION) \
                                    "." TOSTRING(VERSION_BUILD)    \
                                    VERSION_MODIFIER

#define VER_PRODUCTNAME_STR         "MsBTManager7"
#define VER_PRODUCT_VERSION         VER_FILE_VERSION
#define VER_PRODUCT_VERSION_STR     VER_FILE_VERSION_STR
#define VER_ORIGINAL_FILENAME_STR   VER_PRODUCTNAME_STR ".dll"
#define VER_INTERNAL_NAME_STR       VER_ORIGINAL_FILENAME_STR
#define VER_COPYRIGHT_STR           "Copyright (c) " VER_COMPANY_NAME_STR " 2015-2016"

#ifdef _DEBUG
    #define VER_VER_DEBUG           0x1L
#else
    #define VER_VER_DEBUG           0x0L
#endif

#define VER_FILEOS                  0x4L
#define VER_FILEFLAGS               VER_VER_DEBUG
#define VER_FILETYPE                0x2L
