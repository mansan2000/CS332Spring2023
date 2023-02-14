/* Sample C program to illustrate the use of opendir, readdir, and closedir
 * system calls. This version prints the file type next to the file name.
 */
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

// The function fileType can be used to determine the type of file (e.g. directory, a socket, a symbolic link, ...).
char *fileType(unsigned char type) {
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

void traverseDirectory(char *path, int tabSpaces){

    struct dirent *dirent;
    DIR *parentDir;
    parentDir = opendir (path);
    if (parentDir == NULL) {
        printf ("Error opening directory '%s'\n", path);
        exit (-1);
    }
    // Before we can read the contents of the directory, we must open the directory.
    int count = 1;
    // While there's still something left to read in the directory ...
    while((dirent = readdir(parentDir)) != NULL){
        if(strcmp())
        // Print the name of the file and its type.
        printf ("[%d] %s (%s)\n", count, dirent->d_name, fileType(dirent->d_type));
        count++;
    }


    closedir (parentDir);

}


int main (int argc, char **argv) {
//    struct dirent *dirent;
//    DIR *parentDir;

    if (argc < 2) {
        printf ("Usage: %s <dirname>\n", argv[0]);
        exit(-1);
    }


    return 0;
}