--[[
    Copyright (C) 2019 - 2020 "IoT.bzh"
    Author Romain Forlot <romain.forlot@iot.bzh>

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.


    NOTE: strict mode: every global variables should be prefixed by '_'
--]]

function _callback(responseJ)
  _AFT.assertStrContains(responseJ.request.status, "success")
end

_AFT.testVerbStatusSuccess('testSubscribeSuccess','CameraStream', 'subscribe', {})
_AFT.setBefore("testSubscribeSuccess",function() print("~~~~~ Begin testSubscribeSuccess ~~~~~") end)
_AFT.setAfter("testSubscribeSuccess",function() print("~~~~~ End testSubscribeSuccess ~~~~~") end)

_AFT.testVerbCb('testSubscribeSuccessCallback','CameraStream', 'subscribe', {}, _callback)
  