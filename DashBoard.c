#include <stdio.h>
#include <time.h>
#include <unistd.h>

#define MEMINFO_FILE "/proc/meminfo"

// Function to read memory information from /proc/meminfo
int read_memory_info(unsigned long *total_mem, unsigned long *free_mem) {
    FILE *fp = fopen(MEMINFO_FILE, "r");
    if (fp == NULL) {
        perror("Error opening /proc/meminfo");
        return -1;
    }

    // Variables to store memory information
    unsigned long mem_total = 0;
    unsigned long mem_free = 0;
    char buffer[256];

    while (fgets(buffer, sizeof(buffer), fp)) {
        if (sscanf(buffer, "MemTotal: %lu kB", &mem_total) == 1) {
            *total_mem = mem_total;
        }
        if (sscanf(buffer, "MemFree: %lu kB", &mem_free) == 1) {
            *free_mem = mem_free;
        }
    }

    fclose(fp);
    return 0;
}

int main() {
    while (1)
    {
        FILE *temperatureFile;
        double T;
        temperatureFile = fopen ("/sys/class/thermal/thermal_zone0/temp", "r");
        if (temperatureFile == NULL)
          printf("Tempurature file not found.");
        fscanf (temperatureFile, "%lf", &T);
        T /= 1000;
        printf ("The temperature is %6.3f C.\n", T);
        fclose (temperatureFile);
        usleep(5000000);

        unsigned long total_mem, free_mem;

        if (read_memory_info(&total_mem, &free_mem) == 0) {
            printf("Total Memory: %lu kB\n", total_mem);
            printf("Free Memory: %lu kB\n", free_mem);
            // Calculate and print used memory
            printf("Used Memory: %lu kB\n", total_mem - free_mem);
        }
    }
}