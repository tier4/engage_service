# Node Communication Test for engage_service_dummy

## Description

The following aspects are tested.

|Check Point No.|Description|
|---|---|
|1|Must be able to respond to requests for service communication. In the sequence diagram of the module design document, the service provided by own module/own node corresponds.|
|2|If it is not ready to accept a request for service communication, it shall not accept the service request. (The service requester must know that the service cannot be requested.) In the sequence diagram of the module design document, the service provided by own module/own node corresponds.|

## Test coverage

The correspondence between the test objects and the point of view is as follows.

|Test Target No.|Test Target|Check Point No.|
|---|---|---|
|1| `/api/external/set/engage`            |1|

* About checkpoint 2 in this module  
   The services handled by this module are ready immediately after node startup. Therefore, it is impossible to check this checkpoint.

### Common test procedure

**Step.1**

Launch `engage_dummy_service` node with the following commands.
```sh
# Terminal-1
ros2 launch engage_relay_service engage_dummy_service.launch.xml
```

**Step.2**
Call the /api/external/set/engage service with the following command.
```sh
# Terminal-2
ros2 service call /api/external/set/engage tier4_external_api_msgs/srv/Engage "{engage: true}"
```

### Test procedure and criteria details

#### Test procedure and criteria details of target No.1

**After Step 2**

- Check point
  - `/api/external/set/engage`
    - Check Terminal-2 logs.

```sh
# Terminal-2
requester: making request: tier4_external_api_msgs.srv.Engage_Request(engage=True)

response:
tier4_external_api_msgs.srv.Engage_Response(status=tier4_external_api_msgs.msg.ResponseStatus(code=1, message='Received by EngageServiceDummy.'))

```
