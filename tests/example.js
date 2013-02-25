/*
 * example.js: demo basic functionality
 */
var mod_assert = require('assert');
var mod_zoneid = require('../build/Release/zoneid');

var myzoneid = mod_zoneid.getzoneid();
var myzonename = mod_zoneid.getzonenamebyid(myzoneid);

console.log(myzoneid);
console.log(myzonename);
mod_assert.equal(myzoneid, mod_zoneid.getzoneidbyname(myzonename));
