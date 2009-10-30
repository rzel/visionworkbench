/* 
**  mod_plate.c -- Apache sample plate module
**  [Autogenerated via ``apxs -n plate -g'']
**
**  To play with this sample module first compile it into a
**  DSO file and install it into Apache's modules directory 
**  by running:
**
**    $ apxs -c -i mod_plate.c
**
**  Then activate it in Apache's httpd.conf file for instance
**  for the URL /plate in as follows:
**
**    #   httpd.conf
**    LoadModule plate_module modules/mod_plate.so
**    <Location /plate>
**    SetHandler plate
**    </Location>
**
**  Then after restarting Apache via
**
**    $ apachectl restart
**
**  you immediately can request the URL /plate and watch for the
**  output of this module. This can be achieved for instance via:
**
**    $ lynx -mime_header http://localhost/plate 
**
*/ 

#include "httpd.h"
#include "http_config.h"
#include "http_protocol.h"
#include "ap_config.h"
#include "http_core.h"

/* Forward declaration of the C++ callback function in mod_plate_io.h.
   This is our escape from C into higher level C++ where the plate
   lookup actually happens. */
void mod_plate_init();
void mod_plate_destroy();
int mod_plate_callback(request_rec *r);

/* The sample content handler */
static int plate_handler(request_rec *r) {
  r->content_type = "text/plain";      
  ap_rprintf(r, "hello there, bitches\n");
  return OK;
  //  return mod_plate_callback(r);
}

static void plate_register_hooks(apr_pool_t *p)
{
  // TODO: Move this to a better spot.  This is probably not the best
  // place to call mod_plate_init();
  //  mod_plate_init();
  ap_hook_handler(plate_handler, NULL, NULL, APR_HOOK_MIDDLE);
}

/* Dispatch list for API hooks */
module AP_MODULE_DECLARE_DATA plate_module = {
  STANDARD20_MODULE_STUFF, 
  NULL,                  /* create per-dir    config structures */
  NULL,                  /* merge  per-dir    config structures */
  NULL,                  /* create per-server config structures */
  NULL,                  /* merge  per-server config structures */
  NULL,                  /* table of config file commands       */
  plate_register_hooks  /* register hooks                      */
};

