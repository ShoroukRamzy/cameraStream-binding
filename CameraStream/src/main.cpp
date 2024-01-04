#include <json-c/json.h>
#include "CameraManager.h"
#include "Config.h"
#include "VirtualCamera.h"
#include<iostream>
afb::event camera_event;

void start (afb::req req,afb::received_data param)
{
	AFB_NOTICE("Starting CameraStream Microservice!");
	std::string config_file_path{"CameraStream/config/virual_camera_config.json"};//to be extracted from param
    Config config;
	std::unique_ptr<StreamHandlerIF> virtual_camera;
	try{
		
		camera_stream_types::VirtualCamConfig config_s=config.read(std::move(config_file_path));
         if(config_s.type=="VIRTUAL")
			 virtual_camera=std::make_unique<VirtualCamera>();
	    CameraManager camera_mgr(std::move(virtual_camera),std::move(config_s),camera_event);
		camera_mgr.run();
	}
	catch(const std::runtime_error & e)
	{
	
		AFB_NOTICE("runtime_error caught in start");
		AFB_NOTICE(e.what());
	}

	catch(const std::exception & e)
	{
		
		AFB_NOTICE("exception caught in start");
		AFB_NOTICE(e.what());

	}

	req.reply(0);
}

void subscribe (afb::req req,afb::received_data param)
{

    AFB_NOTICE("$OTA::subscribe CameraStream!");
	req.subscribe(camera_event);


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
afb::verb<start>("start"),
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
