#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <limits.h>
#include <time.h>

#define MAX_PATH_SIZE 2000

char *filetype(unsigned char type) {
    char *str;
    switch (type) {
        case DT_BLK:
            str = "block device";
            break;
        case DT_CHR:
            str = "character device";
            break;
        case DT_DIR:
            str = "directory";
            break;
        case DT_FIFO:
            str = "named pipe (FIFO)";
            break;
        case DT_LNK:
            str = "symbolic link";
            break;
        case DT_REG:
            str = "regular file";
            break;
        case DT_SOCK:
            str = "UNIX domain socket";
            break;
        case DT_UNKNOWN:
            str = "unknown file type";
            break;
        default:
            str = "UNKNOWN";
    }
    return str;
}

void printStat(struct stat sb, int tab) {


    printf("%*s  File Permissions:         ", tab, " ");
    printf((S_ISDIR(sb.st_mode)) ? "d" : "-");
    printf((sb.st_mode & S_IRUSR) ? "r" : "-");
    printf((sb.st_mode & S_IWUSR) ? "w" : "-");
    printf((sb.st_mode & S_IXUSR) ? "x" : "-");
    printf((sb.st_mode & S_IRGRP) ? "r" : "-");
    printf((sb.st_mode & S_IWGRP) ? "w" : "-");
    printf((sb.st_mode & S_IXGRP) ? "x" : "-");
    printf((sb.st_mode & S_IROTH) ? "r" : "-");
    printf((sb.st_mode & S_IWOTH) ? "w" : "-");
    printf((sb.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n");
    if (S_ISDIR(sb.st_mode)) {
        printf("%*s  File size:                %lld bytes\n", tab, " ",
               (long long) 0);

    } else {
        printf("%*s  File size:                %lld bytes\n", tab, " ",
               (long long) sb.st_size);

    }
    printf("%*s  Last file access:         %s\n", tab, " ", ctime(&sb.st_atime));
}

int checkSize(struct stat sb, int size) {
    int flag = 0;
    if (sb.st_size <= size) {
        flag = 1;
    }
    return flag;

}

int checkSubstr(char *fileName, char *substr, int depth, int depthLimit) {
    int flag = 0;
    if (strstr(fileName, substr) != NULL && depth <= depthLimit) {
        flag = 1;
    }
    return flag;

}

void traverseDirectory(char *path, int tabSpaces, int depth, int argsFlag) {

    struct dirent *dirent;
    DIR *parentDir;

    // First, we need to open the directory.
    parentDir = opendir(path);
    if (parentDir == NULL) {
        printf("Error opening directory '%s'\n", path);
        exit(-1);
    }
    int count = 1;
    // After we open the directory, we can read the contents of the directory, file by file.
    char pathString[MAX_PATH_SIZE + 1];
    while ((dirent = readdir(parentDir)) != NULL) {

        // If the file's name is "." or "..", ignore them. We do not want to infinitely recurse.
        if (strcmp(dirent->d_name, ".") == 0 || strcmp(dirent->d_name, "..") == 0) {
            continue;
        }





//        printf("name: %s\n", dirent->d_name);
//        printf("cwd: %s\n", cwd);
//        if (strcmp(dirent->d_name,"file2.txt")) {
//            printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
//        }
//        int bool = 0;

        char target[PATH_MAX];
        ssize_t b;
        char *cwd = (char *) malloc(MAX_PATH_SIZE);
        strcat(cwd, path);
        strcat(cwd, "/");
        strcat(cwd, dirent->d_name);
        struct stat buf;
        if (lstat(cwd, &buf) < 0) {
            printf("lstat error for: %s\n", dirent->d_name);
        }
        switch (argsFlag) {
            case 1:

                if (dirent->d_type == DT_LNK) {
                    b = readlink(dirent->d_name, target, PATH_MAX - 1);
                    printf("%*s[%d] %s (symbolic link to %s)\n", 4 * tabSpaces, " ", count, dirent->d_name, target);
                } else {
                    printf("%*s[%d] %s (%s)\n", 4 * tabSpaces, " ", count, dirent->d_name, filetype(dirent->d_type));
                    printf("%d", depth);

                }
                printStat(buf, 4 * tabSpaces);
                break;
            case 2:
                if (dirent->d_type == DT_DIR) {
                    break;

                } else {
                    if (DT_DIR && checkSubstr(dirent->d_name, "file2", depth, 2) == 1) {
//                         Changes for symbolic link
                        if (dirent->d_type == DT_LNK) {
                            b = readlink(dirent->d_name, target, PATH_MAX - 1);
                            printf("%*s[%d] %s (symbolic link to %s)\n", 4 * tabSpaces, " ", count, dirent->d_name,
                                   target);
                        } else {
                            printf("%*s[%d] %s (%s)\n", 4 * tabSpaces, " ", count, dirent->d_name,
                                   filetype(dirent->d_type));

                        }
                    }
                }

                break;
            case 3:
                if (checkSize(buf, 600) == 1) {
                    // Changes for symbolic link
                    if (dirent->d_type == DT_LNK) {
                        b = readlink(dirent->d_name, target, PATH_MAX - 1);
                        printf("%*s[%d] %s (symbolic link to %s)\n", 4 * tabSpaces, " ", count, dirent->d_name, target);
                    } else {
                        printf("%*s[%d] %s (%s)\n", 4 * tabSpaces, " ", count, dirent->d_name, filetype(dirent->d_type));
//                    printf("%d", depth);

                    }
                    printStat(buf, 4 * tabSpaces);
                }

                break;
            default:
                // Changes for symbolic link
                if (dirent->d_type == DT_LNK) {
                    b = readlink(dirent->d_name, target, PATH_MAX - 1);
                    printf("%*s[%d] %s (symbolic link to %s)\n", 4 * tabSpaces, " ", count, dirent->d_name, target);
                } else {
                    printf("%*s[%d] %s (%s)\n", 4 * tabSpaces, " ", count, dirent->d_name, filetype(dirent->d_type));
//                    printf("%d", depth);

                }
//                printStat(buf, 4 * tabSpaces);
                break;

        }


        count++;
        // Check to see if the file type is a directory. If it is, recursively call traverseDirectory on it.
        if (dirent->d_type == DT_DIR) {
            // Build the new file path.
            char *subDirPath = (char *) malloc(MAX_PATH_SIZE);
            strcpy(subDirPath, path);
            strcat(subDirPath, "/");
            strcat(subDirPath, dirent->d_name);
            traverseDirectory(subDirPath, tabSpaces + 1, depth + 1, argsFlag);
        }
    }
}

int main(int argc, char **argv) {

    int tabSpaces = 0;
    int depth = 0;
    char relativePath[MAX_PATH_SIZE];

    // Check to see if the user provides at least 2 command-line-arguments.
    if (argc < 2) {
        traverseDirectory(".", tabSpaces, depth, 3);
//        printf ("Usage: %s <dirname>\n", argv[0]);
//        exit(-1);
    } else {
        traverseDirectory(argv[1], tabSpaces, depth, 3);
    }


    return 0;
}