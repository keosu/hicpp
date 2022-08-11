#include <boost/assign/list_of.hpp>
#include <boost/process.hpp>
#include <iostream>
#include <string>
#include <vector>

using namespace boost::process;

int main() {
  std::string exec = find_executable_in_path("hostname");
  std::vector<std::string> args = boost::assign::list_of("hostname");
  context ctx;
  ctx.environment = self::get_environment();
  child c = launch(exec, args, ctx);
  status s = c.wait();
  if (s.exited()) std::cout << s.exit_status() << std::endl;
}