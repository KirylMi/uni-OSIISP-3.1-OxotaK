## Kyrsach QT_PHP_DOCKER_POSTGRESQL

### Launch:
1. QT with the Source pckg
2. PostgreSQL (yeah, it's still must be installed for QT drivers(not really (sound confusing, right?)))
3. Disable PostgreSQL (optimal - disable autolaunch `sudo update-rc.d postgresql disable`)
4. Start docker `docker-compsoe up`
5. Check the IP of the docker container:
    * `docker ps`
    * get the postgres container id
    * `docker inspect -f '{{range.NetworkSettings.Networks}}{{.IPAddress}}{{end}}' CONTAINER_ID`
6. Connect to the received ip

### Temp info:
1. Get DB connection settings from file or smth (equivalent of dotenv maybe?)
