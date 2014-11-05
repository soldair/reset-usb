
var addon = require('./build/Release/resetusb.node');
var ttylookup = require('tty-to-usb-device')
module.exports = function(path,cb){
  if(path.indexOf('/dev/tty') === 0) {
    return ttylookup(path,function(err,usb){
      if(err) return cb(err);
      path = usb;
      reset();
    })
  }

  function reset(){
    try{
      cb(false,addon.resetusb(path));
    } catch(e){
      cb(e);
    }
  }

  setImmediate(reset);
}

// no support for tty paths.
module.exports.resetSync = addon.resetusb;
