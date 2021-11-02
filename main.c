#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    DIR *directory;
    directory = opendir("./");

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
