/*
 * Copyright (c) 2013-2019 Huawei Technologies Co., Ltd. All rights reserved.
 * Copyright (c) 2020-2021 Huawei Device Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 * conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 * of conditions and the following disclaimer in the documentation and/or other materials
 * provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific prior written
 * permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "It_vfs_jffs.h"

static UINT32 TestCase(VOID)
{
    INT32 fd = -1;
    INT32 ret, len;
    INT32 i = 0;
    CHAR pathname1[JFFS_NAME_LIMITTED_SIZE] = { JFFS_PATH_NAME0 };
    CHAR pathname2[JFFS_STANDARD_NAME_LENGTH] = { JFFS_PATH_NAME0 };
    DIR *dir = NULL;

    ret = mkdir(pathname1, HIGHEST_AUTHORITY);
    ICUNIT_GOTO_EQUAL(ret, 0, ret, EXIT);

    ret = chdir(pathname1);
    ICUNIT_GOTO_EQUAL(ret, 0, ret, EXIT);

    strcat_s(pathname1, JFFS_NAME_LIMITTED_SIZE, "/test");
    while (i < 280) { // loop times: 280
        i++;
        strcat_s(pathname1, JFFS_NAME_LIMITTED_SIZE, "t");
    }

    dir = opendir(pathname1);
    ICUNIT_GOTO_EQUAL(dir, NULL, dir, EXIT2);

    ret = mkdir(pathname1, HIGHEST_AUTHORITY);
    ICUNIT_GOTO_EQUAL(ret, -1, ret, EXIT1);

    dir = opendir(pathname1);
    ICUNIT_GOTO_EQUAL(dir, NULL, dir, EXIT2);

    ret = rmdir(pathname1);
    ICUNIT_GOTO_EQUAL(ret, -1, ret, EXIT1);

    ret = chdir(JFFS_MAIN_DIR0);
    ICUNIT_GOTO_EQUAL(ret, JFFS_NO_ERROR, ret, EXIT2);

    ret = rmdir(pathname2);
    ICUNIT_GOTO_EQUAL(ret, 0, ret, EXIT);

    return JFFS_NO_ERROR;

EXIT2:
    closedir(dir);
EXIT1:
    rmdir(pathname1);
EXIT:
    rmdir(pathname2);
    return JFFS_NO_ERROR;
}

VOID ItFsJffsPressure313(VOID)
{
    TEST_ADD_CASE("ItFsJffsPressure313", TestCase, TEST_VFS, TEST_JFFS, TEST_LEVEL3, TEST_PRESSURE);
}
