/**
 * Converter: convert tab indentation to 8 spaces.
 * Created by STARRY-S - hxstarrys@gmail.com
 * Lisense: Apache-2.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#ifndef MAXLINE
#define MAXLINE 512
#endif

#define TEMP_NAME "_convert.tmp"

int handleChar(char c, int wrfd)
{
        static char buff[MAXLINE] = { 0 };
        static int pos = 0;

        switch (c) {
        case '\t':
        {
                /* replace tab to space */
                if (pos + 8 >= MAXLINE) {
                        if (write(wrfd, buff, pos) < 0) {
                                perror("write");
                        }
                        pos = 0;
                }

                int i;
                for (i = pos; i < pos + 8; ++i) {
                        buff[i] = ' ';
                }
                pos = i;
                break;
        }
        case EOF:
        {
                if (write(wrfd, buff, pos) < 0) {
                        perror("write");
                }
                break;
        }
        case '\n':
        {
                /* end of line */
                buff[pos] = c;
                if (write(wrfd, buff, pos + 1) < 0) {
                        perror("write");
                }
                pos = 0;
                break;
        }
        default:
        {
                buff[pos++] = c;
                break;
        }
        }

        return 0;
}

int main(int argc, char **argv)
{
        if (argc < 2) {
                fprintf(stderr, "Usage: %s <file name>\n", argv[0]);
                exit(EXIT_FAILURE);
        }

        if (strcmp(argv[1], "-h") == 0) {
                fprintf(stdout, "Contert tab to 8 spaces.\n");
                fprintf(stdout, "Usage: %s <file name>\n", argv[0]);
        }

        int opfd = 0;
        if ((opfd = open(argv[1], O_RDONLY)) < 0) {
                perror("open");
                exit(EXIT_FAILURE);
        }

        int wrfd = 0;
        /* rw-r--r-- */
        mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
        if ((wrfd = open(TEMP_NAME, O_RDWR | O_CREAT | O_TRUNC, mode)) < 0) {
                perror("open");
                exit(EXIT_FAILURE);
        }

        char c;
        int result;
        while ((result = read(opfd, &c, 1)) > 0) {
                handleChar(c, wrfd);
        }

        if (result == 0) {
                handleChar(EOF, wrfd);
        } else if (result < 0) {
                perror("read");
                exit(EXIT_FAILURE);
        }

        char backupName[128];
        snprintf(backupName, 128, "%s.bak", argv[1]);
        rename(argv[1], backupName);
        rename(TEMP_NAME, argv[1]);

        return EXIT_SUCCESS;
}
