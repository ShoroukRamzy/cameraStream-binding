#include <json-c/json.h>
//#include "wrap-json.h"

#define AFB_BINDING_VERSION 4
#include <afb/afb-binding>
using namespace std;


void cameraEventHandler(void *closure,const char *event_name,unsigned nparams,afb_data_x4_t const params[],afb_api_x4_t api)
{
    static int count{0};
    AFB_NOTICE("start image object detection on image%d!", count++);
}


int mainctl(afb_api_x4_t api,afb_ctlid_t ctlid,afb_ctlarg_t ctlarg,void *userdata)
{
afb::api API(api);

	if (ctlid == afb_ctlid_Init)
	{
		AFB_NOTICE("init Object Detection!");
		afb_api_require_api(api, "CameraStream", 0);
		afb_api_call_sync(api, "CameraStream", "subscribe", 0, NULL, NULL, NULL, NULL);
		afb_api_event_handler_add(api, "CameraStream/camera_event", cameraEventHandler, NULL);
		
	}
	return 0;

}

const afb_verb_t verbs[]={
afb::verbend()
};


const afb_binding_t afbBindingExport=afb::binding(
    "ObjectDetection",
    verbs,
    "ObjectDetection API",
    mainctl
);
