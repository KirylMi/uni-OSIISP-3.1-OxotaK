## Kyrsach QT_PHP_DOCKER_POSTGRESQL

### Launch (OUTDATED, found a way to start apache at localhost (thanks stackOverflow)):
1. QT with the Source pckg
2. PostgreSQL (yeah, it's still must be installed for QT drivers(not really (sound confusing, right?)))
3. Disable PostgreSQL (optimal - disable autolaunch `sudo update-rc.d postgresql disable`)
~~
4. Start docker `docker-compsoe up`
5. Check the IP of the docker container:
    * `docker ps`
    * get the postgres container id
    * `docker inspect -f '{{range.NetworkSettings.Networks}}{{.IPAddress}}{{end}}' CONTAINER_ID`
6. Connect to the received ip
~~

### Temp info:
1. Fix button names
2. Maybe one Basic window, and others will be derived from it? (AddWindow, EditWindow)
