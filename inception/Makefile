
all:
	mkdir -p /home/jpark2/data/mariadb
	mkdir -p /home/jpark2/data/wordpress
	@docker compose -f ./srcs/docker-compose.yml up -d --build

down:
	@docker compose -f ./srcs/docker-compose.yml down

clean:
	@docker stop `docker ps -qa`; \
	docker rm -f `docker ps -qa`; \
	docker rmi -f `docker images -qa`; \
	docker volume rm `docker volume ls -q`; \
	docker network prune -f;

fclean:
	make clean
	rm -rf /home/jpark2/data

re:
	make fclean
	make all

.PHONY: all re down clean fclean
