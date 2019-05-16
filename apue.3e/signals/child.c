/*
一般的,父进程在生成子进程之后会有两种情况,一种是父进程继续去做别的事情,另一种是父进程啥都不做,
 一直在wait子进程退出.SIGCHLD信号就是为这第一种情况准备的,它让父进程去做别的事情,而只要父进
 程注册了处理该信号的函数,在子进程退出时就会调用该函数,在该函数中又可以调用wait得到终止的子进
 程的状态。处理信号的函数执行完后，再继续做父进程的事情.

也就是说，如果父进程在fork之后调用wait，就会阻塞，直到有一个子进程退出。

如果父进程在fork之前先signal(SIGCLD, sig_cld)，即注册了SIGCLD的信号处理函数。然后做自己
 的事情。当子进程退出时，会给父进程发送一个SIGCLD信号。然后sig_cld函数就会执行。可以在
 sig_cld函数中调用wait获得子进程退出时的状态，并且此时wait不会阻塞。 当sig_cld函数执行完后
 ，父进程又继续做自己的事情。
 */

#include	"apue.h"
#include	<sys/wait.h>

static void	sig_cld(int);

int
main()
{
	pid_t	pid;

//	if (signal(SIGCLD, sig_cld) == SIG_ERR)
	if (signal(SIGCHLD, sig_cld) == SIG_ERR)
		perror("signal error");
	if ((pid = fork()) < 0) {
		perror("fork error");
	} else if (pid == 0) {		/* child */
		sleep(2);
		_exit(0);
	}

	pause();	/* parent */
	exit(0);
}

static void
sig_cld(int signo)	/* interrupts pause() */
{
	pid_t	pid;
	int		status;

	printf("SIGCLD received\n");

//	if (signal(SIGCLD, sig_cld) == SIG_ERR)	/* reestablish handler */
	if (signal(SIGCHLD, sig_cld) == SIG_ERR)	/* reestablish handler */
		perror("signal error");

	if ((pid = wait(&status)) < 0)		/* fetch child status */
		perror("wait error");

	printf("pid = %d\n", pid);
}
