/* this is logread from Busybox 1.2.1, with a couple minor mods to be called as a function */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <signal.h>
#include <setjmp.h>
#include <unistd.h>

static const long KEY_ID = 0x414e4547; /*"GENA"*/

static struct shbuf_ds {
	int size;		// size of data written
	int head;		// start of message list
	int tail;		// end of message list
	char data[1];		// data/messages
} *buf = NULL;			// shared memory pointer


// Semaphore operation structures
static struct sembuf SMrup[1] = {{0, -1, IPC_NOWAIT | SEM_UNDO}}; // set SMrup
static struct sembuf SMrdn[2] = {{1, 0}, {0, +1, SEM_UNDO}}; // set SMrdn

static int	log_shmid = -1;	// ipc shared memory id
static int	log_semid = -1;	// ipc semaphore id

/*
 * cleanup_sema - release semaphore if acquired
 */
static void cleanup_sema() 
{
	//release all acquired resources
	if (log_shmid != -1)
		shmdt(buf);	
}
/*
 * sem_up - up()'s a semaphore.
 */
static inline void sem_up(int semid)
{
	semop(semid, SMrup, 1);		
}

/*
 * sem_down - down()'s a semaphore
 */
static inline void sem_down(int semid)
{
	semop(semid, SMrdn, 2);
}

int busybox_logread(char *pszOutputFile)
{
	int i;
	FILE *fOut=fopen(pszOutputFile,"w");	
	if(!fOut)
	{
		return 1;
	}

	if ( (log_shmid = shmget(KEY_ID, 0, 0)) == -1)
	{
		fclose(fOut);
		return 1;
	}

	// Attach shared memory to our char*
	if ( (buf = shmat(log_shmid, NULL, SHM_RDONLY)) == NULL)
	{
		cleanup_sema();		
		fClose(fOUt);
		return 1;
	}

	if ( (log_semid = semget(KEY_ID, 0, 0)) == -1)
	{
		cleanup_sema();		
		fClose(fOut);
		return 1;
	}

	// Suppose atomic memory move
	i = buf->head;

#ifdef CONFIG_FEATURE_LOGREAD_REDUCED_LOCKING
		char *buf_data;
		int log_len,j;
#endif

		sem_down(log_semid);

		//printf("head: %i tail: %i size: %i\n",buf->head,buf->tail,buf->size);
		if (buf->head == buf->tail || i==buf->tail) {
			fprintf(fOut,"<empty syslog>\n");			
		}

		// Read Memory
#ifdef CONFIG_FEATURE_LOGREAD_REDUCED_LOCKING
		log_len = buf->tail - i;
		if (log_len < 0)
			log_len += buf->size;
		buf_data = (char *)xmalloc(log_len);

		if (buf->tail < i) {
			memcpy(buf_data, buf->data+i, buf->size-i);
			memcpy(buf_data+buf->size-i, buf->data, buf->tail);
		} else {
			memcpy(buf_data, buf->data+i, buf->tail-i);
		}
		i = buf->tail;

#else
		while ( i != buf->tail) {
			fprintf(fOut, "%s", buf->data+i);
			i+= strlen(buf->data+i) + 1;
			if (i >= buf->size )
				i=0;
		}
#endif
		// release the lock on the log chain
		sem_up(log_semid);

#ifdef CONFIG_FEATURE_LOGREAD_REDUCED_LOCKING
		for (j=0; j < log_len; j+=strlen(buf_data+j)+1) {
			fprintf(fOut, "%s", buf_data+j);
		}
		free(buf_data);
#endif
		fflush(fOut);

	if (log_shmid != -1)
		shmdt(buf);
	
	fclose(fOut);
	return 0;
}


