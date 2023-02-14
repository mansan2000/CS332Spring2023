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
  switch(type) {
  case DT_BLK: str = "block device"; break;
  case DT_CHR: str = "character device"; break;
  case DT_DIR: str = "directory"; break;
  case DT_FIFO: str = "named pipe (FIFO)"; break;
  case DT_LNK: str = "symbolic link"; break;
  case DT_REG: str = "regular file"; break;
  case DT_SOCK: str = "UNIX domain socket"; break;
  case DT_UNKNOWN: str = "unknown file type"; break;
  default: str = "UNKNOWN";
  }
  return str;
}

void printStat(struct stat sb, int tab){



    printf("%*s  File Permissions:         ", tab, " ");
    printf( (S_ISDIR(sb.st_mode)) ? "d" : "-");
    printf( (sb.st_mode & S_IRUSR) ? "r" : "-");
    printf( (sb.st_mode & S_IWUSR) ? "w" : "-");
    printf( (sb.st_mode & S_IXUSR) ? "x" : "-");
    printf( (sb.st_mode & S_IRGRP) ? "r" : "-");
    printf( (sb.st_mode & S_IWGRP) ? "w" : "-");
    printf( (sb.st_mode & S_IXGRP) ? "x" : "-");
    printf( (sb.st_mode & S_IROTH) ? "r" : "-");
    printf( (sb.st_mode & S_IWOTH) ? "w" : "-");
    printf( (sb.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n");
//    printf("I-node number:            %ld\n", (long) sb.st_ino);
//
//    printf("  Mode:                     %lo (octal)\n",
//           (unsigned long) sb.st_mode);
//
//    printf("Link count:               %ld\n", (long) sb.st_nlink);
//    printf("Ownership:                UID=%ld   GID=%ld\n",
//           (long) sb.st_uid, (long) sb.st_gid);

//    printf("Preferred I/O block size: %ld bytes\n",
//           (long) sb.st_blksize);
    printf("%*s  File size:                %lld bytes\n", tab, " ",
           (long long) sb.st_size);
//    printf("Blocks allocated:         %lld\n",
//           (long long) sb.st_blocks);

//    printf("Last status change:       %d", ctime(&sb.st_ctime));
    printf("%*s  Last file access:         %s\n", tab, " ", ctime(&sb.st_atime));
//    printf("Last file modification:   %d", ctime(&sb.st_mtime));
}

void traverseDirectory(char *path, char *relativePath, int tabSpaces) {

    struct dirent *dirent;
    DIR *parentDir;

    // First, we need to open the directory.
    parentDir = opendir(path);
    if (parentDir == NULL) { 
        printf ("Error opening directory '%s'\n", path); 
        exit (-1);
    }
    int count = 1; 
    // After we open the directory, we can read the contents of the directory, file by file.
    char pathString[MAX_PATH_SIZE+1];
    char cwd[MAX_PATH_SIZE];
    while((dirent = readdir(parentDir)) != NULL){

        // If the file's name is "." or "..", ignore them. We do not want to infinitely recurse.
        if (strcmp(dirent->d_name, ".") == 0 || strcmp(dirent->d_name, "..") == 0) {
            continue;
        }



//        memmove(path, path + 1, strlen(path));
//        path[strlen(path)] = '\0';
//        printf("path%s\n", path);

//        strcat(cwd, path);
//        realpath(dirent->d_name, path);
//        printf("cwd %s\n", cwd);
//        printf("realPath %s\n", pathString);
        getcwd(cwd, sizeof (cwd));
//        if (dirent->d_type == DT_DIR){
////            printf("path: sdf :%s\n", relativePath);
////            strcat(path, dirent->d_name);
////            strcat(cwd,"/");
//
//        }
        strcat(cwd,"/");
        strcat(cwd, relativePath);
//        strcat(cwd, path);
        strcat(cwd,"/");
        strcat(cwd, dirent->d_name);
//        printf("cwd %s\n", cwd);

//        printf("cwdCAT %s\n", cwd);
//        realpath(dirent->d_name, cwd);
//        printf("cwd %s\n", cwd);
        struct stat buf;
//        printf("test %s\n", pathString);
//        printf("test %ld\n", buf.st_size);
        if (lstat(cwd, &buf) < 0){
            printf("lstat error for: %s\n", dirent->d_name);
        }








        // Changes for symbolic link
        char target[PATH_MAX];
        ssize_t b;
        if (dirent->d_type == DT_LNK){
            b = readlink(dirent->d_name, target, PATH_MAX - 1);
            printf("%*s[%d] %s (symbolic link to %s)\n", 4 * tabSpaces, " ", count, dirent->d_name, target);
        } else {
            // Print the formatted file.
            printf("%*s[%d] %s (%s)\n", 4 * tabSpaces, " ", count, dirent->d_name, filetype(dirent->d_type));

        }
        printStat(buf, 4 * tabSpaces);

        count++;
        // Check to see if the file type is a directory. If it is, recursively call traverseDirectory on it.
        if (dirent->d_type == DT_DIR) {
            // Build the new file path.
            char *subDirPath = (char *) malloc(MAX_PATH_SIZE);
//            printf("path: %s\n", path);
            strcpy(subDirPath, path);
            strcat(relativePath, "/");
            strcat(relativePath, dirent->d_name);
            strcat(subDirPath, "/");
            strcat(subDirPath, dirent->d_name);
//            printf("relativePath: %s\n", relativePath);
//            printf("subDirPath: %s\n", subDirPath);
            traverseDirectory(subDirPath, relativePath , tabSpaces + 1);
        }
    } 
}

int main(int argc, char **argv) {

    int tabSpaces = 0;
    char relativePath[MAX_PATH_SIZE];

    // Check to see if the user provides at least 2 command-line-arguments.
    if (argc < 2) {
        traverseDirectory(".", relativePath, tabSpaces);
//        printf ("Usage: %s <dirname>\n", argv[0]);
//        exit(-1);
    } else {
        traverseDirectory(argv[1], relativePath, tabSpaces);
    }



    return 0;
}