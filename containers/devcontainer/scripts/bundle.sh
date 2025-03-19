#!/bin/bash

cd /root/zcalc/client
esbuild main.js --bundle --minify --outfile=bundled_main.js