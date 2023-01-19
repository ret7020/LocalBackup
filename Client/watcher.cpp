#include <inotify-cpp/NotifierBuilder.h>
#include <filesystem>
#include <iostream>
#include <thread>
#include <chrono>

using namespace inotify;

int main(int argc, char** argv)
{
  if (argc <= 1) {
      std::cout << "Usage: ./inotify_example /path/to/dir" << std::endl;
      exit(0);
  }

  std::filesystem::path path(argv[1]);

  // onChange handler
  auto handleNotification = [&](Notification notification) {
      std::cout << notification.event << "on " << notification.path << " at "
                << notification.time.time_since_epoch().count() << std::endl;
  };

  // Needed events
  auto events = { Event::create,
                  Event::modify,
                  Event::remove }; //Event.move
 

  auto notifier = BuildNotifier()
                      .watchPathRecursively(path)
                      .ignoreFileOnce("fileIgnoredOnce")
                      .ignoreFile("fileIgnored")
                      .onEvents(events, handleNotification);
  
  std::thread thread([&](){ notifier.run(); });
  thread.join();
  return 0;
}

