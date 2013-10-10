/*
 * zoneid.c: exposes documented libc zone-related functions to Node.js
 */

#include <node.h>
#include <v8.h>

#include <errno.h>
#include <string.h>
#include <zone.h>

using namespace v8;

Handle<Value>
call_getzoneid(const Arguments& args)
{
	HandleScope scope;

	if (args.Length() != 0) {
		ThrowException(node::ErrnoException(EINVAL));
		return (scope.Close(Undefined()));
	}

	return (scope.Close(Number::New(getzoneid())));
}

Handle<Value>
call_getzoneidbyname(const Arguments& args)
{
	HandleScope scope;
	char buf[ZONENAME_MAX];

	if (args.Length() != 1 || !args[0]->IsString()) {
		ThrowException(node::ErrnoException(EINVAL));
		return (scope.Close(Undefined()));
	}

	/*
	 * For our caller's convenience, we treat invalid zonenames (i.e., too
	 * short or too long) the same as non-existent zonenames.
	 */
	String::AsciiValue val(args[0]);
	if (val.length() == 0 || val.length() > ZONENAME_MAX - 1)
		return (scope.Close(Number::New(-1)));

	(void) strlcpy(buf, *val, sizeof (buf));
	return (scope.Close(Number::New(getzoneidbyname(buf))));
}

Handle<Value>
call_getzonenamebyid(const Arguments& args)
{
	HandleScope scope;
	char buf[ZONENAME_MAX];

	if (args.Length() != 1 || !args[0]->IsInt32()) {
		ThrowException(node::ErrnoException(EINVAL));
		return (scope.Close(Undefined()));
	}

	if (getzonenamebyid(args[0]->Int32Value(), buf, sizeof (buf)) < 0) {
		ThrowException(node::ErrnoException(errno));
		return (scope.Close(Undefined()));
	}

	return (scope.Close(String::New(buf)));
}

void
init(Handle<Object> target)
{
	target->Set(String::NewSymbol("getzoneid"),
	    FunctionTemplate::New(call_getzoneid)->GetFunction());
	target->Set(String::NewSymbol("getzoneidbyname"),
	    FunctionTemplate::New(call_getzoneidbyname)->GetFunction());
	target->Set(String::NewSymbol("getzonenamebyid"),
	    FunctionTemplate::New(call_getzonenamebyid)->GetFunction());
}

NODE_MODULE(zoneid, init)
