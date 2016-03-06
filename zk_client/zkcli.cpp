// test the API about zookeeper client.
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "facade.h"

const char* zkhost = "172.16.130.1:2181,172.16.130.2:2181,172.16.130.3:2181,172.16.181.1:2181,172.16.181.2:2181";
const int session_timeout = 30000;	// 30s

static int connected = 0;
static int expired = 0;

void zkcli_watcher(zhandle_t* zkh, int type, int state, const char* path, void* context) {
	if(type == ZOO_SESSION_EVENT) {
		if(state == ZOO_CONNECTED_STATE) {
			connected = 1;
			printf("zkcli has connected to zookeeper cluster successfully.\n");
		}
		else if(state == ZOO_EXPIRED_SESSION_STATE) {
			expired = 1;
			connected = 0;
			printf("zookeeper session has expired.\n");
			zookeeper_close(zkh);
		}
	}
}

void create_zkcli_completion(int rc, const char* value, const void* data) {
	switch(rc) {
		case ZCONNECTIONLOSS:
			LOG_WARN(("connection loss"));
			break;
		case ZOK:
			LOG_INFO(("create /zkcli node"));
			break;
		case ZNODEEXISTS:
			LOG_WARN(("node already exists"));
			break;
		default:
			LOG_ERROR(("something went wrong when running for zkcli"));
			break;
	}
}


int main(int argc, const char* argv[]) {
	zoo_set_debug_level(ZOO_LOG_LEVEL_INFO);

	zhandle_t* zkhandle = zookeeper_init(zkhost, zkcli_watcher, session_timeout, 0, 0, 0);
	if(zkhandle == NULL) {
		fprintf(stderr, "error when connecting to zookeeper cluster\n");
		exit(EXIT_FAILURE);
	}

	int ret = zoo_acreate(zkhandle, "/zkcli", "alive", 5, &ZOO_OPEN_ACL_UNSAFE, ZOO_EPHEMERAL, create_zkcli_completion , "acreate");	
	if(ret) {
		fprintf(stderr, "error %d for %s\n", ret, "acreate");
		exit(EXIT_FAILURE);
	}

	zookeeper_close(zkhandle);

	return 0;
}
