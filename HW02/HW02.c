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

void displayForsFlag(struct dirent *dirent, char *target, int tabSpaces, int count, struct stat *buf, ssize_t b,
                     int SFlag, char *subStr, int fileSize, int depth, int argsFlag, char *fileType);

void displayForFFlag(struct dirent *dirent, char *target, int tabSpaces, int count, struct stat *buf, ssize_t b,
                     int SFlag, char *subStr, int fileSize, int depth, int argsFlag, char *fileType);

void displayForSFlag(struct dirent *dirent, char *target, int tabSpaces, int count, struct stat *buf, ssize_t b,
                     int SFlag, char *subStr, int fileSize, int depth, int argsFlag, char *fileType);
void displayFortFlag(struct dirent *dirent, char *target, int tabSpaces, int count, struct stat *buf, ssize_t b,
                     int SFlag, char *subStr, int fileSize, int depth, int argsFlag, char *fileType);

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

void splitStringOnSpace(const char *str, char **str1, char **str2) {
    char *space_pos = strchr(str, ' ');
    if (space_pos == NULL) {
        *str1 = NULL;
        *str2 = NULL;
        return;
    }
    size_t len1 = space_pos - str;
    size_t len2 = strlen(space_pos + 1);
    *str1 = (char *) malloc(len1 + 1);
    *str2 = (char *) malloc(len2 + 1);
    strncpy(*str1, str, len1);
    strncpy(*str2, space_pos + 1, len2);
    (*str1)[len1] = '\0';
    (*str2)[len2] = '\0';
}

void displayForNoFlag(struct dirent *dirent, char *target, int tabSpaces, int count, struct stat *buf, ssize_t b,
                     int SFlag, char *subStr, int fileSize, int depth, int argsFlag, char *fileType) {

    argsFlag--;
    if (argsFlag <= 0) {
        if (dirent->d_type == DT_LNK) {
            b = readlink(dirent->d_name, target, PATH_MAX - 1);
            printf("%*s[%d] %s (symbolic link to %s)\n", 4 * tabSpaces, " ", count, dirent->d_name, target);
        } else {
            printf("%*s[%d] %s (%s)\n", 4 * tabSpaces, " ", count, dirent->d_name, filetype(dirent->d_type));

        }
//        printStat(*buf, 4 * tabSpaces);
    }
    if (subStr != NULL) {
        displayForsFlag(dirent, target, tabSpaces, count, buf, b, SFlag, subStr, fileSize, depth, argsFlag, fileType);
    }else if (fileType != NULL) {
        displayFortFlag(dirent, target, tabSpaces, count, buf, b, SFlag, subStr, fileSize, depth, argsFlag, fileType);
    } else if (fileSize != 0) {
        displayForFFlag(dirent, target, tabSpaces, count, buf, b, SFlag, subStr, fileSize, depth, argsFlag, fileType);
    } else if (SFlag == 1) {
        displayForSFlag(dirent, target, tabSpaces, count, buf, b, SFlag, subStr, fileSize, depth, argsFlag, fileType);
    }


}
void displayForSFlag(struct dirent *dirent, char *target, int tabSpaces, int count, struct stat *buf, ssize_t b,
                     int SFlag, char *subStr, int fileSize, int depth, int argsFlag, char *fileType) {

    argsFlag--;
    SFlag = 0;
    if (argsFlag <= 0) {
        if (dirent->d_type == DT_LNK) {
            b = readlink(dirent->d_name, target, PATH_MAX - 1);
            printf("%*s[%d] %s (symbolic link to %s)\n", 4 * tabSpaces, " ", count, dirent->d_name, target);
        } else {
            printf("%*s[%d] %s (%s)\n", 4 * tabSpaces, " ", count, dirent->d_name, filetype(dirent->d_type));

        }
        printStat(*buf, 4 * tabSpaces);
    }
    if (subStr != NULL) {
        displayForsFlag(dirent, target, tabSpaces, count, buf, b, SFlag, subStr, fileSize, depth, argsFlag, fileType);
    }else if (fileType != NULL) {
        displayFortFlag(dirent, target, tabSpaces, count, buf, b, SFlag, subStr, fileSize, depth, argsFlag, fileType);
    } else if (fileSize != 0) {
        displayForFFlag(dirent, target, tabSpaces, count, buf, b, SFlag, subStr, fileSize, depth, argsFlag, fileType);
    } else if (SFlag == 1) {
        displayForSFlag(dirent, target, tabSpaces, count, buf, b, SFlag, subStr, fileSize, depth, argsFlag, fileType);
    }


}

