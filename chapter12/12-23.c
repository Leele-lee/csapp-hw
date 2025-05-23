/*
 * echoservers.c - A concurrent echo server based on select
 */
/* $begin echoserversmain */
#include "csapp.h"

#define MAXBUF_LEN MAXLINE

typedef struct
{ /* Represents a pool of connected descriptors */ // line:conc:echoservers:beginpool
	int maxfd;									   /* Largest descriptor in read_set */
	fd_set read_set;							   /* Set of all active descriptors */
	fd_set ready_set;							   /* Subset of descriptors ready for reading  */
	int nready;									   /* Number of ready descriptors from select */
	int maxi;									   /* Highwater index into client array */
	int clientfd[FD_SETSIZE];					   /* Set of active descriptors */
	rio_t clientrio[FD_SETSIZE];				   /* Set of active read buffers */
	char clientbuf[FD_SETSIZE][MAXBUF_LEN];
	int buflen[FD_SETSIZE];
} pool;											   // line:conc:echoservers:endpool
/* $end echoserversmain */
void init_pool(int listenfd, pool *p);
void add_client(int connfd, pool *p);
void check_clients(pool *p);
/* $begin echoserversmain */

int byte_cnt = 0; /* Counts total bytes received by server */

int main(int argc, char **argv)
{
	int listenfd, connfd;
	socklen_t clientlen;
	struct sockaddr_storage clientaddr;
	static pool pool;

	if (argc != 2)
	{
		fprintf(stderr, "usage: %s <port>\n", argv[0]);
		exit(0);
	}
	listenfd = Open_listenfd(argv[1]);
	init_pool(listenfd, &pool); // line:conc:echoservers:initpool

	while (1)
	{
		/* Wait for listening/connected descriptor(s) to become ready */
		pool.ready_set = pool.read_set;
		pool.nready = Select(pool.maxfd + 1, &pool.ready_set, NULL, NULL, NULL);
		printf("[DEBUG] in main loop, nready returned by select is: %d\n", pool.nready);
		/* If listening descriptor ready, add new client to pool */
		if (FD_ISSET(listenfd, &pool.ready_set))
		{ // line:conc:echoservers:listenfdready
			clientlen = sizeof(struct sockaddr_storage);
			connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen); // line:conc:echoservers:accept
			add_client(connfd, &pool);								  // line:conc:echoservers:addclient
		}

		/* Echo a text line from each ready connected descriptor */
		check_clients(&pool); // line:conc:echoservers:checkclients
	}
}
/* $end echoserversmain */

/* $begin init_pool */
void init_pool(int listenfd, pool *p)
{
	/* Initially, there are no connected descriptors */
	int i;
	p->maxi = -1; // line:conc:echoservers:beginempty
	for (i = 0; i < FD_SETSIZE; i++)
		p->clientfd[i] = -1; // line:conc:echoservers:endempty

	/* Initially, listenfd is only member of select read set */
	p->maxfd = listenfd; // line:conc:echoservers:begininit
	FD_ZERO(&p->read_set);
	FD_SET(listenfd, &p->read_set); // line:conc:echoservers:endinit
}
/* $end init_pool */

/* $begin add_client */
void add_client(int connfd, pool *p)
{
	int i;
	p->nready--;
	for (i = 0; i < FD_SETSIZE; i++) {/* Find an available slot */
		if (p->clientfd[i] < 0)
		{
			/* Add connected descriptor to the pool */
			p->clientfd[i] = connfd;				 // line:conc:echoservers:beginaddclient
			//Rio_readinitb(&p->clientrio[i], connfd); // line:conc:echoservers:endaddclient
			p->buflen[i] = 0;
			/* Add the descriptor to descriptor set */
			FD_SET(connfd, &p->read_set); // line:conc:echoservers:addconnfd
			printf("[DEBUG] Added client on FD %d at index %d\n", connfd, i);

			/* Update max descriptor and pool highwater mark */
			if (connfd > p->maxfd) // line:conc:echoservers:beginmaxfd
				p->maxfd = connfd; // line:conc:echoservers:endmaxfd
			if (i > p->maxi)	   // line:conc:echoservers:beginmaxi
				p->maxi = i;	   // line:conc:echoservers:endmaxi
			break;
		}
	    if (i == FD_SETSIZE) /* Couldn't find an empty slot */
		    app_error("add_client error: Too many clients");
	}
}
/* $end add_client */

/* $begin check_clients */
void check_clients(pool *p)
{
	int i, connfd, n;
	char buf[MAXLINE];
	//rio_t rio
	printf("[DEBUG] I am coming in check_clients and p->nready is: %d\n", p->nready);

	for (i = 0; (i <= p->maxi) && (p->nready > 0); i++)
	{
		connfd = p->clientfd[i];
		//rio = p->clientrio[i];
		printf("[DEBUG] This is %dth for loop inside check_clients, and current connfd is %d, nready is: %d\n", 
			i, connfd, p->nready);
		printf("[DEBUG] Checking FD %d: buflen=%d\n", connfd, p->buflen[i]);

		/* If the descriptor is ready, echo a text line from it */
		if ((connfd > 0) && (FD_ISSET(connfd, &p->ready_set)))
		{
			printf("[DEBUG] connfd %d is ready!\n", connfd);
			p->nready--;
			// this can not using rio_readn function bc it will block until reads MAXBUF_LEN bytes
			// instead we using read or recv fucntion
			n = read(connfd, buf, MAXBUF_LEN);
			printf("[DEBUG] read read %d bytes from connfd: %d\n", n, connfd);
			if (n > 0) {
				if (p->buflen[i] + n > MAXBUF_LEN) {
					fprintf(stderr, "Buffer overflow from client %d\n", connfd);
					Close(connfd);
					FD_CLR(connfd, &p->read_set);
					p->clientfd[i] = -1;
					p->buflen[i] = 0;
					continue;
				}
				
				printf("[DEBUG] FD %d: readn returned %d bytes\n", connfd, n);
				memcpy(p->clientbuf[i] + p->buflen[i], buf, n);
				p->buflen[i] += n;

				char *newline;
				int newlen;
				if ((newline = memchr(p->clientbuf[i], '\n', p->buflen[i])) != NULL) {
					newlen = newline - p->clientbuf[i] + 1;
					printf("[DEBUG] Server received %d (%d total) bytes on fd %d\n", n, newlen, connfd);
					Rio_writen(connfd, p->clientbuf[i], newlen);
					p->buflen[i] -= newlen;
					memmove(p->clientbuf[i], newline + 1, p->buflen[i]); 
				} else {
					printf("[DEBUG] FD %d: no full line yet, buflen=%d\n", connfd, p->buflen[i]);
				}

			} else {
				printf("[DEBUG] FD %d: client disconnected\n", connfd);
				Close(connfd);
				FD_CLR(connfd, &p->read_set);
				p->clientfd[i] = -1;
				p->buflen[i] = 0;
			}
		}
	}
}
/* $end check_clients */
