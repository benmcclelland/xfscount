#include <xfs/xfs.h>

void fscounts(char *fname, int fsfd)
{
    xfs_fsop_counts_t   counts;
    int                 ret;
    
    ret=xfsctl(fname, fsfd, XFS_IOC_FSCOUNTS, &counts);
    if (ret) {
        perror("xfsctl(XFS_IOC_FSCOUNTS)");
        exit(1);
    }

    printf("XFS_IOC_FSCOUNTS-\n    freedata: %lld freertx: %lld freeino: %lld allocino: %lld\n",
            (long long)counts.freedata, (long long)counts.freertx,
           (long long)counts.freeino, (long long)counts.allocino);
}

int
main(int argc, char **argv)
{
    int                 fsfd;
    
    if (argc != 2) {
        fprintf(stderr,"usage: %s <filesystem>\n",
                argv[0]);
        exit(0);
    }

    fsfd = open(argv[1], O_RDONLY);
    if (fsfd < 0) {
        perror("open");
        exit(1);
    }
    
    /* XFS_IOC_FSCOUNTS */
    fscounts(argv[0], fsfd);

    return 0;
}

