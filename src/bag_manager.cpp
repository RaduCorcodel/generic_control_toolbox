#include <generic_control_toolbox/bag_manager.hpp>

namespace generic_control_toolbox
{
BagManager::BagManager(const std::string &path,
                       const std::string &default_topic)
    : default_topic_(default_topic)
{
  boost::filesystem::create_directory(path);
  int num = numOfFiles(path);
  std::string name = path + "log_" + std::to_string(num) + ".bag";
  ROS_DEBUG_STREAM("Opening a new bag: " << name);
  bag_.open(name, rosbag::bagmode::Write);
}

BagManager::~BagManager() { bag_.close(); }

int BagManager::numOfFiles(const std::string &path) const
{
  // from http://www.cplusplus.com/forum/beginner/70854/
  boost::filesystem::path p(path);
  boost::filesystem::directory_iterator end_iter;
  int num = 1;

  for (boost::filesystem::directory_iterator iter(p); iter != end_iter; iter++)
  {
    if (iter->path().extension() == ".bag")
    {
      num++;
    }
  }

  return num;
}
}  // namespace generic_control_toolbox
