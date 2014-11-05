var fs = require('fs');
var ttyusb = require("tty-to-usb-device");

var ttys = [];

fs.readdir('/dev/',function(err,files){
  files.forEach(function(f){
    if(f.indexOf('ttyACM') > -1) ttys.push('/dev/'+f);
  });

  ttys.forEach(function(tty){ 
    ttyusb(tty,function(err,device,meta){
      console.log(tty,err,device);
      
    });
  })

})



//console.log(addon);

//console.log(addon.resetusb("/dev/bus/usb/002/006"));
