#include <json-c/json.h>
//#include <wrap-json.h>

#define AFB_BINDING_VERSION 4
#include <afb/afb-binding>
using namespace std;

afb::event camera_event;
afb_timer_t timer;

void onTimer(afb_timer_x4_t timer, void *closure, int decount)
{
    static int count {0};
    AFB_NOTICE("$OTA::Capture image %d !",count++);
    camera_event.push();
}

void subscribe (afb::req req,afb::received_data param)
{

    AFB_NOTICE("$OTA::subscribe CameraStream!");
	req.subscribe(camera_event);

	afb_timer_create(&timer,
					 /*start:*/ 0 /*relative*/, 1 /*sec*/, 0 /*msec*/,
					 /*occur:*/ 0 /*infinite*/, 1000 /*period msec*/, 10 /*accuracy msec*/,
					 /*action:*/  (afb_timer_handler_t) onTimer, camera_event, 0 /*no unref*/);
	req.reply(0);

}
void unsubscribe (afb::req req,afb::received_data param)
{
	AFB_NOTICE("Unsubscribe CameraStream!");
	req.unsubscribe(camera_event);
	req.reply(0);
} 

int mainctl(afb_api_x4_t api,afb_ctlid_t ctlid,afb_ctlarg_t ctlarg,void *userdata)
{
    afb::api API(api);

	if (ctlid == afb_ctlid_Init)
	{
		 AFB_NOTICE("init CameraReader");
		camera_event = API.new_event("camera_event");
		if (!camera_event)
		{
			AFB_ERROR("??? Can't create camera Event !!");
			return -1;
		}
	}
	
	return 0;

}
struct afb_auth auth[]={
// /** authorized if LOA greater than or equal to data 'loa' */
// afb_auth_LOA,

// /** authorized if permission 'text' is granted */
// afb_auth_Permission,
	{
	.type=afb_auth_LOA,
	.loa=AFB_SESSION_LOA_1
	},
	{
	.type=afb_auth_LOA,
	.loa=AFB_SESSION_LOA_2
	},
	{
	.type=afb_auth_Permission,
	.text="access_permission"
	}
};


const afb_verb_t verbs[]={
afb::verb<subscribe>("subscribe"/*,nullptr,0,&auth[0]*/),//when I add loa=1 ,object detection can not subscribe
afb::verb<unsubscribe>("unsubscribe"/*,nullptr,0,&auth[1]*/),
afb::verbend()
};

// afbBindingExport is a must , 
// any other name make it not recognized as a binding
const afb_binding_t afbBindingExport=afb::binding(
    "CameraStream",
    verbs,
    "cameraStream API",
    mainctl
);
