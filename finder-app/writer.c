#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <file> <string>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    const char *text = argv[2];

    openlog("writer", LOG_PID | LOG_CONS, LOG_USER);

    FILE *fp = fopen(filename, "w");
    if (!fp) {
        syslog(LOG_ERR, "Error opening file %s: %s", filename, strerror(errno));
        fprintf(stderr, "Error opening file %s\n", filename);
        closelog();
        return 1;
    }

    if (fprintf(fp, "%s\n", text) < 0) {
        syslog(LOG_ERR, "Error writing to file %s: %s", filename, strerror(errno));
        fprintf(stderr, "Error writing to file %s\n", filename);
        fclose(fp);
        closelog();
        return 1;
    }

    fclose(fp);

    syslog(LOG_DEBUG, "Writing %s to %s", text, filename);

    closelog();

    return 0;
}
