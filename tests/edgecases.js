/*
 * edgecases.js: exercise edge cases
 */
var mod_assert = require('assert');
var mod_zoneid = require('../build/Release/zoneid');

/* getzoneid */
mod_assert.throws(function () { mod_zoneid.getzoneid('hello'); }, /EINVAL/);

/* getzoneidbyname */
mod_assert.throws(function () { mod_zoneid.getzoneidbyname(); }, /EINVAL/);
mod_assert.throws(function () { mod_zoneid.getzoneidbyname(3); }, /EINVAL/);
mod_assert.throws(function () { mod_zoneid.getzoneidbyname({}); }, /EINVAL/);

var toolong= '';
for (i = 0; i < 1025; i++)
	toolong += 'a';

mod_assert.equal(-1, mod_zoneid.getzoneidbyname(toolong));
mod_assert.equal(-1, mod_zoneid.getzoneidbyname(''));
mod_assert.equal(-1, mod_zoneid.getzoneidbyname('aaaa'));

/* getzonenamebyid */
mod_assert.throws(function () { mod_zoneid.getzonenamebyid(); }, /EINVAL/);
mod_assert.throws(function () { mod_zoneid.getzonenamebyid({}); }, /EINVAL/);
mod_assert.throws(function () { mod_zoneid.getzonenamebyid(''); }, /EINVAL/);
mod_assert.throws(function () { mod_zoneid.getzonenamebyid('h'); }, /EINVAL/);

var myzoneid = mod_zoneid.getzoneid();
mod_assert.equal(myzoneid,
    mod_zoneid.getzoneidbyname(mod_zoneid.getzonenamebyid(myzoneid)));

console.log('tests ok');
