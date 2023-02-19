#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <limits.h>
#include <time.h>
#include <libgen.h>

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

void displayForStringFlag(struct dirent *dirent, char *target, int tabSpaces, int count, struct stat *buf, ssize_t b,
                          int SFlag, char *subStr, int fileSize, int depth, int argsFlag, char *fileType);

void displayForSizeFlag(struct dirent *dirent, char *target, int tabSpaces, int count, struct stat *buf, ssize_t b,
                        int SFlag, char *subStr, int fileSize, int depth, int argsFlag, char *fileType);

void displayStatFlag(struct dirent *dirent, char *target, int tabSpaces, int count, struct stat *buf, ssize_t b,
                     int SFlag, char *subStr, int fileSize, int depth, int argsFlag, char *fileType);

void displayFileTypeFlag(struct dirent *dirent, char *target, int tabSpaces, int count, struct stat *buf, ssize_t b,
                         int SFlag, char *subStr, int fileSize, int depth, int argsFlag, char *fileType);

void printFile(struct dirent *dirent, char *target, int tabSpaces, int count, struct stat *buf, int SFlag,
          int argsFlag);


typedef void (*funcTarget)(struct dirent *, char *, int, int, struct stat *, ssize_t,
                           int, char *, int, int, int, char *);

void chooseNextFunc(struct dirent *dirent, char *target, int tabSpaces, int count, struct stat *buf, ssize_t b, int SFlag,
               char *subStr, int fileSize, int depth, int argsFlag, char *fileType, funcTarget funcTargCall);

/**
 * Returns cwd but just the current folder
 * @return current folder
 */
char* get_current_directory_name() {
    char* cwd;

    size_t size = MAX_PATH_SIZE;
    cwd = malloc(sizeof(char) * size);

    if (getcwd(cwd, size) != NULL) {
        const char* directory_name = basename(cwd);

        char* result = malloc(sizeof(char) * (strlen(directory_name) + 1));
        strcpy(result, directory_name);

        free(cwd);

        return result;
    } else {
        free(cwd);
        return NULL;
    }
}
/**
 * Takes in stat for a file and a tab indentation for formatting and prints out
 * the file size, permissions, and last access time.
 * @param sb
 * @param tab
 */
void printStat(struct stat sb, int tab) {
    // The conversion formatting for the permissions was borrowed from a stack overflow thread: https://stackoverflow.com/questions/10323060/printing-file-permissions-like-ls-l-using-stat2-in-c
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
    // This formatting was taken from the man page
    if (S_ISDIR(sb.st_mode)) {
        printf("%*s  File size:                %lld bytes\n", tab, " ",
               (long long) 0);

    } else {
        printf("%*s  File size:                %lld bytes\n", tab, " ",
               (long long) sb.st_size);

    }
    printf("%*s  Last file access:         %s\n", tab, " ", ctime(&sb.st_atime));
}

/**
 * Method that takes in stat for a file and a size parameter and returns 1 if the file size is less or equal
 * to the parameter and 0 if it is not.
 * and 0 if it
 * @param sb
 * @param size
 * @return 0 or 1
 */
int checkSize(struct stat sb, int size) {
    int flag = 0;
    if (sb.st_size <= size) {
        flag = 1;
    }
    return flag;

}

/**
 * Takes in the fileName of the current file and its' depth and also the substring and depth from the cmd args.
 * Then compares them and returns 1 if the substring is in the filename and the depth is less than the depth limit.
 * @param fileName
 * @param substr
 * @param depth
 * @param depthLimit
 * @return 0 or 1
 */
int checkSubstr(char *fileName, char *substr, int depth, int depthLimit) {
    int flag = 0;
    if (strstr(fileName, substr) != NULL && depth <= depthLimit) {
        flag = 1;
    }
    return flag;

}

/**
 * Method to take in three strings and split the first one into two parts at the space character.
 * It then assigns the seperated strings to the two other string params.
 * @param str
 * @param str1
 * @param str2
 */
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

/**
 * Takes in information for a file and the flags from the cmd args.
 * it then call the printFile function to print the file
 * @param dirent
 * @param target
 * @param tabSpaces
 * @param count
 * @param buf
 * @param b
 * @param SFlag
 * @param subStr
 * @param fileSize
 * @param depth
 * @param argsFlag
 * @param fileType
 */
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
    }

}
/**
 * Takes in information for a file and the flags from the cmd args.
 * it then call the printFile function to print the file if requirements are met.
 * It then sets the SFlag to zero marking that the -S flag has been handled and
 * then calls the chooseNextFunc function to determine which function the file should be
 * sent to next depending on what flags are left to handle.
 * @param dirent
 * @param target
 * @param tabSpaces
 * @param count
 * @param buf
 * @param b
 * @param SFlag
 * @param subStr
 * @param fileSize
 * @param depth
 * @param argsFlag
 * @param fileType
 */
