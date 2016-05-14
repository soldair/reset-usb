#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#include <errno.h>
#include <sys/ioctl.h>
#include <linux/usbdevice_fs.h>



#include <nan.h>
//using namespace v8;
//using namespace node;



void Reset(const Nan::FunctionCallbackInfo<v8::Value>& info) {

  if (info.Length() < 1) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }

  //Local<Object> obj = info[0].As<Object>();
  //Local<String> name = Nan::Get(obj, Nan::New<String("name").ToLocalChecked()).ToLocalChecked()->ToString();
  //v8::String::Utf8Value val(name);
  //std::string str(*val);
  //char* path = str.c_str();


  //Local<String> name = Nan::Get(info[0].As<Object>(), Nan::New("name").ToLocalChecked()).ToLocalChecked();
  //Nan::Utf8String val(name);
  //char* path = *val;


  Nan::Utf8String foo(info[0]);
  std::string tempString(*foo);

  int fd;
  int rc;

  fd = open( tempString.c_str(), O_WRONLY);
  if (fd < 0) {
    Nan::ThrowError("Error opening usb device file");
  } else {

    rc = ioctl(fd, USBDEVFS_RESET, 0);

    if (rc < 0) {

      Nan::ThrowError(" =( error issuing usb device reset. Error in ioctl.");
    }
  }

  close(fd);

  info.GetReturnValue().Set(1);
}

void Init(v8::Local<v8::Object> exports) {
    exports->Set(Nan::New("reset").ToLocalChecked(),
                       Nan::New<v8::FunctionTemplate>(Reset)->GetFunction());
}

NODE_MODULE(reset, Init)


/*

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
*/
