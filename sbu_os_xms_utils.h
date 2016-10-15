/*******************************************************************************
**                                                                            **
** File: sbu_os_xms_utils.h                                                   **
**                                                                            **
** Copyright Â© 2016, OS Lab, CSE, Stony Brook University.                    **
** All rights reserved.                                                       **
** http://www.cs.stonybrook.edu                                               **
**                                                                            **
** All information contained herein is property of Stony Brook University     **
** unless otherwise explicitly mentioned.                                     **
**                                                                            **
** The intellectual and technical concepts in this file are proprietary       **
** to SBU and may be covered by granted or in process national                **
** and international patents and are protect by trade secrets and             **
** copyright law.                                                             **
**                                                                            **
** Redistribution and use in source and binary forms of the content in        **
** this file, with or without modification are not permitted unless           **
** permission is explicitly granted by Stony Brook University.                **
**                                                                            **
**                                                                            **
** Project: File MergeSort System Call                                        **
**                                                                            **
** Author(s): Mallesham Dasari                                                **
**                                                                            **
*******************************************************************************/

#ifndef __SBU_OS_XMERGESORT_UTILS_H__
#define __SBU_OS_XMERGESORT_UTILS_H__

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/linkage.h>
#include <linux/moduleloader.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/err.h>

typedef enum sbu_os_rw_perm_ {
	SBU_OS_READ_PERM	= 0,
	SBU_OS_WRITE_PERM	= 1
}sbu_os_rw_perm;

/* Function to open the file. */
struct file* sbu_os_file_open(const char* path, sbu_os_rw_perm flags);

/* Function to read the file. */
int sbu_os_file_read(struct file* file, unsigned char* data, unsigned int size);

/* Function to write into the file. */
int sbu_os_file_write(struct file* file, unsigned char* data, unsigned int size);

/* Function to close the file. */
void sbu_os_file_close(struct file* file);

#endif /* __SBU_OS_SYS_MERGESORT_H__ */

/* EOF */