void displayStatFlag(struct dirent *dirent, char *target, int tabSpaces, int count, struct stat *buf, ssize_t b,
                     int SFlag, char *subStr, int fileSize, int depth, int argsFlag, char *fileType) {
    argsFlag--;
    funcTarget funcTargCall = NULL;
    printFile(dirent, target, tabSpaces, count, buf, SFlag, argsFlag);
    SFlag = 0;
    chooseNextFunc(dirent, target, tabSpaces, count, buf, b, SFlag, subStr, fileSize, depth, argsFlag, fileType,
                   funcTargCall);


}

/**
 * This method takes in information for a file and the flags from the cmd args.
 * It then checks whether all flags have been handled and if they have it prints the files
 * that met the criteria for all flags
 * @param dirent
 * @param target
 * @param tabSpaces
 * @param count
 * @param buf
 * @param b
 * @param SFlag
 * @param subStr
 * @param fileSize
 * @param depth
 * @param argsFlag
 * @param fileType
 */
void printFile(struct dirent *dirent, char *target, int tabSpaces, int count, struct stat *buf, int SFlag,
          int argsFlag) {
    ssize_t b;
    if (argsFlag <= 0) {
        if (dirent->d_type == DT_LNK) {
            b = readlink(dirent->d_name, target, PATH_MAX - 1);
            printf("%*s[%d] %s (symbolic link to %s)\n", 4 * tabSpaces, " ", count, dirent->d_name, target);
        } else {
            printf("%*s[%d] %s (%s)\n", 4 * tabSpaces, " ", count, dirent->d_name, filetype(dirent->d_type));

        }
        if (SFlag != 0) {
            printStat(*buf, 4 * tabSpaces);
        }
    }
}

/**
 * Takes in information for a file and the flags from the cmd args.
 * It then decides which flags have not been handled and calls the appropriate function.
 * @param dirent
 * @param target
 * @param tabSpaces
 * @param count
 * @param buf
 * @param b
 * @param SFlag
 * @param subStr
 * @param fileSize
 * @param depth
 * @param argsFlag
 * @param fileType
 * @param funcTargCall
 */
void chooseNextFunc(struct dirent *dirent, char *target, int tabSpaces, int count, struct stat *buf, ssize_t b, int SFlag,
                    char *subStr, int fileSize, int depth, int argsFlag, char *fileType, funcTarget funcTargCall) {
    if (subStr != NULL) {
        funcTargCall = &displayForStringFlag;
    } else if (fileType != NULL) {
        funcTargCall = &displayFileTypeFlag;
    } else if (fileSize != 0) {
        funcTargCall = &displayForSizeFlag;
    } else if (SFlag == 1) {
        funcTargCall = &displayStatFlag;
    }
    if (funcTargCall != NULL) {
        (*funcTargCall)(dirent, target, tabSpaces, count, buf, b, SFlag, subStr, fileSize, depth, argsFlag,
                        fileType);
    }
}
/**
 * Takes in information for a file and the flags from the cmd args.
 * It then checks to see if the current file is a folder or a regular file and only
 * executes the rest of the function on the files that type matches the fileType arg.
 * it then call the printFile function to print the file if all requirements are met.
 * It then sets the fileType param to NULL marking that the -t flag has been handled and
 * then calls the chooseNextFunc function to determine which function the file should be
 * sent to next depending on what flags are left to handle.
 * @param dirent
 * @param target
 * @param tabSpaces
 * @param count
 * @param buf
 * @param b
 * @param SFlag
 * @param subStr
 * @param fileSize
 * @param depth
 * @param argsFlag
 * @param fileType
 */
void displayFileTypeFlag(struct dirent *dirent, char *target, int tabSpaces, int count, struct stat *buf, ssize_t b,
                         int SFlag, char *subStr, int fileSize, int depth, int argsFlag, char *fileType) {
    argsFlag--;
    funcTarget funcTargCall = NULL;
    int x;
    if (strcmp(fileType, "d") == 0) {
        x = DT_DIR;
    }
    if (strcmp(fileType, "f") == 0) {
        x = DT_REG;
    }
    if (dirent->d_type == x) {
        printFile(dirent, target, tabSpaces, count, buf, SFlag, argsFlag);
        fileType = NULL;
        chooseNextFunc(dirent, target, tabSpaces, count, buf, b, SFlag, subStr, fileSize, depth, argsFlag, fileType,
                       funcTargCall);
    }
}

