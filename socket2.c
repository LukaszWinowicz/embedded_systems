#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

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

int read_all(SSL *ssl, void *buf, size_t len)
{
    int ret = 0;
    unsigned char *bytes = buf;
    int remaining = (int)len;
    while (1) {
        /* Odczytaj blok danych */
        char buf[1024];
        int num_read = SSL_read(ssl, buf, sizeof(buf));
        if (num_read < 0)
            return errno;
        if (num_read == 0)
            break;
        /* Oceń czy można skopiować cały blok, czy tylko tyle ile sie zmieści */
        int to_copy = remaining < num_read ? remaining : num_read;
        if (!to_copy) {
            ret = ENOBUFS;
            continue;
        }

        /* Skopiuj odczytany kawałek do bufora */
        memcpy(bytes, buf, to_copy);
        remaining -= to_copy;
        bytes += to_copy;
    }
}

int write_all(SSL *ssl, const void *buf, size_t len)
{
    const unsigned char *bytes = buf;
    int remaining = (int)len;

    /* Jeżeli jest jeszcze coś do wpisania */
    while (remaining) {
        /* Wpisz ile się da */
        int num_written = SSL_write(ssl, bytes, remaining);
        if (num_written <= 0)
            return 1;

        /* Zauktualizuj ile jeszcze mamy wpisać */
        remaining -= num_written;

        /* Przesuń wskaźnik do jeszcze nie wpisanych danych */
        bytes += num_written;
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
    SSL_CTX* ctx = SSL_CTX_new(SSLv23_client_method());
    if (!ctx)
        return 1;

    int fd = connected_socket("46.41.138.133", 443);
    if (fd < 0)
        goto err_ssl_ctx_free;

    SSL* ssl = SSL_new(ctx);
    if (!ssl)
        goto err_close_fd;
    if (SSL_set_fd(ssl, fd) != 1 || SSL_connect(ssl) != 1)
        goto err_free_ssl;

    if (write_all(ssl, http_request, strlen(http_request)))
        goto err_free_ssl;

    char response[9000] = {0};
    if (read_all(ssl, response, sizeof(response) - 1)) {
        goto err_free_ssl;
    }

    printf("%s", response); // Wypisz odpowiedź serwera

    err_free_ssl:
        SSL_free(ssl);
    err_close_fd:
        close(fd);
    err_ssl_ctx_free:
        SSL_CTX_free(ctx);
        return 0;

}