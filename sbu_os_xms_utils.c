/*******************************************************************************
 * **                                                                            **
 * ** File: sbu_os_xms_utils.c                                                   **
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
 * *******************************************************************************/

#include "sbu_os_xms_utils.h"

/* Function to open the file. */
struct file* sbu_os_file_open(const char* path, sbu_os_rw_perm flags)
{
	struct file* filp = NULL;

	if (flags == SBU_OS_READ_PERM)
		filp = filp_open (path, O_RDONLY, 0);
	if(flags == SBU_OS_WRITE_PERM)
		filp = filp_open (path, O_WRONLY, 0);

	/* Check if the file opened successfully or not. */
	if (!filp) {
		printk(KERN_INFO "Opening file: Failed. \n");
		goto out;
	}

	/* Check if there is an error in file pointer. */
	if (IS_ERR(filp)) {
                printk(KERN_INFO "File error : %d \n", (int) PTR_ERR(filp));
		goto out;
	}

	/* Check if the file is regular or not. */
        if ((!S_ISREG(file_inode(filp)->i_mode))) {
                printk(KERN_INFO "Checking if the file is regular: Failed. \n");
                goto out; 
        }
#if 0
	/* Check read permissions for input files. */
	if (flags == SBU_OS_READ_PERM) {
		if (!(filp->f_mode & FMODE_READ)) {
			printk(KERN_INFO "Input file for read mode: Failed. \n");
			goto out;
		}
		/* Check if the file can be read. */
	        if (!filp->f_op->read) {
	                printk(KERN_INFO "Read file: Failed. \n");
			goto out;
	        }
	}

        /* Check write permissions for the output file. */
	if (flags == SBU_OS_WRITE_PERM) {
		if (!(filp->f_mode & FMODE_WRITE)) {
			printk(KERN_INFO "Output file for write mode: Failed .\n");
			goto out;
		}
		/* Check if the file can be written*/
	        if (!filp->f_op->write) {
        	        printk(KERN_INFO "File write: Failed. \n");
	                goto out;
	        }
	}
#endif
	return filp;
	out:	
		if (filp!= NULL)
			if (!IS_ERR(filp))
				filp_close(filp, NULL);
		return NULL;
}

/* Function to read the file. */
int sbu_os_file_read(struct file* filp, unsigned char* data, unsigned int size)
{
    int bytes = 0;
    mm_segment_t oldfs;
    filp->f_pos = 0;		/* start offset */
    oldfs = get_fs();
    set_fs(KERNEL_DS);
 
    bytes = vfs_read(filp, data, size, &filp->f_pos); 
    set_fs(oldfs);
    return bytes;
}

/* Function to write the file. */
int sbu_os_file_write(struct file* filp, unsigned char* data, unsigned int size)
{
    int bytes = 0;
    mm_segment_t oldfs;
    filp->f_pos = 0;		/* start offset */
    oldfs = get_fs();
    set_fs(KERNEL_DS);
 
    bytes = vfs_write(filp, data, size, &filp->f_pos); 
    set_fs(oldfs);
    return bytes;
}

/* Function to close the file. */
void sbu_os_file_close(struct file* filp)
{
	if (filp!= NULL)
		if (!IS_ERR(filp))
			filp_close(filp, NULL);
}
