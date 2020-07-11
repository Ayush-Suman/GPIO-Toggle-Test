#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define GPIO_PIN 	"200"
#define GPIO_DIR 	"/sys/class/gpio/gpio200/direction"
#define GPIO_VAL 	"/sys/class/gpio/gpio200/value"
#define SLEEP_TIME 	50000

int main()
{


    int fd = open("/sys/class/gpio/export", O_WRONLY);
    if (fd == -1) {
        perror("Unable to open /sys/class/gpio/export");
        exit(1);
    }

    if (write(fd, GPIO_PIN, 3) != 3) {
        perror("Error writing to /sys/class/gpio/export");
        exit(1);
    }

    close(fd);


    fd = open(GPIO_DIR, O_WRONLY);
    if (fd == -1) {
        perror("Unable to open direction file");
        exit(1);
    }

    if (write(fd, "out", 3) != 3) {
        perror("Error writing to direction file");
        exit(1);
    }

    close(fd);

    fd = open(GPIO_VAL, O_WRONLY);
    if (fd == -1) {
        perror("Unable to open value file");
        exit(1);
    }


    for (int i = 0; i < 100; i++) {
        if (write(fd, "1", 1) != 1) {
            perror("Error writing to value file");
            exit(1);
        }
        usleep(SLEEP_TIME);

        if (write(fd, "0", 1) != 1) {
            perror("Error writing to /sys/class/gpio/gpio24/value");
            exit(1);
        }
        usleep(SLEEP_TIME);
    }

    close(fd);


    fd = open("/sys/class/gpio/unexport", O_WRONLY);
    if (fd == -1) {
        perror("Unable to open /sys/class/gpio/unexport");
        exit(1);
    }

    if (write(fd, GPIO_PIN, 3) != 3) {
        perror("Error writing to /sys/class/gpio/unexport");
        exit(1);
    }

    close(fd);

    return 0;
}
