#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/errno.h>

int main(int argc, char *argv[]) {
    DIR *directory;
    
    if (argc < 2) {
        char dir[200];
        printf("Enter a directory: ");
        scanf("%s", dir);
        directory = opendir(dir);
    } else {
        directory = opendir(argv[1]);
    }
    
    if (directory == NULL) {
        errno = 2;
        printf("Error: %s\n", strerror(errno));
    } else {
        struct dirent *entry = readdir(directory);
        int size = 0;

        while (entry) {
            struct stat entry_stats;
            int i = stat(entry->d_name, &entry_stats);
            size += (entry_stats.st_size);

            if (entry->d_type == DT_DIR) {
                printf("Directory | Name: %s, Type: %d\n", entry->d_name, entry->d_type);
            } else printf("Regular File | Name: %s, Type: %d\n", entry->d_name, entry->d_type);

            entry = readdir(directory);
        }

        printf("\nTotal size: %d bytes\n", size);

        closedir(directory);
    }
}
