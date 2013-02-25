# zoneid: Binding for illumos zone-related library functions

This package exposes the following libc functions on illumos systems:

    #include <zone.h>

    zoneid_t getzoneid(void);
    zoneid_t getzoneidbyname(const char *name);
    ssize_t getzonenamebyid(zoneid_t id, char *buf, size_t buflen);

For details on these functions, see
[getzoneid(3c)](http://illumos.org/man/3c/getzoneid).


## Synopsis

Here's an example use:

    var mod_assert = require('assert');
    var mod_zoneid = require('zoneid');

    var myzoneid = mod_zoneid.getzoneid();
    var myzonename = mod_zoneid.getzonenamebyid(myzoneid);

    console.log(myzoneid);
    console.log(myzonename);
    mod_assert.equal(myzoneid, mod_zoneid.getzoneidbyname(myzonename));

In the global zone, this prints:

    0
    global

In a non-global zone, this could print:

    71
    a2cf54c9-ec0d-412d-b40d-d38c6092b114
