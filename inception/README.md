- 개요

가상 머신과 docker의 차이에 대해 이해하고, docker와 docker compose를 사용해보며 docker 환경에 대해 공부해보는 과제

---
- 과정

1. 이미지 생성을 위해 mariadb, wordpress, nginx의 각 컨테이너의 목적에 맞게 Dockerfile을 작성한다.
2. mariadb에서 root의 비밀번호 설정이나, wordpress의 사용자 설정 및 nginx의 ssl 인증서 설정과 같은 컨테이너의 기본 설정들을 잡아줄 config 파일을 작성한다.
3. 작성한 Dockerfile들을 통해 일괄적으로 이미지를 생성하고, 해당 이미지로 컨테이너를 올릴 수 있도록 docker-compose.yml 파일을 작성한다. 도커 네트워크나 볼륨에 관한 설정도 docker-compsoe.yml 파일에서 설정한다.

---
- 어려웠던 점

1. 이전 과제에서 가상 환경은 직접 다뤄보면서 이해했으나, docker와 오케스트레이션에 대한 개념을 처음 접해보았다. 개념들과 전체적인 구조에 대해 이해하고 있는 지금에서는 이 과제가 어떤 취지이고, 어떤 것들을 공부해보고, 그게 왜 좋은지에 대해서 알고있지만, 공부를 시작한 초반에는 개념도 잘 안잡히고 왜 하는지도 모른채 무작정 공부를 시작했었다. 그렇게 공부를 시작하다보니 집중도 잘 안되고 공부 기간도 분량에 비해 오래 걸렸던 것 같다.
2. config 파일과 Dockerfile을 통해 이미지를 생성하고 해당 이미지로 docker-compose를 통해서 컨테이너를 프로세스에 올리는 형태라서, 작성한 config 파일이나 Dockerfile에 치명적이지 않은 오류가 있다면 동작 과정에서 그 원인을 정확하게 찾아내기가 쉽지 않았다.
3. docker를 접해보지 않은 사람에게 설명을 한다면, docker의 구조부터, 왜 가상환경에 비해 더 빠른지, 어떤 경우에 자주 사용되는지, docker compose는 왜 사용하는지 등 설명해주어야 하는 정보가 방대하기 때문에 그 모든 것들을 정리해야만 했다. 공부하고 정리하는 과정이 config 파일과 Dockerfile을 작성하고 동작을 확인하는 과정보다 길었던 것 같다.

---
- 배운 점

https://thinkable-son-6b5.notion.site/Inception-5abdaeac6abf440893ed975126a7b478