void displayFortFlag(struct dirent *dirent, char *target, int tabSpaces, int count, struct stat *buf, ssize_t b,
                     int SFlag, char *subStr, int fileSize, int depth, int argsFlag, char *fileType) {
    argsFlag--;
    int x;
    if (strcmp(fileType, "d") == 0){

        x = DT_DIR;
    }
    if (strcmp(fileType, "f") == 0){

        x = DT_REG;
    }
    if (dirent->d_type == x) {
        // Changes for symbolic link
        if (argsFlag <= 0) {
            if (dirent->d_type == DT_LNK) {
                b = readlink(dirent->d_name, target, PATH_MAX - 1);
                printf("%*s[%d] %s (symbolic link to %s)\n", 4 * tabSpaces, " ", count, dirent->d_name, target);
            } else {
                printf("%*s[%d] %s (%s)\n", 4 * tabSpaces, " ", count, dirent->d_name,
                       filetype(dirent->d_type));

            }
        }
        fileType = NULL;
        if (subStr != NULL) {
            displayForsFlag(dirent, target, tabSpaces, count, buf, b, SFlag, subStr, fileSize, depth, argsFlag, fileType);
        }else if (fileType != NULL) {
            displayFortFlag(dirent, target, tabSpaces, count, buf, b, SFlag, subStr, fileSize, depth, argsFlag, fileType);
        } else if (fileSize != 0) {
            displayForFFlag(dirent, target, tabSpaces, count, buf, b, SFlag, subStr, fileSize, depth, argsFlag, fileType);
        } else if (SFlag == 1) {
            displayForSFlag(dirent, target, tabSpaces, count, buf, b, SFlag, subStr, fileSize, depth, argsFlag, fileType);
        }
    }
}
void displayForFFlag(struct dirent *dirent, char *target, int tabSpaces, int count, struct stat *buf, ssize_t b,
                     int SFlag, char *subStr, int fileSize, int depth, int argsFlag, char *fileType) {
    argsFlag--;
    if (checkSize(*buf, fileSize) == 1) {
        // Changes for symbolic link
        if (argsFlag <= 0) {
            if (dirent->d_type == DT_LNK) {
                b = readlink(dirent->d_name, target, PATH_MAX - 1);
                printf("%*s[%d] %s (symbolic link to %s)\n", 4 * tabSpaces, " ", count, dirent->d_name, target);
            } else {
                printf("%*s[%d] %s (%s)\n", 4 * tabSpaces, " ", count, dirent->d_name,
                       filetype(dirent->d_type));

            }
        }
        fileSize = 0;
        if (subStr != NULL) {
            displayForsFlag(dirent, target, tabSpaces, count, buf, b, SFlag, subStr, fileSize, depth, argsFlag, fileType);
        }else if (fileType != NULL) {
            displayFortFlag(dirent, target, tabSpaces, count, buf, b, SFlag, subStr, fileSize, depth, argsFlag, fileType);
        } else if (fileSize != 0) {
            displayForFFlag(dirent, target, tabSpaces, count, buf, b, SFlag, subStr, fileSize, depth, argsFlag, fileType);
        } else if (SFlag == 1) {
            displayForSFlag(dirent, target, tabSpaces, count, buf, b, SFlag, subStr, fileSize, depth, argsFlag, fileType);
        }
    }
}

