# !/bin/bash
docker-machine start default
docker-machine env
eval $(docker-machine env default)