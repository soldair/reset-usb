
var test = require('tape');

var reset = require("../");

test("can reset",function(t){
  reset("/dev/bus/usb/002/011",function(err,success){
    t.ok(success,'should be successful');
    t.end();
  });
});

test("errors when not valid file",function(t){
    reset("/dev/bus/ughshjskskjsjk",function(err){;
      t.ok(err,"got error");
      t.end();
    });
})


