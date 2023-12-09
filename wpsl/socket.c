
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

int connected_socket(const char *ip, unsigned short port)
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
        return -1;

    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_port = htons(port),
    };
    if (!inet_aton(ip, &addr.sin_addr))
        goto err_close;

    if (connect(fd, (const struct sockaddr *)&addr, sizeof(addr)))
        goto err_close;

    return fd;

err_close:
    close(fd);
    return -1;
}

int read_all(int fd, void *buf, size_t len)
{
    int ret = 0;
    unsigned char *bytes = buf;
    size_t remaining = len;
    while (1) {
        /* Odczytaj blok danych */
        char buf[1024];
        ssize_t num_read = read(fd, buf, sizeof(buf));
        if (num_read < 0)
            return errno;
        if (num_read == 0)
            break;
        /* Oceń czy można skopiować cały blok, czy tylko tyle ile sie zmieści */
        size_t to_copy = remaining < num_read ? remaining : num_read;
        if (!to_copy) {
            ret = ENOBUFS;
            continue;
        }

        /* Skopiuj odczytany kawałek do bufora */
        memcpy(bytes, buf, to_copy);
        remaining -= to_copy;
        bytes += to_copy;
    }
    return ret;
}

int write_all(int fd, const void *buf, size_t len)
{
    const unsigned char *bytes = buf;
    size_t remaining = len;

    /* Jeżeli jest jeszcze coś do wpisania */
    while (remaining) {
        /* Wpisz ile się da */
        ssize_t num_written = write(fd, bytes, remaining);
        if (num_written <= 0)
            return errno;

        /* Zauktualizuj ile jeszcze mamy wpisać */
        remaining -= (size_t)num_written;

        /* Przesuń wskaźnik do jeszcze nie wpisanych danych */
        bytes += (size_t)num_written;
    }
    return 0;
}

static const char *http_request =
    "GET /api/v1/displays/32621 HTTP/1.1\r\n"
    "Host: www.zditm.szczecin.pl\r\n"
    "Connection: close\r\n"
    "\r\n"
;

int main(void)
{
    int fd = connected_socket("46.41.138.133", 80);
    if (fd < 0)
        return 1;

    if (write_all(fd, http_request, strlen(http_request)))
        goto err_close_fd;

    char response[9000] = {0};
    if (read_all(fd, response, sizeof(response) - 1))
        goto err_close_fd;

    printf("%s", response);

err_close_fd:
    close(fd);

    return 0;
}