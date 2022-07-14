#include <iostream>
#include <memory>
using namespace std;

//定义了一个类,里面有一个private成员,我们不希望别人直接访问
struct TestCls {
  TestCls() { value = make_shared<int>(3); }

 private:
  shared_ptr<int> value;
};

///////////////////////////////////////////////////////////////////
//这是一个指向类的成员变量的指针类型
typedef shared_ptr<int> TestCls::*stolen_mem_ptr;

//模板定义一个友元函数,返回指向类的成员变量的指针.
template <stolen_mem_ptr MemPtr>
struct Robber {
  friend stolen_mem_ptr steal() { return MemPtr; }
};
//模板显式初始化, 可以忽略private修饰符, 这样友元函数就可以
//获得指向成员的指针,并且忽略了private
template struct Robber<&TestCls::value>;
stolen_mem_ptr steal();
///////////////////////////////////////////////////////////////////

int main() {
  auto f = new TestCls();
  //返回指向成员的指针,忽略了private修饰符
  auto accessor = steal();
  //访问私有成员
  cout << "Private member value: " << *(f->*accessor) << endl;
  *(f->*accessor) = 5;
  cout << "Modify member value to: " << *(f->*accessor) << endl;
  return 0;
}