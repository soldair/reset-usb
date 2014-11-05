#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#include <errno.h>
#include <sys/ioctl.h>
#include <linux/usbdevice_fs.h>

#include "nan.h"

using namespace v8;
using namespace node;

// based on 
// usbreset -- send a USB port reset to a USB device 
// from http://askubuntu.com/questions/645/how-do-you-reset-a-usb-device-from-the-command-line

static const char *path;

NAN_METHOD(resetusb) {
  NanScope();

  std::string tempString(*v8::String::Utf8Value(args[0]));    
  //NanNew(*NanUtf8String(arg[0]))
  path = tempString.c_str();

  int fd;
  int rc;

  fd = open(path, O_WRONLY);
  if (fd < 0) {
      NanThrowError("Error opening usb device file");
  } else {

    rc = ioctl(fd, USBDEVFS_RESET, 0);

    if (rc < 0) {

        NanThrowError(" =( error issuing usb device reset. Error in ioctl.");
    }
  }

  close(fd);
  //NanReturnValue(NanNew<String>(path));

  NanReturnValue(NanNew<Number>(1));

}

void InitAll(Handle<Object> exports) {
  exports->Set(NanNew<String>("resetusb"),
    NanNew<FunctionTemplate>(resetusb)->GetFunction());
}

NODE_MODULE(resetusb, InitAll);
