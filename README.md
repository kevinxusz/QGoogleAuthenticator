QGoogleAuthenticator
====================

*Library optimized for Qt 5.2.0*

A [Google Authenticator](http://code.google.com/p/google-authenticator/) library including the following features:
* Generate a Google Authenticator secret
* Check a code
* Get a new code based on timestamp


How to build
------------
* Open .pro in QtCreator, specify build directory for release and/or debug target and hit "Build"
* Or: run qmake and make from command line


How to use
----------

In your .pro file add:
```
LIBS += "<path-to-your-QGoogleAuthenticator-library>"
```

And in your source add:
```
#include "qgoogleauthenticator.h"
```
WARNING: You need to have access to base32.h, hmac.h and qgoogleauthenticator_global.h in qgoogleauthenticator.h

* To generate a new secret call ```QGoogleAuthenticator::generate_secret();```
* To check a code call ```QGoogleAuthenticator::checkCode(<code>, <your secret>);```
* To get a new code call ```QGoogleAuthenticator::getCode(<your secret>, <time (if empty system time is beeing used)>);```


