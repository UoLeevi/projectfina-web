#include "uo_conf.h"
#include "uo_http.h"
#include "uo_http_server.h"
#include "uo_err.h"
#include "uo_prog.h"

void http_server_before_send_res(
    uo_cb *cb)
{
    uo_http_conn *http_conn = uo_cb_stack_index(cb, 0);
    uo_http_msg_set_header(&http_conn->http_res, "server", "libuo http");
    uo_cb_invoke(cb);
}

int main(
    int argc, 
    char **argv)
{
    uo_http_init();

    uo_conf *conf = uo_conf_create("projectfina-web.conf");

    const char *port = uo_conf_get(conf, "http_server.port");
    const char *root_dir = uo_conf_get(conf, "http_server.root_dir");

    uo_http_server *http_server = uo_http_server_create(port);

    uo_cb_append(http_server->evt_handlers.before_send_msg, http_server_before_send_res);

    if (!uo_http_server_set_opt_serve_static_files(http_server, root_dir, 0xA00000))
        uo_err_exit("Error while setting root directory.");

    uo_http_server_start(http_server);

    uo_prog_init();
    uo_prog_wait_for_sigint();

    uo_http_server_destroy(http_server);
    uo_conf_destroy(conf);

    return 0;
}
