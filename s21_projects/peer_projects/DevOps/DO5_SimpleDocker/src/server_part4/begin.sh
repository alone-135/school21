#!/bin/bash
gcc hello.c -lfcgi -o hello
spawn-fcgi -p 8080 ./hello
service nginx start
/bin/bash