/**
 * Takes in information for a file and the flags from the cmd args.
 * Then uses the checkSize function to see if the current file is smaller than the
 * size param specified and only executes the rest of the function on those files.
 * it then call the printFile function to print the file if all requirements are met.
 * It then sets the fileType param to NULL marking that the -t flag has been handled and
 * then calls the chooseNextFunc function to determine which function the file should be
 * sent to next depending on what flags are left to handle.
 * @param dirent
 * @param target
 * @param tabSpaces
 * @param count
 * @param buf
 * @param b
 * @param SFlag
 * @param subStr
 * @param fileSize
 * @param depth
 * @param argsFlag
 * @param fileType
 */
void displayForSizeFlag(struct dirent *dirent, char *target, int tabSpaces, int count, struct stat *buf, ssize_t b,
                        int SFlag, char *subStr, int fileSize, int depth, int argsFlag, char *fileType) {
    argsFlag--;
    funcTarget funcTargCall = NULL;
    if (checkSize(*buf, fileSize) == 1) {
        // Changes for symbolic link
        printFile(dirent, target, tabSpaces, count, buf, SFlag, argsFlag);
        fileSize = 0;
        chooseNextFunc(dirent, target, tabSpaces, count, buf, b, SFlag, subStr, fileSize, depth, argsFlag, fileType,
                       funcTargCall);
    }
}

/**
 * Takes in information for a file and the flags from the cmd args.
 * Then splits the subStr into the string to find and the depth.
 * Then uses the checkSubstr function to see if the file name contains the substr
 * and is within the specified depth and only executes the rest of the function on those files.
 * it then call the printFile function to print the file if all requirements are met.
 * It then sets the subStr param to NULL marking that the -s flag has been handled and
 * then calls the chooseNextFunc function to determine which function the file should be
 * sent to next depending on what flags are left to handle.
 * @param dirent
 * @param target
 * @param tabSpaces
 * @param count
 * @param buf
 * @param b
 * @param SFlag
 * @param subStr
 * @param fileSize
 * @param depth
 * @param argsFlag
 * @param fileType
 */
void displayForStringFlag(struct dirent *dirent, char *target, int tabSpaces, int count, struct stat *buf, ssize_t b,
                          int SFlag, char *subStr, int fileSize, int depth, int argsFlag, char *fileType) {
    argsFlag--;
    funcTarget funcTargCall = NULL;
    if (dirent->d_type == DT_DIR) {
        return;
    } else {
        char *str1;
        char *str2;
        splitStringOnSpace(subStr, &str1, &str2);
        if (DT_DIR && checkSubstr(dirent->d_name, str1, depth, atoi(str2)) == 1) {
            printFile(dirent, target, tabSpaces, count, buf, SFlag, argsFlag);
            subStr = NULL;
            chooseNextFunc(dirent, target, tabSpaces, count, buf, b, SFlag, subStr, fileSize, depth, argsFlag, fileType,
                           funcTargCall);
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
        funcTarget funcTargCall = NULL;
        if (lstat(cwd, &buf) < 0) {
            printf("lstat error for: %s\n", dirent->d_name);
        }

        if (subStr != NULL) {
            funcTargCall = &displayForStringFlag;
        } else if (fileType != NULL) {
            funcTargCall = &displayFileTypeFlag;
        } else if (fileSize != 0) {
            funcTargCall = &displayForSizeFlag;
        } else if (SFlag == 1) {
            funcTargCall = &displayStatFlag;
        } else {
            funcTargCall = &displayForNoFlag;
        }
        (*funcTargCall)(dirent, target, tabSpaces, count, &buf, b, SFlag, subStr, fileSize, depth, argsFlag,
                        fileType);

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


    char *root;
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
        root = get_current_directory_name();
    } else {
        startingFolder = argv[1];
        root = argv[1];
    }
    printf("STARTING DIR\n[%s]\n",root);
    tabSpaces++;
    while ((opt = getopt(argc, argv, "Ss:f:t:")) != -1) {
        switch (opt) {
            case 'S':
                argFlag++;
                SFlag = 1;
                break;
            case 'f':
                subStr = optarg;
                argFlag++;
                break;
            case 's':
                argFlag++;
                fileSize += atoi(optarg);
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