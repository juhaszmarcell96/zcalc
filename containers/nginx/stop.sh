#!/bin/bash

docker stop nginx_proxy zcalc_server
docker rm nginx_proxy zcalc_server
docker-compose down