#!/bin/bash

docker start LOCAL
docker exec -it LOCAL make clean -C/root/Toolchain
docker exec -it LOCAL make clean -C/root/
docker exec -it LOCAL make -C/root/Toolchain
docker exec -it LOCAL make -C/root/
docker stop LOCAL
