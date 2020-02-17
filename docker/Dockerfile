FROM docker.io/alpine:3.11 AS builder
WORKDIR /umoria
COPY ../* /umoria
RUN apk update && apk upgrade && apk add git make cmake g++ pulseaudio-dev ncurses-dev
RUN mkdir /build && cmake -D build_dir=/build . && make

FROM docker.io/alpine:3.11
WORKDIR /umoria
COPY --from=builder /build /umoria
CMD ["umoria/umoria"]
