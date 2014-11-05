reset-usb
=========

reset a usb device. simulate plug/unplug.

```js
var reset = require("reset-usb")

reset('/dev/bus/usb/002/007',function(err,data){
  console.log(err,data);
  if(!err) console.log('success!');
})

```
you can also specify the path to a usb serial tty device and ```tty-to-usb-device`` will find it for you.

```js

var reset = require("reset-usb")
reset('/dev/ttyACM0',function(err,data){
  console.log(err,data);
  if(!err) console.log('success!');
})


```


and the bad news.
-----------------

- requires linux.  ioctls are supported in different ways cross platform. it would be nice for this to work on osx.
- requires sudo. usb devices are owned by root. you have to be root to restart them =(



