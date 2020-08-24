#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFSIZE 4096
#define COPYMORE 0644
void oops(char * ,char *);

void main(int argc, char* argv[])
{
    int in_fd; int out_fd; int n_chars;
    char buf[BUFSIZ];
    if(argc != 3)
    {
        fprintf(stderr,"usage : %s ============= \n",*argv);
        exit(1);
    }
    printf("open fd %s :: %d ..\n",argv[1],open(argv[1],O_RDONLY) );
    printf("open fd %s :: %d ..\n",argv[2],open(argv[2],O_RDONLY) );

    printf("cp %s to %s \n",argv[1],argv[2]) ;
    if((in_fd = open(argv[1],O_RDONLY)) == -1)
        oops("can not open file ", argv[1]);
    printf("in file %d  \n",in_fd);
    if((out_fd = open(argv[2],O_RDWR | O_CREAT)) == -1)
        oops("can not open file ", argv[2]);
    printf("out file %d  \n",out_fd);
    while((n_chars = read(in_fd,buf,BUFSIZ)) > 0)
    {
        printf("#%d \n",n_chars);
        if(write(out_fd,buf,n_chars) != n_chars)
            oops("write error to ",argv[2]);
    }
    printf("close file begin >> \n");
    if(close(in_fd) == -1 || close(out_fd) == -1)
    {
        oops("Error closing files >> \n\n","");
    }
}
void oops(char * s1,char * s2)
{
    fprintf(stderr,"Error : %s \n",s1);
    perror(s2);
    exit(1);
}