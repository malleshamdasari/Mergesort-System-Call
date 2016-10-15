/*******************************************************************************
 * **                                                                            **
 * ** File: xhw1.h                                                               **
 * **                                                                            **
 * ** Copyright Â© 2016, OS Lab, CSE, Stony Brook University.                    **
 * ** All rights reserved.                                                       **
 * ** http://www.cs.stonybrook.edu                                               **
 * **                                                                            **
 * ** All information contained herein is property of Stony Brook University     **
 * ** unless otherwise explicitly mentioned.                                     **
 * **                                                                            **
 * ** The intellectual and technical concepts in this file are proprietary       **
 * ** to SBU and may be covered by granted or in process national                **
 * ** and international patents and are protect by trade secrets and             **
 * ** copyright law.                                                             **
 * **                                                                            **
 * ** Redistribution and use in source and binary forms of the content in        **
 * ** this file, with or without modification are not permitted unless           **
 * ** permission is explicitly granted by Stony Brook University.                **
 * **                                                                            **
 * **                                                                            **
 * ** Project: File MergeSort System Call                                        **
 * **                                                                            **
 * ** Author(s): Mallesham Dasari                                                **
 * **                                                                            **
 *********************************************************************************/

#ifndef __SBU_OS_XHW1_H__
#define __SBU_OS_XHW1_H__

#include <asm/unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <sys/mman.h>
#include <openssl/md5.h>

/* Size of the file name. */
#define FILE_NAME_SIZE 128

/* Arguments that are passed from user space. */
typedef struct sbu_os_args_ {
        char ifile1[FILE_NAME_SIZE];
        char ifile2[FILE_NAME_SIZE];
        char ofile[FILE_NAME_SIZE];
        unsigned int flags;
}sbu_os_args;

#endif /* __SBU_OS_XHW1_H__ */

/* EOF */

