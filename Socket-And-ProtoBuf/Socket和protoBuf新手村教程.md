# C# Socket和protoBuf新手村教程

## Boss->Socket

此教程纯属Socket初级应用篇，因为网上全是理论篇（实践才是王道）

### 1级->Client创建

1. 首先创建一个C#命令行工程（别告诉这个不会）
2. 创建Socket实例，别忘了引用System.Net和System.Net.Sockets

    ``` csharp
    Socket client = new Socket(SocketType.Stream, ProtocolType.Tcp); // TCP链接
    ```

    * [Socket](https://docs.microsoft.com/en-us/dotnet/api/system.net.sockets.socket?redirectedfrom=MSDN&view=netframework-4.8)

3. 设置要链接的服务器ip地址，IPAddress是C#提供的ip封装类

    ``` csharp
    IPAddress ip = IPAddress.Parse("127.0.0.1"); // 本地地址127.0.0.1（别说你不知道）
    ```

    * [IPAddress](https://docs.microsoft.com/en-us/dotnet/api/system.net.ipendpoint?redirectedfrom=MSDN&view=netframework-4.8)

4. 设置要链接的服务器ip和端口，IPEndPoint是C#提供的ip和端口的封装类

    ``` csharp
    IPEndPoint point = new IPEndPoint(ip, 2333); // 端口为2333，ip为上一段代码的ip
    ```

5. 链接

    ``` csharp
    client.Connect(point);
    // client.Connect("127.0.0.1", 2333); // 等同于3,4
    ```

6. 开启线程接收服务器消息，别忘了引用System.Threading

    ``` csharp
    Thread thread = new Thread(Recive);
    thread.IsBackground = true; // 后台执行线程
    thread.Start(client); // 传入客户端的Socket
    ```

    ```csharp
    // Recive函数
    static void Recive(object o)
    {
        var client = o as Socket;
        while (true)
        {
            byte[] buffer = new byte[1024 * 1024 * 2];
            int effective = client.Receive(buffer); //二进制数据存储在buffer中，数据长度为effective
            if (effective == 0)
            {
                break;
            }
            var str = Encoding.UTF8.GetString(buffer, 0, effective); // 将二进制数据转换为UTF8格式的String
            Console.WriteLine(str);
        }
    }
    ```

    * [Recieve函数](https://docs.microsoft.com/zh-cn/dotnet/api/system.net.sockets.socket.receive?redirectedfrom=MSDN&view=netframework-4.8#overloads)

7. 发送自定义数据给服务器

    ``` csharp
    while (true)
    {
        string s = Console.ReadLine();
        byte[] buffer = Encoding.ASCII.GetBytes(s); // 将数据转换为ASCII编码的二进制数组形式
        socketClient.Send(buffer); // 发送消息
        Console.WriteLine("Send Message");
    }
    ```

8. client完整代码

``` csharp
using System;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;

namespace SocketTest
{
    class Program
    {
        static void Main(string[] args)
        {
            Socket client = new Socket(SocketType.Stream, ProtocolType.Tcp);
            IPAddress ip = IPAddress.Parse("127.0.0.1");
            IPEndPoint point = new IPEndPoint(ip, 2333);
            client.Connect("127.0.0.1", 2333);

            Thread thread = new Thread(Recive);
            thread.IsBackground = true;
            thread.Start(client);

            while (true)
            {
                string s = Console.ReadLine();
                byte[] buffer = Encoding.ASCII.GetBytes(s);
                client.Send(buffer);
                Console.WriteLine("Send Message");
            }
        }

        static void Recive(object o)
        {
            var client = o as Socket;
            while (true)
            {
                byte[] buffer = new byte[1024 * 1024 * 2];
                var effective = client.Receive(buffer);
                if (effective == 0)
                {
                    break;
                }
                var str = Encoding.UTF8.GetString(buffer, 0, effective);
                Console.WriteLine(str);
            }
        }
    }
}
```

### 2级->Server创建

1. 首先创建一个C#命令行工程（别告诉这个不会）
2. 创建Socket实例（同client）
3. 设置服务器的ip地址

    ``` csharp
    IPAddress ip = IPAddress.Parse("127.0.0.1");
    IPEndPoint point = new IPEndPoint(ip, 2333);
    server.Bind(point);
    ```

4. 设置服务器的最大监听数

    ``` cs
    server.Listen(10);
    ```

5. 开启线程接收客户端连接和数据（※注意是连接）

    ``` cs
    Thread thread = new Thread(Listen);
    thread.IsBackground = true;
    thread.Start(serverSocket);
    ```

    ``` cs
    // Listen函数，等待客户端连接
    static void Listen(object o)
    {
        var serverSocket = o as Socket;
        while (true)
        {
            client = serverSocket.Accept(); // 等待客户端连接，返回客户端的Socket，之前的10限制就是在这里，最多有10个客户端可以建立连接
            var sendIpoint = client.RemoteEndPoint.ToString(); // 客户端的ip和端口
            Console.WriteLine($"{sendIpoint}Connection");
            // 连接成功则开启一个接收线程接收客户端发来的消息
            Thread thread = new Thread(Recive);
            thread.IsBackground = true;
            thread.Start(client);
        }
    }
    ```

    ``` cs
    // Recive函数，同客户端
    ```

6. server完整代码

``` cs
using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;

namespace SocketServer
{
    class Program
    {
        static void Main(string[] args)
        {
            Socket server = new Socket(SocketType.Stream, ProtocolType.Tcp);
            IPAddress ip = IPAddress.Parse("127.0.0.1");
            IPEndPoint point = new IPEndPoint(ip, 2333);
            server.Bind(point);
            server.Listen(10);

            Thread thread = new Thread(Listen);
            thread.IsBackground = true;
            thread.Start(server);

            Console.Read();
        }

        static void Listen(object o)
        {
            var server = o as Socket;
            while (true)
            {
                client = server.Accept();
                var clientIpoint = client.RemoteEndPoint.ToString();
                Console.WriteLine($"{clientIpoint}Connection");
                Thread thread = new Thread(Recive);
                thread.IsBackground = true;
                thread.Start(client);
            }
        }

        static void Recive(object o)
        {
            var client = o as Socket;
            while (true)
            {
                byte[] buffer = new byte[1024 * 1024 * 2];
                var effective = client.Receive(buffer);
                if (effective == 0)
                {
                    break;
                }
                var str = Encoding.UTF8.GetString(buffer, 0, effective);
                Console.WriteLine(str);
            }
        }
    }
}
```

## Boss->ProtoBuf

如果我们要用ProtoBuf用在C#中就得集齐各种神器

1. [ProtoBuf源码](https://github.com/protocolbuffers/protobuf/tree/v3.8.0)：其中有C#的示例代码
2. [ProtoBuf编译器](https://github.com/protocolbuffers/protobuf/releases/tag/v3.8.0)：编译`.proto`文件
3. [ProtoBuf的C#工具集](https://www.nuget.org/packages/Google.Protobuf/3.8.0)(你可能会需要下载nuget)：提供工程中的dll引用文件
4. [ProtoBuf官方教程](https://developers.google.com/protocol-buffers/)(科学上网)

### 1级->编写proto文件

都说ProtoBuf不依赖于任何语言是一个跨语言的神器，然而他的语言格式是scheme(Lisp的方言)，并且编译器就是把`.proto`文件翻译成各个不同语言的编译器。

proto文件示例(教程中示例的文件)

``` scheme
// [START declaration]
syntax = "proto3";
package tutorial;

import "google/protobuf/timestamp.proto";
// [END declaration]

// [START java_declaration]
option java_package = "com.example.tutorial";
option java_outer_classname = "AddressBookProtos";
// [END java_declaration]

// [START csharp_declaration]
option csharp_namespace = "Google.Protobuf.Examples.AddressBook";
// [END csharp_declaration]

// [START messages]
message Person {
  string name = 1;
  int32 id = 2;  // Unique ID number for this person.
  string email = 3;

  enum PhoneType {
    MOBILE = 0;
    HOME = 1;
    WORK = 2;
  }

  message PhoneNumber {
    string number = 1;
    PhoneType type = 2;
  }

  repeated PhoneNumber phones = 4;

  google.protobuf.Timestamp last_updated = 5;
}

// Our address book file is just one of these.
message AddressBook {
  repeated Person people = 1;
}
// [END messages]
```

### 2级->编译proto文件

将上面的文件用proto.exe编译

``` vim
格式：proto -I=当前目录 -out_csharp=当前目录 目录/文件名.扩展名
例：
文件名为：address.proto
目录为：D:/Work下
proto -I=D:/Work -out_csharp=D:/Work D:/Wrok/address.proto
```

编译完后会生成一个`.cs`文件，文件很长我就不展示了

### 3级->nuget下载dll

``` cs
nuget install Google.Protobuf -Version 3.8.0 // 版本随意
```

下载下来找到dll

``` vim
Google.Protobuf.3.8.0/bin/net45/Google.Protobuf.dll
```

引用到客户端和服务器中，然后把生成的`.cs`文件也复制到项目中

### 4级->编写序列化和反序列化代码

在客户端和服务器的Program（上面的代码）中加入序列化和反序列化的函数，需要引用Google.Protobuf、Google.Protobuf.Examples.AddressBook和static Google.Protobuf.Examples.AddressBook.Person.Types(C#6 才支持)

``` cs
public static byte[] Serialize<T>(T obj) where T : IMessage
{
    return obj.ToByteArray();
}

public static T Deserialize<T>(byte[] data) where T : class, IMessage, new()
{
    T obj = new T();
    IMessage message = obj.Descriptor.Parser.ParseFrom(data);
    return message as T;
}
```

注释：

1. 可以看到由`.proto`转换成`.cs`的文件的父接口为IMessage
2. ToByteArray()是protoBuf自带的类转二进制的函数（所谓的序列化）
3. obj.Descriptor.Parser.ParseFrom是是protoBuf自带的二进制转类的函数（所谓的反序列化）

知道这些之后就可以传输二进制数据啦，所以我们的客户端代码的发送数据部分改为

``` cs
// 建立数据
Person john = new Person
{
    Id = 1234,
    Name = "John Doe",
    Email = "jdoe@example.com",
    Phones = { new PhoneNumber { Number = "555-4321", Type = PhoneType.Home } }
};
var message = Serialize(john); // 得到byte[]的message

while (true)
{
    string s = Console.ReadLine();
    socketClient.Send(message); //  直接传输message
    Console.WriteLine("Send Message");
}
```

服务端的接受部分改一下，这部分注意反序列化素组的长度必须和序列化后的一致，所以这边新建了一个正确长度的b2数组把数据复制过去

``` cs
static void Recive(object o)
{
    var send = o as Socket;
    while (true)
    {
        byte[] buffer = new byte[1024 * 1024 * 2];
        var effective = send.Receive(buffer);
        byte[] b2 = new byte[effective];
        Array.Copy(buffer, 0, b2, 0, effective); // 把数据拷贝给b2
        if (effective == 0)
        {
            break;
        }
        var message = Deserialize<Person>(b2); // 解析时候必须为正确的长度
        Console.WriteLine("ID = {0}", message.Id);
        Console.WriteLine("Name = {0}", message.Name);
        Console.WriteLine("Email = {0}", message.Email);
        Console.WriteLine("Phone Number = {0}", message.Phones[0].Number);
        Console.WriteLine("Phone Type = {0}", message.Phones[0].Type);
    }
}
```

完结撒花~
