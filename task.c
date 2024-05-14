#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <sys/types.h>


bool iszeroed(char buf[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (buf[i] != '\0')
        {
            return false;
        }
    }
    return true;
}

int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        printf("Missing path to target file\n");
        return -1;
    }

    // вычленияем размер буфера
    char *bufsize = NULL;
    int res = 0;
    while ((res = getopt(argc, argv, "b:")) != -1)
    {

        switch (res)
        {
        case 'b':
            bufsize = optarg;

            break;
        default:
            break;
        }
    }

    if (!bufsize)
    {
        char defbuf[] = "4096";
        bufsize = defbuf;
    }

    // читаем с stdin, если первый позиционный - последний
    int sourcefd;
    int targetfd;
    //int targetmetafd;
    if (optind < argc - 1)
    {
        sourcefd = open(argv[optind], O_RDONLY);
        targetfd = open(argv[optind + 1], O_CREAT | O_WRONLY | O_TRUNC, 0777);
        //targetmetafd = open(strcat(argv[optind + 1], ".meta"), O_CREAT | O_WRONLY | O_TRUNC, 0777);
    }
    else
    {
        sourcefd = STDIN_FILENO;
        targetfd = open(argv[optind], O_CREAT | O_WRONLY | O_TRUNC, 0777);
      //  targetmetafd = open(strcat(argv[optind], ".meta"), O_CREAT | O_WRONLY | O_TRUNC, 0777);
    }

    int ibufsize = atoi(bufsize);

    char buf[ibufsize];

	while (ibufsize = read(sourcefd, buf, ibufsize)) {
		if (iszeroed(buf, ibufsize)) {
			lseek(targetfd, ibufsize, SEEK_CUR);
		}
		else {
			write(targetfd, buf, ibufsize);
		}
	}
    close(sourcefd);
    close(targetfd);
    //close(targetmetafd);

    return 0;
}
