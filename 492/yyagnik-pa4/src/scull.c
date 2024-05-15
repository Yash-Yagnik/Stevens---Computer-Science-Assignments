#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/wait.h>
#include "scull.h"
#include <pthread.h>

#define CDEV_NAME "/dev/scull"

/* Quantum command line option */
static int g_quantum;
struct task_info curr_task;
struct task_info thread;

pthread_t all_threads_list[4];
int fd_args[4];

void* helper(void* args){ // This is a function for creating the helper 
	
	int* curr_thread = (int*) args;
	for (int i = 0; i < 2; i++){
		ioctl(*curr_thread, SCULL_IOCIQUANTUM, &thread);
		printf("state %d, cpu %d, prio %d, pid %d, tgid %d, nv %ld, niv %ld\n", thread.__state, thread.cpu, thread.prio, thread.pid, thread.tgid, thread.nvcsw, thread.nivcsw);
	}
	return NULL;
}
static void usage(const char *cmd)
{
	printf("Usage: %s <command>\n"
	       "Commands:\n"
	       "  R          Reset quantum\n"
	       "  S <int>    Set quantum\n"
	       "  T <int>    Tell quantum\n"
	       "  G          Get quantum\n"
	       "  Q          Query quantum\n"
	       "  X <int>    Exchange quantum\n"
	       "  H <int>    Shift quantum\n"
	       "  h          Print this message\n", // Might have to add i into the usage case and
	       cmd);
}

typedef int cmd_t;

static cmd_t parse_arguments(int argc, const char **argv)
{
	cmd_t cmd;

	if (argc < 2) {
		fprintf(stderr, "%s: Invalid number of arguments\n", argv[0]);
		cmd = -1;
		goto ret;
	}

	/* Parse command and optional int argument */
	cmd = argv[1][0];
	switch (cmd) {
	case 'S':
	case 'T':
	case 'H':
	case 'X':
		if (argc < 3) {
			fprintf(stderr, "%s: Missing quantum\n", argv[0]);
			cmd = -1;
			break;
		}
		g_quantum = atoi(argv[2]);
		break;
	case 'R':
	case 'G':
	case 'Q':
	case 'h':
	case 'p':
	case 't':
	case 'i':
		break;
	default:
		fprintf(stderr, "%s: Invalid command\n", argv[0]);
		cmd = -1;
	}

ret:
	if (cmd < 0 || cmd == 'h') {
		usage(argv[0]);
		exit((cmd == 'h')? EXIT_SUCCESS : EXIT_FAILURE);
	}
	return cmd;
}

static int do_op(int fd, cmd_t cmd)
{
	int ret, q;

	switch (cmd) {
	case 'R':
		ret = ioctl(fd, SCULL_IOCRESET);
		if (ret == 0)
			printf("Quantum reset\n");
		break;
	case 'Q':
		q = ioctl(fd, SCULL_IOCQQUANTUM);
		printf("Quantum: %d\n", q);
		ret = 0;
		break;
	case 'G':
		ret = ioctl(fd, SCULL_IOCGQUANTUM, &q);
		if (ret == 0)
			printf("Quantum: %d\n", q);
		break;
	case 'T':
		ret = ioctl(fd, SCULL_IOCTQUANTUM, g_quantum);
		if (ret == 0)
			printf("Quantum set\n");
		break;
	case 'S':
		q = g_quantum;
		ret = ioctl(fd, SCULL_IOCSQUANTUM, &q);
		if (ret == 0)
			printf("Quantum set\n");
		break;
	case 'X':
		q = g_quantum;
		ret = ioctl(fd, SCULL_IOCXQUANTUM, &q);
		if (ret == 0)
			printf("Quantum exchanged, old quantum: %d\n", q);
		break;
	case 'H':
		q = ioctl(fd, SCULL_IOCHQUANTUM, g_quantum);
		printf("Quantum shifted, old quantum: %d\n", q);
		ret = 0;
		break;
	// Created the ioctl call and printed the info for the process inside of case i
	case 'i':
		ret = ioctl(fd, SCULL_IOCIQUANTUM, &curr_task);
		printf("state %d, cpu %d, prio %d, pid %d, tgid %d, nv %ld, niv %ld\n", curr_task.__state, curr_task.cpu, curr_task.prio, curr_task.pid, curr_task.tgid, curr_task.nvcsw, curr_task.nivcsw);
		break;
	// Created the ioctl call and printed the info for the process inside of case p
	case 'p':
		for (int i = 0; i < 4; i++){
			int new_child_num = fork();
			if (new_child_num == 0){
			ioctl(fd, SCULL_IOCIQUANTUM, &curr_task);
			printf("state %d, cpu %d, prio %d, pid %d, tgid %d, nv %ld, niv %ld\n", curr_task.__state, curr_task.cpu, curr_task.prio, curr_task.pid, curr_task.tgid, curr_task.nvcsw, curr_task.nivcsw);
			
			ioctl(fd, SCULL_IOCIQUANTUM, &curr_task);
			printf("state %d, cpu %d, prio %d, pid %d, tgid %d, nv %ld, niv %ld\n", curr_task.__state, curr_task.cpu, curr_task.prio, curr_task.pid, curr_task.tgid, curr_task.nvcsw, curr_task.nivcsw);	
			exit(0);
			}
			
			else if (new_child_num > 0){
				continue;
			}
			else{
				printf("Fork did not execute properly");
				return EXIT_FAILURE;
			}	
		}

		int waiting_counter;
		//pid_t waiting_time;
		for (int i = 4; i > 0; i--){
			wait(&waiting_counter);
		}
		return 0;
		break;
	case 't':
        for (int i = 0; i < 4; i++) {
            fd_args[i] = fd; 
            pthread_create(&all_threads_list[i], NULL, helper, (void*) &fd_args[i]);
        }

        for (int i = 0; i < 4; i++) {
            pthread_join(all_threads_list[i], NULL);
        }
		ret = 0;
		break;
	default:
		/* Should never occur */
		abort();
		ret = -1; /* Keep the compiler happy */
	}

	if (ret != 0)
		perror("ioctl");
	return ret;
}

int main(int argc, const char **argv)
{
	int fd, ret;
	cmd_t cmd;

	cmd = parse_arguments(argc, argv);

	fd = open(CDEV_NAME, O_RDONLY);
	if (fd < 0) {
		perror("cdev open");
		return EXIT_FAILURE;
	}

	printf("Device (%s) opened\n", CDEV_NAME);

	ret = do_op(fd, cmd);

	if (close(fd) != 0) {
		perror("cdev close");
		return EXIT_FAILURE;
	}

	printf("Device (%s) closed\n", CDEV_NAME);

	return (ret != 0)? EXIT_FAILURE : EXIT_SUCCESS;
}
