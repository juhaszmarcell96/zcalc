#!/bin/bash

docker run --rm -it \
    --privileged \
    --name zcalc \
    --user=root \
    -p 4444:4444 \
    -v $PWD/../../:/root/zcalc \
    --entrypoint /bin/bash \
    zcalc:active
