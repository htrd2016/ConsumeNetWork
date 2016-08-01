# ConsumeNetWork
该工程目的是为了消耗系统网络资源，用于创造一个网络环境差的情况，以便测试在网络差的状态下client的性能。

工程分为两部分：

Server和Client，其中Server为接收数据端，Client为发送数据端。

Server启动方式:“./Server 监听端口 接收数据buffer大小”。

Client启动方式：“./Client 服务端IP 服务端端口 buffer大小”。