void displayForsFlag(struct dirent *dirent, char *target, int tabSpaces, int count, struct stat *buf, ssize_t b,
                     int SFlag, char *subStr, int fileSize, int depth, int argsFlag, char *fileType) {
    argsFlag--;
    if (dirent->d_type == DT_DIR) {
        return;

    } else {

        char *str1;
        char *str2;
        splitStringOnSpace(subStr, &str1, &str2);
        if (DT_DIR && checkSubstr(dirent->d_name, str1, depth, atoi(str2)) == 1) {
//                         Changes for symbolic link
            if (argsFlag <= 0) {
                if (dirent->d_type == DT_LNK) {
                    b = readlink(dirent->d_name, target, PATH_MAX - 1);
                    printf("%*s[%d] %s (symbolic link to %s)\n", 4 * tabSpaces, " ", count, dirent->d_name,
                           target);
                } else {
                    printf("%*s[%d] %s (%s)\n", 4 * tabSpaces, " ", count, dirent->d_name,
                           filetype(dirent->d_type));

                }
            }
            subStr = NULL;
            if (subStr != NULL) {
                displayForsFlag(dirent, target, tabSpaces, count, buf, b, SFlag, subStr, fileSize, depth, argsFlag, fileType);
            }else if (fileType != NULL) {
                displayFortFlag(dirent, target, tabSpaces, count, buf, b, SFlag, subStr, fileSize, depth, argsFlag, fileType);
            } else if (fileSize != 0) {
                displayForFFlag(dirent, target, tabSpaces, count, buf, b, SFlag, subStr, fileSize, depth, argsFlag, fileType);
            } else if (SFlag == 1) {
                displayForSFlag(dirent, target, tabSpaces, count, buf, b, SFlag, subStr, fileSize, depth, argsFlag, fileType);
            }
        }
        free(str1);
        free(str2);
    }
}

void traverseDirectory(char *path, int tabSpaces, int depth, int argsFlag, char *subStr, int fileSize, int SFlag,
                       char *fileType) {

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
    char *cwd = (char *) malloc(MAX_PATH_SIZE);
    while ((dirent = readdir(parentDir)) != NULL) {

        // If the file's name is "." or "..", ignore them. We do not want to infinitely recurse.
        if (strcmp(dirent->d_name, ".") == 0 || strcmp(dirent->d_name, "..") == 0) {
            continue;
        }

        char target[PATH_MAX];
        ssize_t b;
        memset(cwd, 0, MAX_PATH_SIZE);
        strcat(cwd, path);
        strcat(cwd, "/");
        strcat(cwd, dirent->d_name);
        struct stat buf;
        int firstOrNotFlag = 0;
        int paramsPassedFlag = 0;
        if (lstat(cwd, &buf) < 0) {
            printf("lstat error for: %s\n", dirent->d_name);
        }

        if (subStr != NULL) {
            displayForsFlag(dirent, target, tabSpaces, count, &buf, b, SFlag, subStr, fileSize, depth, argsFlag, fileType);
        }else if (fileType != NULL) {
            displayFortFlag(dirent, target, tabSpaces, count, &buf, b, SFlag, subStr, fileSize, depth, argsFlag, fileType);
        } else if (fileSize != 0) {
            displayForFFlag(dirent, target, tabSpaces, count, &buf, b, SFlag, subStr, fileSize, depth, argsFlag, fileType);
        } else if (SFlag == 1) {
            displayForSFlag(dirent, target, tabSpaces, count, &buf, b, SFlag, subStr, fileSize, depth, argsFlag, fileType);
        }
        else {
            displayForNoFlag(dirent, target, tabSpaces, count, &buf, b, SFlag, subStr, fileSize, depth, argsFlag, fileType);
        }

        count++;
        // Check to see if the file type is a directory. If it is, recursively call traverseDirectory on it.
        if (dirent->d_type == DT_DIR) {
            // Build the new file path.
            char *subDirPath = (char *) malloc(MAX_PATH_SIZE);
            strcpy(subDirPath, path);
            strcat(subDirPath, "/");
            strcat(subDirPath, dirent->d_name);
            traverseDirectory(subDirPath, tabSpaces + 1, depth + 1, argsFlag, subStr, fileSize, SFlag, fileType);
        }
    }
}

int main(int argc, char **argv) {

    int tabSpaces = 0;
    int depth = 0;

    int opt;
    int argFlag = 0;
    char *subStr = NULL;
    int fileSize = 0;
    char *startingFolder = NULL;
    int SFlag = 0;
    char *fileType;

    if (argv[1] == NULL || argv[1][0] == '-') {
        startingFolder = ".";
    } else {
        startingFolder = argv[1];
    }
    while ((opt = getopt(argc, argv, "Ss:f:t:")) != -1) {
        switch (opt) {
            case 'S':
                argFlag++;
                SFlag = 1;
                break;
            case 's':
                subStr = optarg;
                argFlag++;
                break;
            case 'f':
                argFlag++;
                fileSize += atoi(optarg);
//                    fFlag = 1;
                break;
            case 't':
                argFlag++;
                fileType = optarg;
                break;
            default:
                printf("Invalid args");
        }

    }
    traverseDirectory(startingFolder, tabSpaces, depth, argFlag, subStr, fileSize, SFlag, fileType);


    return 0;
}