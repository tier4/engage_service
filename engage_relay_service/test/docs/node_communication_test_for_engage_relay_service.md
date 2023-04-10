# Node Communication Test for engage_relay_service

## Description

The following aspects are tested.

|Check Point No.|Description|
|---|---|
|1|Must be able to respond to requests for service communication. In the sequence diagram of the module design document, the service provided by own module/own node corresponds.|
|2|If it is not ready to accept a request for service communication, it shall not accept the service request. (The service requester must know that the service cannot be requested.) In the sequence diagram of the module design document, the service provided by own module/own node corresponds.|
|3|This node must be able to provide service requests to other modules. In the sequence diagram of the module design document, the service requested by own module/own node corresponds.|
|4|After requesting services from other modules, a corresponding response must be received. In the sequence diagram of the module design document, the service requested by own module/own node corresponds.|

## Test coverage

The correspondence between the test objects and the point of view is as follows.

|Test Target No.|Test Target|Check Point No.|
|---|---|---|
|1| `/in_parking/set/auto_engage`         |1|
|2| `/api/external/set/engage`            |3|
|3| `/api/external/set/engage`            |4|

* About checkpoint 2 in this module  
   The services handled by this module are ready immediately after node startup. Therefore, it is impossible to check this checkpoint.

### Common test procedure

**Step.1**

Launch `engage_service_dummy` node with the following commands.
```sh
# Terminal-1
ros2 launch engage_relay_service engage_dummy_service.launch.xml
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

### Test procedure and criteria details

#### Test procedure and criteria details of target No.1

**After Step 3**

- Check point
  - `/in_parking/set/auto_engage`
    - Check Terminal-3 logs.

```sh
# Terminal-3
requester: making request: tier4_external_api_msgs.srv.Engage_Request(engage=True)

response:
tier4_external_api_msgs.srv.Engage_Response(status=tier4_external_api_msgs.msg.ResponseStatus(code=1, message='Received by EngageServiceDummy.'))

```

#### Test procedure and criteria details of target No.2

**After Step 3**

- Check point
  - `/api/external/set/engage`
    - Check the logs at Terminal-1 when the dummy module is serviced.

```sh
# Terminal-1
[engage_service_dummy_node-1] [DEBUG] [1676600229.478510002] [engage_service_dummy]: Requested /api/external/set/engage:engage: true
```

#### Test procedure and criteria details of target No.3

**After Step 3**

- Check point
  - `/api/external/set/engage`
    - Check Terminal-3 for the inclusion of the message 'Received by EngageServiceDummy.' received from the dummy module.

```sh
# Terminal-3
requester: making request: tier4_external_api_msgs.srv.Engage_Request(engage=True)

response:
tier4_external_api_msgs.srv.Engage_Response(status=tier4_external_api_msgs.msg.ResponseStatus(code=1, message='Received by EngageServiceDummy.'))

```
