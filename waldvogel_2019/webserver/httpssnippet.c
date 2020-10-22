/* Bisherige Netzwerk-Header ausgelassen */
#include <tls.h>

int main(void) {
    /* bisheriger startServer Code mit gesetztem listenfd */

    uint8_t *mem;
	size_t mem_len;
    struct tls_config *cfg = NULL;
    struct tls *ctx = NULL; /* Server Context */
    struct tls *cctx = NULL; /* Individual Client Socket */

    cfg = tls_config_new();
    /* Lädt das Zertifikat inklusive Chain */
    mem = tls_load_file("/etc/letsencrypt/live/beispiel.flect.net/fullchain.pem", &mem_len, NULL);
    tls_config_set_cert_mem(cfg, mem, mem_len);
    /* Lädt den private Key eures Zertifikats */
    mem = tls_load_file("/etc/letsencrypt/live/beispiel.flect.net/privkey.pem", &mem_len, NULL);
    tls_config_set_key_mem(cfg, mem, mem_len);
    ctx = tls_server();
    tls_configure(ctx, cfg);

    int client = accept(listenfd, (struct sockaddr *)&clientaddr, &addrlen);
    tls_accept_socket(ctx, &cctx, client);

    char buffer[BUFFERSIZE];
    buffer_len = tls_read(cctx, buffer, sizeof(buffer));

    tls_write(cctx, buffer, buffer_len);

    close(client);
    tls_free(cctx);

    tls_close(ctx);
    tls_free(ctx);
}
