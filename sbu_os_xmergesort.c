/*******************************************************************************
**                                                                            **
** File: sbu_os_xmergesort.c                                                  **
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

#include "sbu_os_xmergesort.h"
#include "sbu_os_xms_utils.h"

asmlinkage extern long (*sysptr)(void *arg);

unsigned int sbu_os_xmergesort(const char *buf1, const char *buf2, int n1, int n2, char *out_buf)
{
	char *line1=NULL, *line2=NULL;
	int l1=0, l2=0, i=0, j=0, k=0, t1=0, t2=0;
	line1 = kmalloc(4096, GFP_KERNEL);
	line2 = kmalloc(4096, GFP_KERNEL);

        while(i<n1 && j<n2) {
                if(!l1) {
        		while(buf1[i] != '\n' && buf1[i] != '\0') 
				line1[l1++] = buf1[i++];
        		line1[l1++] = buf1[i++];
		}
		if(!l2) {
        		while(buf2[j] != '\n' && buf2[j] != '\0') 
				line2[l2++] = buf2[j++];
        		line2[l2++] = buf2[j++];
		}
		if(strcmp(line1, line2) <= 0) {
			while(t1<l1) 
                                out_buf[k++] = line1[t1++];
			l1 = 0;
                	t1 = 0;
		}
		else {
	                while(t2<l2) 
                                out_buf[k++] = line2[t2++];
			l2 = 0;
                	t2 = 0;	
		}
	}
	while(i<n1) 
		out_buf[k++] = buf1[i++];
	while(j<n2) 
		out_buf[k++] = buf2[j++];
	if(l1)
		while(t1<l1)
			out_buf[k++] = line1[t1++];
	if(l2)
		while(t2<l2)
			out_buf[k++] = line1[t2++];
	if(line1)
		kfree(line1);
	if(line2)
		kfree(line2);
	return n1+n2;
}

asmlinkage long xmergesort(void *arg)
{
        int ret = 0;
	int i=0;
	char *buf1=NULL, *buf2=NULL, *out_buf=NULL; 
        int n1=0, n2=0, n3=0; 
	sbu_os_kargs *karg = NULL;
	struct file *ifile1 = NULL, *ifile2 = NULL, *ofile = NULL;
  
	/* No arguments: -EINVAL for NULL */
	if (arg == NULL) {
		printk("No arguments passed: Failed\n");
		return -EINVAL;
        }
	
	/* Allocate the memory for arguments structure. */
	if ((karg = kmalloc(sizeof(sbu_os_kargs), GFP_KERNEL)) == NULL) {
		printk(KERN_ERR "Memory Allocation for kernel arguments: Failed. \n");
		ret = -ENOMEM;
		goto out;
	}

	/* Check the read access permissions of userspace arguments. */
	if(!access_ok(VERIFY_READ, arg, sizeof(sbu_os_kargs))) {
		printk(KERN_ERR "Checking userspace arguments read permissions: Failed. \n");
		ret = -EFAULT;
		goto out;
	}

	/* Get the userspace arguments. */
	if(copy_from_user(karg, (sbu_os_kargs *) arg, sizeof(sbu_os_kargs))!=0) {
		printk(KERN_ERR "Copying the arguments from user: Failed \n");
		ret = -EFAULT;	
		goto out;
	}

	/* Validate the kernelspace arguments. */
	if((karg->ifile1 == NULL) || (karg->ifile2 == NULL) || (karg->ofile == NULL)) {
		printk(KERN_INFO "Checking kernel space arguments validity: Failed. \n");
		ret = -EINVAL;
		goto out;
	}

	/* Open the input/output files. */
        ifile1 = sbu_os_file_open(karg->ifile1, SBU_OS_READ_PERM);
        ifile2 = sbu_os_file_open(karg->ifile2, SBU_OS_READ_PERM);
        ofile = sbu_os_file_open(karg->ofile, SBU_OS_WRITE_PERM);
        if (!ifile1 || !ifile2 || !outfile)
		goto out;

        buf1 = kmalloc(4096*sizeof(char), GFP_KERNEL);
        buf2 = kmalloc(4096*sizeof(char), GFP_KERNEL);
      
	n1 = sbu_os_file_read(ifile1, buf1, 4096);
	n2 = sbu_os_file_read(ifile2, buf2, 4096);

        out_buf = kmalloc(n1+n2, GFP_KERNEL);
        n3 = sbu_os_xmergesort(buf1, buf2, n1, n2, out_buf);

#if 0
	for(i=0;i<n1;i++)
		printk("%c",buf1[i]); 
	for(i=0;i<n2;i++)
		printk("%c",buf2[i]); 
	for(i=0;i<n3;i++)
		printk("%c",out_buf[i]); 
#endif
	n3 = sbu_os_file_write(ofile, out_buf, n3);

        sbu_os_file_close(ifile1);
        sbu_os_file_close(ifile2);
        sbu_os_file_close(ofile);
out:
	if (karg) {
		kfree(karg);
	}
	if(buf1)
		kfree(buf1);
	if(buf2)
		kfree(buf2);
	if(out_buf)
		kfree(out_buf);
        return ret;
}

static int __init init_sys_xmergesort(void)
{
	printk("installed new sys_xmergesort module\n");
	if (sysptr == NULL)
		sysptr = xmergesort;
	return 0;
}

static void  __exit exit_sys_xmergesort(void)
{
	if (sysptr != NULL)
		sysptr = NULL;
	printk("removed sys_xmergesort module\n");
}

module_init(init_sys_xmergesort);
module_exit(exit_sys_xmergesort);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Mallesham Dasari");
