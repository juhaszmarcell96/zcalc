FROM debian:bookworm-slim

RUN apt update && apt update
RUN apt install -y g++ vim cmake make build-essential git esbuild
RUN apt install -y g++ libgtest-dev

COPY --chown=root:root .vimrc /root/.vimrc

RUN echo "export PS1='\[\e[91m\]\u\[\e[0m\]:\[\e[94m\]\w\[\e[0m\]$ '" >> /root/.bashrc
RUN echo 'export PROMPT_COMMAND="echo -n"' >> /root/.bashrc

RUN echo 'alias build="/root/zcalc/containers/devcontainer/scripts/build.sh"' >> ~/.bashrc
RUN echo 'alias test="/root/zcalc/containers/devcontainer/scripts/test.sh"' >> ~/.bashrc
RUN echo 'alias bundle="/root/zcalc/containers/devcontainer/scripts/bundle.sh"' >> ~/.bashrc
RUN echo 'alias clean="/root/zcalc/containers/devcontainer/scripts/clean.sh"' >> ~/.bashrc
RUN echo 'alias purge="/root/zcalc/containers/devcontainer/scripts/purge.sh"' >> ~/.bashrc

WORKDIR /root