/*******************************************************************************
 * **                                                                            **
 * ** File: xhw1.c                                                               **
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

#include "xhw1.h"

#ifndef __NR_xmergesort
#error xmergesort system call not defined
#endif

int main(int argc, char *argv[])
{
	int ret = 0;
	int ch;
        unsigned int flags = 0;
        void *buf = NULL;
        sbu_os_args *arg = NULL;

	if ((argc<3) || (argc>8))  {
		perror("Invalid arguments: Use -h flag for help \n");
		goto out;

	}

        buf = (void *) malloc (sizeof(sbu_os_args));
        arg = (sbu_os_args *) malloc (sizeof(sbu_os_args)); 

        /* Allocate the memory for arguments structure. */
        if ((arg = (sbu_os_args *) malloc(sizeof(sbu_os_args))) == NULL) {
                printf("Memory allocation for user arguments: Failed. \n");
                ret = -ENOMEM;
                goto out;
        }

        /* Allocate the memory for arguments structure. */
        if ((buf = malloc(sizeof(sbu_os_args))) == NULL) {
                printf("Memory allocation for user arguments: Failed. \n");
                ret = -ENOMEM;
                goto out;
        }

	opterr = 0;
 	while((ch = getopt (argc, argv, "uaitd")) != -1) {
		switch(ch) {
			case 'u':
                                flags |= 0x01;
				break;
			case 'a':
                                flags |= 0x02;
				break;
			case 'i':
                                flags |= 0x04;
				break;
			case 't':
                                flags |= 0x10;
				break;
			case 'd':
                                flags |= 0x20;
				break;
			case '?' :
				perror ("Unknown option character.\n");
				goto out;
	
			default :
				printf ("Bad Command Line Arguments. \
						 Use '-h' flag for Help.\n");
				goto out;
		}
	}

	strncpy(arg->ifile1, argv[optind], strlen(argv[optind]));
     	strncpy(arg->ifile2, argv[optind+1], strlen(argv[optind+1]));
     	strncpy(arg->ofile, argv[optind+2], strlen(argv[optind+2]));

	memcpy((void *) buf, (void *) arg, sizeof(sbu_os_args));

  	ret = syscall(__NR_xmergesort, buf);
	if (ret == 0)
		printf("syscall returned %d\n", ret);
	else
		printf("syscall returned %d (errno=%d)\n", ret, errno);

        

out:
        if (arg) {
                free(arg);
        }
        if (buf) {
                free(buf);
        }
        return 0;
}
