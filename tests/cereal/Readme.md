Cereal library--快速入门
​

本文是一个简单的Cereal入门手册，需要支持C++11的编译器。

如何获取
只需要将Cereal头文件Include到你的项目中，你就可以开始使用Cereal。在Github上你可以获取到最近版本的Cereal(​​https://github.com/USCiLab/cereal​​)，然后将其解压到某个路径即可。再次说明，Cereal是一个纯头文件库，无需编译即可使用。

序列化类
使用Cereal，需要声明需要进行序列化的类。解决方法也很简单，在你需要的类中添加一个serialize函数。
```c++
struct MyClass
{
  int x, y, z;

  // 此函数告诉Cereal那些类需要序列化
  template<class Archive>
  void serialize(Archive & archive)
  {
    archive( x, y, z ); //需要进行存储的变量 
  }
};
```
Cereal是一个非常灵活的库。这意味着，你不仅可以在类定义之外去实现serialize函数，也可以将serialize函数分成load函数和save函数。关于此处的详细操作，你将会在“​​serialize函数​​”得到更加详细的了解。

Cereal也支持class versioning（是啥？）、私有序列化方法，甚至一些不支持默认构造函数的类。

Cereal可以全自动序列所有的原始数据类型和基本全部的标准库类型。

存储方式
Cereal目前支持三种基本的存储方式，二进制、XML和JSON。无论是那种存储方式，他们都将提供完整的读写操作。XML和JSON存储格式的文件是人类可读的，但是性能和速度比二进制差。关于存储方式具体细节，移步到“​​序列化类型”​​。

在使用某种存储方式时，需要包含对应的头文件：
```c++
#include <cereal/archives/binary.hpp>
#include <cereal/archives/portable_binary.hpp>
#include <cereal/archives/xml.hpp>
#include <cereal/archives/json.hpp>
```
序列化数据
在代码中，要使用Cereal，首先要创建一个Cereal数据存储类，然后把所有要序列化的数据发送给他即可。存储类使用了​​RAII​​规范，并保证只在析构时更新。存储类通常在其构造函数中使用了std::istream和std::ostream。

```c++
//MyClass见上文
#include <cereal/archives/binary.hpp>
#include <sstream>

int main()
{
  std::stringstream ss; // string stream

  {
    cereal::BinaryOutputArchive oarchive(ss); //创建一个二进制序列化存储类 
    MyClass m1, m2, m3;
    oarchive(m1, m2, m3); //将三个数据写到存储类中
  } // 存储类使用完毕，刷新内存

  {
    cereal::BinaryInputArchive iarchive(ss); // 读取类
    MyClass m1, m2, m3;
    iarchive(m1, m2, m3); // 从存储中读取数据
  }
}
```
注意：请如意Cereal使用了RAII规范。一些存储类只能在其析构时刷新其内容！当要序列化保存数据时，请务必保证在程序块结束之前析构该存储类，以刷新内存。

命名标签
Cereal支持对序列化的变量添加一个名字变量。这项特性在反序列化一个XML文件和JSON文件时非常有用，这样既可根据文件中的节点名给对应的变量赋值。
```c++
#include <cereal/archives/xml.hpp>
#include <fstream> 
int main() {
  {
    std::ofstream os("data.xml");
    cereal::XMLOutputArchive archive(os); 
    MyClass m1;
    int someInt;
    double d;

    archive( CEREAL_NVP(m1), // 根据序列化的对象的名称命名序列化结果
             someInt,        // 没有使用NVP宏的变量会随机指定一个名词
             cereal::make_nvp("this_name_is_way_better", d) ); // 给序列化对象指定名称
  } 
  {
    std::ifstream is("data.xml");
    cereal::XMLInputArchive archive(is);

    MyData m1;
    int someInt;
    double d;

    archive( m1, someInt, d ); // 名称在读取时并不必要
  }
}
```

上文中只简要列出了Cereal使用的方法。

Cereal可以处理智能指针、集成、多态等等特性。

如果想了解更多信息，请阅读[​​quick start](http://uscilab.github.io/cereal/quickstart.html)。

