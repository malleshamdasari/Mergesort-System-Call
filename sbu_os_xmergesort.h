/*******************************************************************************
**                                                                            **
** File: sbu_os_xmergesort.h                                                  **
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

#ifndef __SBU_OS_SYS_MERGESORT_H__
#define __SBU_OS_SYS_MERGESORT_H__

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/linkage.h>
#include <linux/moduleloader.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/err.h>

/* Size of the file name. */
#define FILE_NAME_SIZE 128

/* Used for Debugging. Borrowed from Dr. Erez's lecture. */
#define UDBG printk(KERN_DEFAULT "DBG:%s:%s:%d\n", __FILE__, __func__, __LINE__)

/* Arguments that are passed from user space. */
typedef struct sbu_os_kargs_ {
	char ifile1[FILE_NAME_SIZE];
	char ifile2[FILE_NAME_SIZE];
	char ofile[FILE_NAME_SIZE];
}sbu_os_kargs;

#endif /* __SBU_OS_SYS_MERGESORT_H__ */

/* EOF */
