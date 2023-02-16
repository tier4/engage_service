# PR #1 Test Procedure

## Table of contents

- (Node Communication Test)[#node-communication-test]

## Node Communication Test

### Test procedure

**Step.1**

Launch `engage_service_dummy` node with the following commands.
```sh
# Terminal-1
ros2 launch engage_service_dummy engage_service_dummy.launch.py
```

**Step.2**

Launch `engage_relay_service` node with the following commands.
```sh
# Terminal-2
ros2 launch engage_relay_service engage_relay_service.launch.py
```

**Step.3**
Call the /in_parking/set/auto_engage service with the following command.
```sh
# Terminal-3
ros2 service call /in_parking/set/auto_engage tier4_external_api_msgs/srv/Engage "{engage: true}"
```

### Test report

**After Step 3**

- Check point
  - `/in_parking/set/auto_engage`
    - Make a request to `/api/external/set/engage.`
    - Receive response from `/api/external/set/engage` and return that data in response to `/in_parking/set/auto_engage.`
    - Check with Terminal-3 logs.
- Result
  - OK

```sh
# Terminal-3
$ ros2 service call /in_parking/set/auto_engage tier4_external_api_msgs/ srv/Engage "{engage: true}"
requester: making request: tier4_external_api_msgs.srv.Engage_Request (engage=True)
   
response:
tier4_external_api_msgs.srv.Engage_Response (status=tier4_external_api_msgs.msg.ResponseStatus(code=1, message='Received by EngageServiceDummy.'))
```
