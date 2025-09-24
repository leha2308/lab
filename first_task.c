#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>

int main(void) {
    pid_t pid, ppid, pgid;
    uid_t ruid, euid;
    gid_t rgid, egid;

    pid = getpid();
    if (pid == -1) {
        perror("Error getting PID");
        return 1;
    }

    ppid = getppid();
    if (ppid == -1) {
        perror("Error getting PPID");
        return 1;
    }

    pgid = getpgid(pid);
    if (pgid == -1) {
        perror("Error getting PGID");
        return 1;
    }

    ruid = getuid();
    euid = geteuid();
    rgid = getgid();
    egid = getegid();

    printf("Current process information:\n");
    printf("PID (process ID): %d\n", pid);
    printf("PPID (parent process ID): %d\n", ppid);
    printf("PGID (process group ID): %d\n", pgid);
    printf("Real UID (owner): %d\n", ruid);
    printf("Effective UID (owner): %d\n", euid);
    printf("Real GID (owner group): %d\n", rgid);
    printf("Effective GID (owner group): %d\n", egid);

    return 0;
}
