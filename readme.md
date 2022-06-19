# ZeroMQ 简介

ZMQ (以下 ZeroMQ 简称 ZMQ) 是一个简单好用的传输层，像框架一样的一个 socket library，他使得 Socket 编程更加简单、简洁和性能更高。是一个消息处理队列库，可在多个线程、内核和主机盒之间弹性伸缩。ZMQ 的明确目标是 “成为标准网络协议栈的一部分，之后进入 Linux 内核”。现在还未看到它们的成功。但是，它无疑是极具前景的、并且是人们更加需要的 “传统”BSD 套接字之上的一层封装。ZMQ 让编写高性能网络应用程序极为简单和有趣。”

近几年有关”Message Queue” 的项目层出不穷，知名的就有十几种，这主要是因为后摩尔定律时代，分布式处理逐渐成为主流，业界需要一套标准来解决分布式计算环境中节点之间的消息通信。几年的竞争下来，Apache 基金会旗下的符合 AMQP/1.0 标准的 RabbitMQ 已经得到了广泛的认可，成为领先的 MQ 项目。

与 RabbitMQ 相比，ZMQ 并不像是一个传统意义上的消息队列服务器，事实上，它也根本不是一个服务器，它更像是一个底层的网络通讯库，在 Socket API 之上做了一层封装，将网络通讯、进程通讯和线程通讯抽象为统一的 API 接口。

ZMQ 跟 Socket 的区别是：普通的 socket 是端到端的（1:1 的关系），而 ZMQ 却是可以 N：M 的关系，人们对 BSD 套接字的了解较多的是点对点的连接，点对点连接需要显式地建立连接、销毁连接、选择协议（TCP/UDP）和处理错误等，而 ZMQ 屏蔽了这些细节，让你的网络编程更为简单。 


# ZMQ三种基本模式

## Request-Reply（应答模式）

应答模式特点：  
1. 客户端提出请求，服务端必须回答请求，每个请求只回答一次   
2.  客户端没有收到答复前，不能再次进行请求   
3. 可以有多个客户端提出请求，服务端能保证各个客户端只接收到自己的答复   
4. 如果服务端断掉或者客户端断掉会产生怎样的影响？
> 如果是客户端断掉，对服务端没有任何影响，如果客户端随后又重新启动，那么两方继续一问一答，但是如果是服务端断掉了，就可能会产生一些问题，这要看服务端是在什么情况下断掉的，如果服务端收是在回答完问题后断掉的，那么没影响，重启服务端后，双发继续一问一答，但如果服务端是在收到问题后断掉了，还没来得及回答问题，这就有问题了，那个提问的客户端迟迟得不到答案，就会一直等待答案，因此不会再发送新的提问，服务端重启后，客户端迟迟不发问题，所以也就一直等待提问。


python 实现客户端和服务端代码如下：

zmq_server.py
```python
import zmq 
context = zmq.Context()            #创建上下文
socket = context.socket(zmq.REP)   #创建Response服务端socket
socket.bind("tcp://*:5555")        #socket绑定，*表示本机ip，端口号为5555，采用tcp协议通信

while True:
    message = socket.recv()
    print(type(message))          #接收到的消息也会bytes类型(字节)
    print("收到消息：{}".format(message))
    socket.send(b"new message")   #发送消息，字节码消息
```
zmq_client.py
```python
import zmq

context = zmq.Context()
socket = context.socket(zmq.REQ)
socket.connect("tcp://localhost:5555")

socket.send(b"A message")
response = socket.recv()
print(response)
```
常用API
```python
#发送数据
socket.send_json(data)   #data 会被json序列化后进行传输 (json.dumps)
socket.send_string(data, encoding="utf-8")   #data为unicode字符串，会进行编码成子节再传输
socket.send_pyobj(obj)    #obj为python对象，采用pickle进行序列化后传输
socket.send_multipart(msg_parts)   # msg_parts, 发送多条消息组成的迭代器序列，每条消息是子节类型，
                                    # 如[b"message1", b"message2", b"message2"]

#接收数据
socket.recv_json()
socket.recv_string()
socket.recv_pyobj()
socket.recv_multipart()
```
 

## Publisher-Subscriber (发布-订阅模式)

publiser广播消息到所有客户端，客户端根据订阅主题过滤消息

python实现代码如下

zmq_server.py

```python
import zmq

context = zmq.Context()
socket = context.socket(zmq.PUB)
socket.bind("tcp://*:5555")
topic = ["client1", "client2"]
while True:
    for t in topic:
        data = "message for {}".format(t)
        msg = [t.encode("utf-8"), data.encode("utf-8")]     #列表中的第一项作为消息的topic，sub根据topic过滤消息
        print(msg)
        socket.send_multipart(msg)
```
zmq_client1.py
```python
import zmq
context = zmq.Context()
socket = context.socket(zmq.SUB)
socket.subscribe("client1")          #订阅主题topic为：client1
socket.connect("tcp://localhost:5555")
msg = socket.recv_multipart()
print(msg)
```
 
zmq_client2.py

```python
import zmq

context = zmq.Context()
socket = context.socket(zmq.SUB)
socket.subscribe("client2")     #订阅主题topic为：client2
socket.connect("tcp://localhost:5555")
msg = socket.recv_multipart()
print(msg)　
```



## Parallel Pipeline(并行管道模式)
  
管道模式有三部分组成，如下图所示，最左边的producer通过push产生任务， 中间的consumer接收任务处理后转发，最后result collector接收所有任务的结果。 相比于publisher-subscriber，多了一个数据缓存和处理负载的部分，当连接断开，数据不会丢失，重连后数据继续发送到客户端。



 

 

### python实现

producer.py
```python
import zmq

context = zmq.Context()
socket = context.socket(zmq.PUSH)
socket.bind("tcp://*:5577")
for num in range(2000):
    work_message = {"num": num}
    socket.send_json(work_message)
```

consumer.py

```python
import random
import zmq
context = zmq.Context()
consumer_id = random.randint(1, 1000)
#接收工作
consumer_receiver = context.socket(zmq.PULL)
consumer_receiver.connect("tcp://localhost:5577")
#转发结果
consumer_sender = context.socket(zmq.PUSH)
consumer_sender.bind("tcp://*:5578")
while True:
    msg = consumer_receiver.recv_json()
    data = msg["num"]
    result = {"consumer_id":consumer_id, "num":data}
    consumer_sender.send_json(result)
```

resultcollector.py
```python
import zmq

context = zmq.Context()
result_receiver = context.socket(zmq.PULL)
result_receiver.connect("tcp://localhost:5578")
result = result_receiver.recv_json()
collecter_data = {}
for x in range(1000):
    if result['consumer_id'] in collecter_data:
        collecter_data[result['consumer_id']] = collecter_data[result['consumer_id']] + 1
    else:
        collecter_data[result['consumer_id']] = 1
    if x == 999:
        print(collecter_data)
```
```
python producer.py
python consumer.py
python resultcollector.py
```
 