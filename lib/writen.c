/*
 * 图3-16 writen函数: 往一个描述符写n字节
 * */
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>

/* write "n" bytes to a descriptor */
ssize_t                  
writen(int fd,const void *vptr, size_t n)
{
    size_t nleft;
    ssize_t nwritten;
    const char *ptr;

    ptr = vptr;
    nleft = n;
    while(nleft > 0)
    {
        if( (nwritten = write(fd, ptr, nleft)) <= 0)
        {
            if(nwritten < 0 && errno == EINTR)
                nwritten = 0; /* and call write() again */
            else
                return -1;    /* error */
        }
        nleft -= nwritten;
        ptr += nwritten;
    }
    return n;
}
