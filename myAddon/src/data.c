#include <node_api.h>
#include <openssl/rand.h>
#include "data.h"

/**
 * @brief generate a 16 bytes long data
 *
 * @return the generated data
 */
unsigned char *getData(void) {
	unsigned char *data = malloc(16);
	RAND_bytes(data, 16);
	return data;
}

/***** N-API wrapper for the function *****/ 

napi_value GetDataWrapper(napi_env env, napi_callback_info info) {
  
  napi_status status;
  napi_value buffer;

  // call to my custom function
  unsigned char* data = getData();
  status = napi_create_buffer(env, sizeof(data), &buffer, data);

  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Failed to get data from my custom function");
    return NULL;
  }

  return buffer;
}

/***** Module Initialization *****/ 

napi_value Init(napi_env env, napi_value exports) {

  napi_status status;  
  napi_value fn;
  
  status = napi_create_function(env, NULL, 0, GetDataWrapper, NULL, &exports);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Failed to create function");
    return NULL;
  }

  status = napi_set_named_property(env, exports, "getRandomData", fn);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Failed to set property");
    return NULL;
  }

  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
